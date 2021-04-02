// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"
#include "bitfile.h"

struct minHeap * minHeap_new()
{
	struct minHeap * result;

	result = malloc(sizeof(struct minHeap));
	result->max_size = 256;
	result->top = 0;

	result->heap = malloc(sizeof(struct huffchar **) * 256);

	return result;
}

void findMax(int freq[], int maxCombined[])
{
	int max = 0;
	int maxPos = 0;

	for(int i = 0; i < 256; i++)
	{
		if(freq[i] > max)
		{
			max = freq[i];
			maxPos = i;
		}
	}

	freq[maxPos] = 0;
	maxCombined[0] = max;
	maxCombined[1] = maxPos;
}

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
	for(int i = 0; i < 256; i++)
	{
		result->freqs[i] = 0;
	}
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

void findPlace(struct minHeap * heap, struct huffchar * hChar)
{
	int i = heap->top - 1;

	if(i == 0)
	{
		heap->heap[0] = hChar;
	}
	else
	{
		while(i > 0 && heap->heap[i - 1]->freq < hChar->freq)
		{
			heap->heap[i] = heap->heap[i - 1];
			i--;
		}
		heap->heap[i] = hChar;
	}
	// if top = 1 at start, instantly add the two and place it into pos 0;
}

void create_code(struct huffcoder * this, struct huffchar * hChar, int code_length, unsigned long long code[])
{
  if(hChar->is_compound == 0)
  {
    if(code_length == 12)
    {
      printf("%d  %d      ", code_length, hChar->u.c);
      unsigned long long x[1];
      x[0] = code[0];
      for(int i = 0; i < code_length; i++)
      {
        printf("%lld", x[0] & 1);
        x[0] = x[0] >> 1;
      }
      printf("\n");
    }
    this->code_lengths[hChar->u.c] = code_length;
    this->codes[hChar->u.c] = code[0];
  }
  else
  {
    code[0] = code[0] << 1;

    code_length += 1;
    create_code(this, hChar->u.compound.left, code_length, code);
    code[0] = code[0] | 1;
    create_code(this, hChar->u.compound.right, code_length, code);
  }
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
	unsigned char c;
	FILE * file;
	char * inputFromFile;
	int sizeOfFile = 0;
	int i = 0;

	file = fopen(filename, "r");
	assert(file != NULL);
	c = fgetc(file);
	while( !feof(file) )
	{
		c = fgetc(file);
		sizeOfFile++;
	}
	fclose(file);

	inputFromFile = malloc(sizeof(char) * sizeOfFile);

	file = fopen(filename, "r");
	c = fgetc(file);
	while(!feof(file) )
	{
		inputFromFile[i] = c;
		c = fgetc(file);
		i++;
	}
	fclose(file);

	i = 0;
	while(inputFromFile[i] != 0)
	{
		this->freqs[(int)inputFromFile[i]]++;
		i++;
	}

	for(i = 0; i < 256; i++)
	{
		if(this->freqs[i] == 0)
			this->freqs[i] = 1;
	}
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
	int freqsCopy[256];
	int maxCombined[2];    // in pos 0 = freq, in pos 1 = char in int form.
	int i, seqno;

	for(i = 0; i < 256; i++)
	{
		freqsCopy[i] = this->freqs[i];
	}

	struct minHeap * heap = minHeap_new();

	for( i = 0; i < 256; i++)
	{
		findMax(freqsCopy, maxCombined);
		heap_add(heap, maxCombined);
	}

	seqno = 256;

	while(heap->top > 1)
	{
		struct huffchar * newChar = combine(heap->heap[heap->top - 1], heap->heap[heap->top - 2], seqno);
		seqno++;
		heap->top--;

		findPlace(heap, newChar);
	}

	this->tree = heap->heap[heap->top - 1];


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
