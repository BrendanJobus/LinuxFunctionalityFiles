#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

struct stack
{
	char ** items;
	int max_size;
	int top;
};

void stack_push(struct stack * this, char * value)
{
	this->items[this->top] = value;
	this->top++;
}

char * stack_pop(struct stack * this)
{
	char * poppedCharacter;
	poppedCharacter = this->items[--this->top];

	return poppedCharacter;
}

struct stack * stack_new(int max_size)
{
	struct stack * result;

	result = malloc(sizeof(struct stack));
	result->max_size = max_size;
	result->top = 0;

	result->items = malloc(sizeof(char **) * max_size);

	return result;
}

struct double_stack
{
	double * items;
	int max_size;
	int top;
};

void double_stack_push(struct double_stack * this, double value)
{
	this->items[this->top] = value;
	this->top++;
}

double double_stack_pop(struct double_stack * this)
{
	double poppedNumber;
	poppedNumber = this->items[--this->top];

	return poppedNumber;
}

struct double_stack * double_stack_new(int max_size)
{
	struct double_stack * result;

	result = malloc(sizeof(struct double_stack));
	result->max_size = max_size;
	result->top = 0;

	result->items = malloc(sizeof(double) * max_size);

	return result;
}

void apply_operator(struct double_stack * stack, char * operator)
{
/*	for(int i = 0; i < stack->top; i++)
	{
		printf("%f\n", stack->items[i]);
	}
	*/
	double firstNumber = double_stack_pop(stack);
	double secondNumber = double_stack_pop(stack);
	double answer;

	if(*operator == '+')
	{
		answer = firstNumber + secondNumber;
		double_stack_push(stack, answer);
	}
	else if(*operator == '-')
	{
		answer = secondNumber - firstNumber;
		double_stack_push(stack, answer);
	}
	else if(*operator == 'x')
	{
		//printf("%f\n", firstNumber);
		//printf("%f\n", secondNumber);
		answer = firstNumber * secondNumber;
		//printf("%f\n", answer);
		double_stack_push(stack, answer);
	}
	else if(*operator == '/')
	{
		answer = secondNumber / firstNumber;
		double_stack_push(stack, answer);
	}
	else if(*operator == '^')
	{
		answer = pow(secondNumber, firstNumber);
		double_stack_push(stack, answer);
	}
	else
	{
		//printf("%f\n", atof(operator) );
		double_stack_push( stack, secondNumber );
		double_stack_push( stack, firstNumber );
		double_stack_push( stack, atof(operator) );
	}
	return;
}

double postfix_calculation(struct stack * this, int nterms)
{
	struct double_stack * stack;
	stack = double_stack_new(nterms);
	double answer;
	int i;

	for(i = 0; i < this->top; i++)
	{
		if( strlen( this->items[i] ) == 1)
		{
			apply_operator(stack, this->items[i] );
		}
		else
		{
			char * value = this->items[i];
			//printf("%f\n", atof( value ));
			double_stack_push(stack, atof( value ) );
		}
	}

	answer = double_stack_pop(stack);
	return answer;
}

double evaluate_postfix_expression(char ** inputs, int numberOfInputs)
{
	int i;

	struct stack * this = stack_new(numberOfInputs);

	for(i = 0; i < numberOfInputs; i++)
	{
		stack_push( this, inputs[i] );
	}

	double answer = postfix_calculation(this, this->top);
	return answer;
}

// main function for a simple bench calculator with command
// line inputs
int main(int argc, char ** argv) {
	if ( argc == 1 ) {
		// command line contains only the name of the program
		printf("Error: No command line parameters provided\n");
		printf("Usage: %s postfix|infix <expression>\n", argv[0]);
		exit(1);
	}
	else if ( argc == 2 ) {
		// command line contains name of prog and one other parameter
		printf("Error: No expression to evaluate provided\n");
		printf("Usage: %s postfix|infix <expession>\n", argv[0]);
		exit(1);
	}
	else {
		// command line has enough parameters for an expression
		double result;
		if (strcmp(argv[1], "postfix") == 0 ) {
			//pass the command line parameters, but with the first two removed
			result = evaluate_postfix_expression(argv+2, argc-2);
			printf("Result is %lf\n", result);
		}
		else if ( strcmp(argv[1], "infix") == 0 ) {
			// pass the command line parameters, but with the first two removed
			// result = evaluate_infix_expression(argv+2, argc-2);
			// printf("Result is %lf\n", result);
		}
		else {
			printf("Error: You must specify whether the expression is infix or postfix\n");
			printf("Usage: %s postifx|infix <expression>\n", argv[0]);
			exit(1);
		}
	}
	return 0;
}
