#include "infix.h"

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
	else if(*operator == 'X')
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

char ** changeInfixToPostfix(char ** inputs, int numberOfInputs)
{
	struct stack * this = stack_new(numberOfInputs);
	char ** outputString;
	outputString = malloc(sizeof(char **) * numberOfInputs);
	char * addToOutput;

	int i = 0;
	int j;

	for(j = 0; j < numberOfInputs; j++)
	{
		if(strcmp(inputs[j], "+") != 0 && strcmp(inputs[j], "-") != 0 && strcmp(inputs[j], "X") != 0 && strcmp(inputs[j], "/") != 0 && strcmp(inputs[j], "^") != 0 && strcmp(inputs[j], "(") != 0 && strcmp(inputs[j], ")") != 0)
		{
			outputString[i] = inputs[j];
			i++;
		}
		else if(strcmp(inputs[j], "(") == 0)
		{
			stack_push(this, inputs[j]);
		}
		else if(strcmp(inputs[j], "+") == 0 || strcmp(inputs[j], "-") == 0 || strcmp(inputs[j], "X") == 0 || strcmp(inputs[j], "/") == 0 || strcmp(inputs[j], "^") == 0)
		{
			if(strcmp(inputs[j], "+") == 0 || strcmp(inputs[j], "-") == 0)
			{
				if(this->top != 0)
				{
					while( this->top != 0 && strcmp( this->items[this->top - 1], "(") != 0 && ( strcmp( (this->items[this->top - 1]) , "X") == 0 || strcmp( (this->items[this->top - 1]) , "/") == 0 || strcmp( (this->items[this->top - 1]) , "^") == 0) )
					{
						addToOutput = stack_pop(this);
						outputString[i] = addToOutput;
						i++;
					}
				}
			}
			else if(strcmp(inputs[j], "X") == 0 || strcmp(inputs[j], "/") == 0)
			{
				if(this->top != 0)
				{
					while( strcmp(this->items[this->top], "^") == 0 )
					{
						addToOutput = stack_pop(this);
						outputString[i] = addToOutput;
						i++;
					}
				}
			}
			else
			{
			}
			stack_push(this, inputs[j]);
		}
		else if(strcmp(inputs[j], ")") == 0)
		{
			for(int k = this->top; k > 0; k++)
			{
				addToOutput = stack_pop(this);
				if( strcmp(addToOutput, "(") == 0 )
				{
					break;
				}
				else
				{
					outputString[i] = addToOutput;
					i++;
				}
			}
		}
		else
		{
		}
	}

	if(this->top > 0)
	{
		for(j = 0; j < this->top; j++)
		{
			outputString[i] = stack_pop(this);
			i++;
		}
	}

	return outputString;
}

int newInputSize(char ** inputs, int numberOfOriginalInputs)
{
	int i;
	int numberOfInputs = 0;

	for(i = 0; i < numberOfOriginalInputs; i++)
	{
		if( strcmp(inputs[i], "(") != 0 && strcmp(inputs[i], ")") != 0)
		{
			numberOfInputs++;
		}
	}

	return numberOfInputs;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  // Write your code here
  char ** postfixInputs = changeInfixToPostfix(args, nargs);
	int i;

	int numberOfPostfixInputs;
	numberOfPostfixInputs = newInputSize(args, nargs);

	struct stack * this = stack_new(nargs);

	for(i = 0; i < numberOfPostfixInputs; i++)
	{
		stack_push( this, postfixInputs[i] );
	}

	double answer = postfix_calculation(this, numberOfPostfixInputs);
	return answer;
		//answer;
}
