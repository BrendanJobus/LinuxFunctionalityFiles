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

void heap_add(struct minHeap * heap, int maxCombined[])
{
	struct huffchar * hChar = huffchar_new(maxCombined[0], maxCombined[1]);
	heap->heap[heap->top] = hChar;
	heap->top++;
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
	result->tree = malloc( sizeof(struct huffchar) );

	return result;
}

struct huffchar * combine(struct huffchar * smallest, struct huffchar * secondSmallest, int seqno)
{
	struct huffchar * result;

	result = malloc(sizeof(struct huffchar));
	result->freq = smallest->freq + secondSmallest->freq;
	result->is_compound = 1;
	result->seqno = seqno;

	result->u.compound.left = smallest;
	result->u.compound.right = secondSmallest;

	return result;
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
    this->list[i] = huffchar_new(this->freqs[i], i);
  }

  while(this->n_node > 1)
  {

  }
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
  // using recursion on this
  // call function on root, then go to the left while you can, then the right afterward
  // each time couting to get the huffcode of the character your going to

  int code_length = 0;
  unsigned long long code[1];
  code[0] = 0;

  create_code(this, this->tree, code_length, code);

}

// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for ( i = 0; i < NUM_CHARS; i++ ) {
    // put the code into a string
    assert(this->code_lengths[i] < NUM_CHARS);
    for ( j = this->code_lengths[i]-1; j >= 0; j--)
    {
      buffer[j] = ((this->codes[i] >> j) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';

    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename, char * output_filename)
{

}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename, char * output_filename)
{

}
