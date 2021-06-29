// C program to convert infix expression to postfix 
#include <stdio.h> 
#include <conio.h>
#include <string.h> 
#include <stdlib.h> 

struct Stack		
{
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(int cap)
{
	struct Stack *st = (struct Stack*) malloc(sizeof(struct Stack));

	st->top = -1;
	st->capacity = cap;
	st->array = (int*)malloc(cap * sizeof(int));
	return st;
}
int isEmpty(struct Stack *st)
{
	return st->top == -1;
}
int isFull(struct Stack *st)
{
	return (st->top == st->capacity - 1);
}
char peek(struct Stack *st)
{
	return st->array[st->top];
}
char pop(struct Stack *st)
{
	if (isEmpty(st))
		return '$';
	int temp = st->array[st->top];
	st->top--;
	return temp;
}
void push(struct Stack *st, char op)
{
	st->top++;
	st->array[st->top] = op;
}

int isOperand(char ch)	 
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int Precedence(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}

void infixToPostfix(char *exp)
{
	int i, k;
	char postfix[30] = {};
	struct Stack *s = createStack(strlen(exp));   

	for (i = 0, k = 0; exp[i]; i++)
	{
		if (isOperand(exp[i]))   
		{
			postfix[k] = exp[i];
			k++;
		}
		else if (exp[i] == '(')   
			push(s, exp[i]);

		else if (exp[i] == ')')
		{
			while (peek(s) != '(' && !isEmpty(s))
			{
				postfix[k] = pop(s);
				k++;
			}			 
			if (!isEmpty(s) && peek(s) != '(')
				return; // invalid expression              
			else
				pop(s);
		}
		else 
		{
		//	if (Precedence(exp[i]) <= Precedence(peek(s)))
			while (Precedence(exp[i]) <= Precedence(peek(s)) && !isEmpty(s))
			{
				postfix[k] = pop(s);
				k++;
			}
			push(s, exp[i]);
		}
	}

	while (!isEmpty(s))  
	{
		postfix[k] = pop(s);
		k++;
	}
	postfix[k] = '\0';
	printf("%s", postfix);
}

int main()
{
	char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
	infixToPostfix(exp);
	printf("\n\n");
	char exp2[] = "a+b*c-d/e";
	infixToPostfix(exp2);
	printf("\n\n");
	char exp3[] = "(a+b)*(c-d)/e";
	infixToPostfix(exp3);
	printf("\n\n");
	char exp4[] = "a+((b+c)+(d+e)*f)/g";
	infixToPostfix(exp4);
	printf("\n\n");
	char exp5[] = "a-b/c*d)^e";
	infixToPostfix(exp5);
	_getch();
}