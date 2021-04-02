#include <stdlib.h>
#include <stdio.h>
#include "bitset.h"

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size)
{
	struct bitset * result;

	result = malloc(sizeof(struct bitset));

	result->universe_size = size;
	result->size_in_words = 0;

	int sizeToUse;
	sizeToUse = (size / sizeof(uint64_t)) + 1;

	result->bits = malloc(sizeof(uint64_t) * sizeToUse);

	for(int i = 0; i < (size / sizeof(uint64_t) + 1); i++)
	{
		result->bits[i] = 0;
	}

	return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this)
{
	return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this)
{
	return this->size_in_words;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item)               // check to find what element the item goes into e.g 64 goes into element 2 of the pointer array
{
	int elementBitIsIn = item / sizeof(uint64_t);
	uint64_t bit = 1;
	int llrShifts = item % sizeof(uint64_t);
	bit = bit << llrShifts;
	//printf("%lu, %lu, ", this->bits[elementBitIsIn], bit);
	if(bit == (this->bits[elementBitIsIn] & bit) )
	{
		//printf("here 1");
		return 1;
	}
	else
	{
			//printf("here 2");
		return 0;
	}
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item)
{
	int elementBitIsIn = item / sizeof(uint64_t);
	uint64_t bit = 1;
	int llrShifts = item % sizeof(uint64_t);

	this->bits[elementBitIsIn] |= bit << llrShifts;

	this->size_in_words++;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item)
{
	int elementBitIsIn = item / sizeof(uint64_t);
	uint64_t bit = 0;
	int llrShifts = item % sizeof(uint64_t);
	//bit = bit << llrShifts;
	llrShifts = sizeof(uint64_t) - llrShifts - 1;

	for(int i = 0; i < sizeof(uint64_t); i++)
	{
		bit = bit << 1;
		if(i != llrShifts)
		{
			bit |= 1;
		}
	}

	//this->bits[elementBitIsIn] = ~(this->bits[elementBitIsIn] & bit);

	this->bits[elementBitIsIn] &= bit;

	this->size_in_words--;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
	int i;
	for(i = 0; i < ( dest->universe_size / sizeof(uint64_t) + 1 ); i++)
	{
		dest->bits[i] = src1->bits[i] | src2->bits[i];
	}
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
	int i;
	for(i = 0; i < ( dest->universe_size / sizeof(uint64_t) + 1 ); i++)
	{
		dest->bits[i] = src1->bits[i] & src2->bits[i];
	}
}
