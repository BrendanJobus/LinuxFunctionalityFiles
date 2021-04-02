// code for a huffman coder

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"
#include "bitfile.h"

struct huffchar * huffchar_new(int freq, int asciiChar)
{
	struct huffchar * result;

	result = malloc(sizeof(struct huffchar));
	result->freq = freq;
	result->is_compound = 0;
	result->seqno = asciiChar;
	result->u.c = asciiChar;

	return result;
}

struct huffchar * removeSmallest(struct huffcoder * this)
{
  int i, index = 0;
  for(i = 0; i < this->n_node; i++)
  {
    if(this->huffCharList[i]->freq < this->huffCharList[index]->freq)
      index = i;
    else if(this->huffCharList[i]->freq == this->huffCharList[index]->freq && this->huffCharList[i]->seqno < this->huffCharList[index]->seqno)
      index = i;
  }
  struct huffchar * result = this->huffCharList[index];
  this->n_node--;
  this->huffCharList[index] = this->huffCharList[this->n_node];
  return result;
}

// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
	struct huffcoder * result;
	result = malloc( sizeof(struct huffcoder) );

	for(int i = 0; i < NUM_CHARS; i++)
	{
		result->freqs[i] = 0;
    result->code_lengths[i] = 0;
    result->codes[i] = 0;
	}
  result->n_seq = NUM_CHARS;
  result->n_node = NUM_CHARS;
	result->tree = malloc(sizeof(struct huffchar));

  result->huffCharList = malloc(sizeof(struct huffchar *) * NUM_CHARS);

	return result;
}

struct huffchar * combine(int freq, struct huffchar * smallest, struct huffchar * secondSmallest, int seqno)
{
	struct huffchar * result;

	result = malloc(sizeof(struct huffchar));
	result->freq = freq;
	result->is_compound = 1;
	result->seqno = seqno;

	result->u.compound.left = smallest;
	result->u.compound.right = secondSmallest;

	return result;
}

void create_code(struct huffcoder * this, struct huffchar * hChar, unsigned long long code, int length)
{
  if(!hChar->is_compound)
  {
    this->codes[hChar->u.c] = code;
    this->code_lengths[hChar->u.c] = length;
  }
  else
  {
    code <<= 1;
    create_code(this, hChar->u.compound.left, code, length + 1);
    create_code(this, hChar->u.compound.right, code + 1, length + 1);
  }
}

void write(struct bitfile * file, unsigned long long code, int code_length)
{
  for(int i = code_length - 1; i >= 0; i--)
  {
    bitfile_write_bit(file, ((code >> i) & 1));
  }
}
// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
	unsigned char c;
	FILE * file;

	file = fopen(filename, "r");
	assert(file != NULL);
	c = fgetc(file);
	while( !feof(file) )
	{
    this->freqs[c]++;
  	c = fgetc(file);
	}
	fclose(file);

	for(int i = 0; i < NUM_CHARS; i++)
	{
		if(this->freqs[i] == 0)
			this->freqs[i] = 1;
	}
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
  for(int i = 0; i < NUM_CHARS; i++)
  {
    this->huffCharList[i] = huffchar_new(this->freqs[i], i);
  }

  while(this->n_node > 1)
  {
    struct huffchar * smallest = removeSmallest(this);
    struct huffchar * secondSmallest = removeSmallest(this);
    int freq = smallest->freq + secondSmallest->freq;
    this->huffCharList[this->n_node] = combine(freq, smallest, secondSmallest, this->n_seq++);
    this->n_node++;
  }
  this->tree = this->huffCharList[0];
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
  create_code(this, this->tree, 0, 0);
}

// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for (i = 0; i < NUM_CHARS; i++) {
    // put the code into a string
    assert(this->code_lengths[i] < NUM_CHARS);
    int k = 0;
    for (j = this->code_lengths[i] - 1; j >= 0; j--) {
      buffer[k++] = ((this->codes[i] >> j) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';

    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);
    ;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename, char * output_filename)
{
	struct bitfile * write_file = bitfile_open(output_filename, "w");
	FILE * read_file = fopen(input_filename, "r");
	assert(read_file != NULL);
	unsigned char c;
	unsigned long long code;
	int code_length;
	c = fgetc(read_file);
	while(!feof(read_file))
	{
		code = this->codes[c];
		code_length = this->code_lengths[c];

		write(write_file, code, code_length);
		c = fgetc(read_file);
	}
	write(write_file, this->codes[4], this->code_lengths[4]);
	bitfile_close(write_file);
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename, char * output_filename)
{
	u_int64_t buffer = 0;
	int buffer_len = 0;
	FILE * file = fopen(output_filename, "w");
	struct bitfile * input = bitfile_open(input_filename, "r");

	int bit = bitfile_read_bit(input);
	while(!bitfile_end_of_file(input))
	{
		buffer = buffer << 1 | bit;
		buffer_len++;
		for(int i = 0; i < NUM_CHARS; i++)
		{
			if(i == 4)
				continue;
			if(this->codes[i] == buffer && this->code_lengths[i] == buffer_len)
			{
				fputc(i, file);
				buffer = 0;
				buffer_len = 0;
			}
		}
		bit = bitfile_read_bit(input);
	}
	fflush(file);
	fclose(file);
}
