// include parts of the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

// type declaration for stack of doubles
struct double_stack
{
  double * items;
  int max_size;
  int top;
};

// prototypes of functions that operate on the double stack

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value)
{
  this->items[this->top] = value;
  printf("%f\n", this->items[this->top]);
  this->top++;
}

// pop a vlue from the stack
double double_stack_pop(struct double_stack * this)
{
  double poppedNumber;
  poppedNumber = this->items[--this->top];

  return poppedNumber;
}

// create a new empty stack
struct double_stack * double_stack_new(int max_size)
{
  struct double_stack * result;

  // allocate space for the stack header
  result = malloc(sizeof(struct double_stack));
  result->max_size = max_size;
  result->top = 0;
  // allocate space for the data stored in the stack
  result->items = malloc(sizeof(double)*max_size);
  // return pointer to the newly-allocated stack
  return result;
}

int main(int argc, char ** argv)
{
  int i;

  int bit = 1;
  bit = bit >> 1;

  if (argc == 1)
  {
    printf("Please try adding some command-line parameters\n");
    printf("Usage: %s <param1> <param2> ...\n", argv[0]);
    exit(1);
  }

  printf("The number of command line parameters is stored in argc: %d\n", argc);
  printf("The value of argc couts the name of the program itself as a parameter\n");
  printf("The name of the program is stored in argv[0]: %s\n", argv[0]);
  printf("The parameters are:\n");
  for(i = 1; i < argc; i++)
  {
	  printf("%s\n", argv[i]);
  }

  struct double_stack * this = double_stack_new(argc - 1);
  for(i = 1; i < argc; i++)
  {
    double_stack_push(this, atof(argv[i]));
  }

  printf("%f\n", double_stack_pop(this));

  return 0;
}
// end of code
