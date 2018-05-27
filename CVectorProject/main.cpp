
#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include "CVector/CVector.h"
#include "CStack/CStack.h"
#include <string.h>
#include <math.h>


#define isNumber(a)  a >= '0' && a <= '9'
#define isCharacter(a) a >='A' && a <= 'z'


enum Process
{
	undefined,
	lhBracked,
	addProc,
	subProc,
	divProc,
	mulProc,
	rhBracked
	
};

char ProcToChar(Process proc)
{
	switch (proc)
	{
	case addProc:
		return '+';
		break;
	case subProc:
		return '-';
		break;
	case divProc:
		return '/';
		break;
	case mulProc:
		return '*';
		break;
	default:
		return '?';
		break;
	}
}

Process CharToProc(char c)
{
	switch (c)
	{
	case '+':
		return Process::addProc;
		break;
	case '-':
		return Process::subProc;
		break;
	case '*':
		return Process::mulProc;
		break;
	case '/':
		return Process::divProc;
	case '(':
		return Process::lhBracked;
	case ')':
		return Process::rhBracked;
	default:
		return Process::undefined;
		break;
	}
}

enum ItemType
{
	Variable,
	Operator,
	Immediate
};

struct Element_s
{
	union
	{
		float* addr;
		enum Process proc;
		float value;
	};
	enum ItemType type;
};
typedef struct Element_s Element;

Element ElementVariable(float* addr)
{
	Element e;
	e.type = ItemType::Variable;
	e.addr = addr;
	return  e;
}
Element ElementImmediate(float val)
{
	Element e;
	e.type = ItemType::Immediate;
	e.value = val;
	return  e;
}
Element ElementOperator(enum Process proc)
{
	Element e;
	e.type = ItemType::Operator;
	e.proc = proc;
	return  e;
}

float ElementGetValue(Element e)
{	
	if (e.type == ItemType::Operator) return 0;
	else
	return e.type == ItemType::Variable ? *e.addr : e.value;
}

void PrintElement(Element e)
{
	switch (e.type)
	{
	case Variable:
		printf("%.1f", *e.addr);
		break;
	case Immediate:
		printf("%.1f", e.value);
		break;
	case Operator:
		printf("%c", ProcToChar(e.proc));
		break;
	default:
		printf("Error");
		break;
	}

}

typedef struct
{
	int size;
	int capacity;
	Element *data;
} CStackElement;





int ParseInt(char* str)
{
	int val = 0;
	while (isNumber(*str))
	{
		val *= 10;
		val += *str - '0';
		str++;
	}
	return val;
}

char* ParseString(char* str , int maxLen)
{
	char* buffer = (char*)malloc(maxLen * sizeof(char));
	int index = 0;;
	while(isCharacter(str[index]) && index < (maxLen-1))
	{
		buffer[index] = str[index];
		index++;
	}
	buffer[index] = 0;
	return  buffer;
}

int ParseFloat(char* str ,float *outValue)
{
	float val = 0;
	int advance = 0;
	while (isNumber(*str))
	{
		val *= 10;
		val += *str - '0';
		str++;
		advance++;
	}

	if (*str  == ',' || *str == '.')
	{
		str++;
		int index = 0;
		int decimalPart = 0;
		while (isNumber(*str))
		{
			decimalPart *= 10;
			decimalPart += *str - '0';
			index++;
			str++;
		}
		val += ((float)decimalPart / pow(10, index));
		advance += index+1;

	}

	*outValue = val;
	return advance;
}

void printStack(const char* name, CStackElement stack)
{
	printf("%s\n" , name);
	for (int i = 0; i < stack.size; i++)
	{
		//if (isCharacter(stack.data[i]) || isNumber(stack.data[i]))
		//{
		PrintElement(stack.data[i]);
		printf(" ");
		//}else
		//	printf("%d ", stack.data[i]);
		
	}
	printf("\n");
}

char getPriority(char val)
{
	switch (val)
	{
	case '+':
		val = 10;
		break;
	case '-':
		val = 10;
		break;
	case '*':
		val = 100;
		break;
	case '/':
		val = 100;
		break;
	case '(':
		val = 1;
		break;
	default:
		val = 0;
		break;
	}

	return val;
}



int solve()
{
	CStackElement stack;
	CStackElement postFix;
	StackInit(stack);
	StackInit(postFix);
	float deffValAddr = 1;


	char buffer[255];
	fgets(buffer, 255, stdin);


	//float outer;
	//int advance = ParseFloat(buffer, &outer);


	int len = strlen(buffer);
	buffer[len - 1] = 0;
	len--;

	int index = 0;
	while (index < len)
	{
		if (isNumber(buffer[index]))
		{
			float val;
			int advance = ParseFloat(&buffer[index], &val);
			StackPush(postFix, ElementImmediate(val));
			index += advance;

		}
		else
			if (isCharacter(buffer[index]))
			{

				StackPush(postFix, ElementVariable(&deffValAddr));
				index++;
			}
			else
			{
				char c = buffer[index];
				Process proc = CharToProc(c);
				if (proc == rhBracked)
				{
					Element e = StackPop(stack);

					while (e.proc != lhBracked)//||  e.type != ItemType::Operator
					{
						StackPush(postFix, e);
						e = StackPop(stack);
					}


				}
				else
				{
					if (proc == lhBracked) {

					}else
					while (StackTop(stack).type == Operator && proc < StackTop(stack).proc)
					{
						StackPush(postFix, StackPop(stack));
					}
					StackPush(stack, ElementOperator(proc));
				}
				index++;

			}


	}

	while (!StackIsEmpty(stack))
	{
		Element popped = StackPop(stack);
		StackPush(postFix, popped);
	}



	printStack("stack", stack);
	printStack("post", postFix);


	printf("solve process\n\n");



	int postFixIndex;
	for (postFixIndex = 0; postFixIndex < postFix.size; postFixIndex++)
	{
		Element e = postFix.data[postFixIndex];
		switch (e.type)
		{
		case Variable:
			StackPush(stack, e);
			break;
		case Operator:
		{
			float b = ElementGetValue(StackPop(stack));
			float a = ElementGetValue(StackPop(stack));
			float res;
			switch (e.proc)
			{
			case addProc:
				res = a + b;
				break;
			case subProc:
				res = a - b;
				break;
			case divProc:
				res = a / b;
				break;
			case mulProc:
				res = a * b;
				break;
			default:
				res = -999;
				break;
			}

			StackPush(stack, ElementImmediate(res));

		}
		break;
		case Immediate:
			StackPush(stack, e);
			break;
		default:
			break;
		}



		//	printStack("stack", stack);

		//	system("pause");
	}


	printf("\n here a res value as shown as ");  //,StackTop());
	printStack("\0", stack);

	

	int temp;

	return 0;
}


int main(int argc, char ** argv)
{
	while (1)
	{
		solve();
		system("pause");
	}
}

