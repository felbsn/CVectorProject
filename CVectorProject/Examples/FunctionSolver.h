#pragma once

#include <string.h>
#include <math.h>

#include "CVector/CVector.h"
#include "CStack/CStack.h"
#include "../Utilities/ColorConsole.h"


#define isNumber(a)  ((a >= '0') && (a <= '9'))
#define isCharacter(a) ((a >='A') && (a <= 'Z')) || ((a >='a') && (a <='z'))
#define isAlphabetic(a) ((isNumber(a) ||  isCharacter(a)))

enum Process
{
	undefined,
	semicolon,
	equality,
	lhBracked,
	addProc,
	subProc,
	divProc,
	mulProc,
	powProc,
	rhBracked
};

char ProcToChar(Process proc)
{
	switch (proc)
	{
	case addProc:
		return '+';
	case subProc:
		return '-';
	case divProc:
		return '/';
	case mulProc:
		return '*';
	case equality:
		return '=';
	case powProc:
		return '^';
	case semicolon:
		return ';';
	default:
		return '?';
	}
}

Process CharToProc(char c)
{
	switch (c)
	{
	case '+':
		return Process::addProc;
	case '-':
		return Process::subProc;
	case '*':
		return Process::mulProc;
	case '/':
		return Process::divProc;
	case '(':
		return Process::lhBracked;
	case ')':
		return Process::rhBracked;
	case '=':
		return Process::equality;
	case '^':
		return Process::powProc;
	case ';':
		return Process::semicolon;
	default:
		return Process::undefined;
	}
}

enum ItemType
{
	Variable,
	Operator,
	Immediate,
	Lvalue
};


typedef struct VarStruct
{
	char*  name;
	float value;
}VarStruct;
typedef VarStruct* VarPtr;

struct Element_s
{
	union
	{
		VarPtr var;
		enum Process proc;
		float value;
	};
	enum ItemType type;
};
typedef struct Element_s Element;

Element ElementVariable(char* name ,float val)
{
	Element e;
	e.type = ItemType::Variable;
	e.var = (VarPtr)malloc(sizeof(VarStruct));
	e.var->value = val;
	e.var->name = name;
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
	 return e.type == ItemType::Variable ? e.var->value : e.value;
}

void PrintElement(Element e)
{
	switch (e.type)
	{
	case Variable:
 		printf("[%s->%.1f]",e.var->name,  e.var->value);
		break;
	case Immediate:
		printf("(%.1f)", e.value);
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

int ParseString(char* str,  char** outStr,int maxLen)
{
	char* buffer = (char*)malloc(maxLen * sizeof(char));
	int index = 0;;
	while (isAlphabetic(str[index]) && index < (maxLen - 1))
	{
		buffer[index] = str[index];
		index++;
	}
	buffer[index] = 0;
	*outStr = buffer;
	return  index;
}

int ParseFloat(char* str, float *outValue)
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

	if (*str == ',' || *str == '.')
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
		advance += index + 1;

	}

	*outValue = val;
	return advance;
}

void printStack(const char* name, CStackElement stack)
{
	setColor(C_WHITE);
	printf(" %s : ", name);
	int i;
	for ( i = 0; i < stack.size; i++)
	{
		PrintElement(stack.data[i]);
		printf(" ");

	}
	printf("\n");
}

typedef struct
{
	const char* str;
	float* valAddr;
} VariablePair;

typedef struct
{
	int size;
	int capacity;
	VariablePair * data;
} CVectorVariable;

int elementcmp(Element lhs, Element rhs)
{
	char* s0, *s1;
	s0 = lhs.var->name;
	s1 = rhs.var->name;
	while ((*s0 && *s1)& (*s0 == *s1))
	{
		s1++;
		s0++;
	}

	return *s0 - *s1;
}

int elementcmp_n(  char* otherName , Element lhs)
{
	char* s0, *s1;
	s0 = otherName;
	s1 = lhs.var->name;
	while ((*s0 && *s1) & (*s0 == *s1))
	{
		s1++;
		s0++;
	}

	return *s0 - *s1;
}

typedef struct
{
	int size;
	int capacity;
	Element *data;
} CVectorElement;

int SolveFunction( CStackElement postFix , float *out)
{
	if(postFix.size > 1)
	printStack("PostFix", postFix);
	int flag = 1;

	CStackElement stack;
	VectorInit(stack);
	//initial control 
	if (postFix.data[0].type == Operator || postFix.size == 2)
	{
		setColor(C_RED);
		printf("! Cant resolve symbols\n");
		return 0;
	}
	int postFixIndex;
	for (postFixIndex = 0; postFixIndex < postFix.size; postFixIndex++)
	{
		Element e = postFix.data[postFixIndex];
		switch (e.type)
		{
		case Variable:
			StackPush(stack, e);
			break;
		case Immediate:
			StackPush(stack, e);
			break;
		case Operator:
		{
			Element rhE = StackPop(stack);
			Element lhE = StackPop(stack);
			if (rhE.type == Operator || lhE.type == Operator)
			{
				setColor(C_RED);
				printf("! Cant resolve symbols\n");
				return 0;
			}
			float b = ElementGetValue(rhE);
			float a = ElementGetValue(lhE);
			float res;

			if (e.proc == equality)
			{
				if (lhE.type != Variable)
				{
					setColor(C_RED);
					printf("! cant change immediate value\n");
					return 0;
				}
				lhE.var->value = b;

				 if(postFixIndex+1 < postFix.size && 
				 postFix.data[postFixIndex + 1].type == Operator && postFix.data[postFixIndex+1].proc == equality)
				 StackPush(stack, ElementImmediate(b));

				flag++;

			}else
			{ 
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
				case powProc:
					res = pow(a, b);
					break;
				case semicolon:
					StackClear(stack);
					res = 0;
					break;
				default:
					res = b;
					break;
				}
				StackPush(stack, ElementImmediate(res));
			}
		}
		break;
		default:
			break;
		}

	}

	*out = ElementGetValue(StackPop(stack));
	return flag;
}

void printWelcome()
{
	system("color");
	printf("\n ");
	setColors(C_MAGENTA, CB_WHITE);
	printf("Stack-Function Solver \n");
	setColors(C_GREEN, CB_BLACK);

	printf("\n Welcome the simple funciton solver - imlemented with using stack approach. \n You can use this command line like a aritmetic calculator \n plus you can define your own variables too. \n\n ");
	printf("Here some embedded commands;\n");
	setColor(C_CYAN);
	printf("-> clear:   clear  screen\n");
	printf("-> show :   prints all defined variables\n");
	printf("-> reset:   reset all defined variables\n");
	printf("-> help :   print this screen\n");
	printf("-> exit :   terminate the program\n");

	setColor(C_WHITE);
	printf("\n felbsn 2018\n\n");
	setColor(CB_BLACK);
}

int ParseFunction()
{

	printWelcome();

	CStackElement stack;
	CStackElement postFix;

	CVectorElement elements;
	CVectorChar bufferVec;

	StackInit(stack);
	StackInit(postFix);

	VectorInit(elements);
	VectorInit(bufferVec);



	
	while(1)
	{ 
	
	StackClear(postFix);
	setColor(C_CYAN);
	// get input string
	VectorGetLine(&bufferVec , 255);

	// here try to cath some functions such as clear and reset
	if (strcmp(bufferVec.data, "clear") == 0)
	{
		clear();
		continue;
	}else
		if (strcmp(bufferVec.data, "reset") == 0)
		{
			VectorClear(elements);
			continue;
		}else
			if (strcmp(bufferVec.data, "show") == 0)
			{
				int i;
				for ( i = 0; i < elements.size; i++)
				{
					printf(" ");
					setColors(CB_MAGENTA, C_WHITE);
					int elm = printf("{%s}", elements.data[i].var->name);
					setColors(C_WHITE, CB_BLACK);
					// some padding 
					while (20 - elm > 0) { elm++; printf("-"); }
					printf("-> ");
					setColor(C_GREEN);
					printf("%.3f \n", elements.data[i].var->value);
				}

				continue;
			}else
				if (strcmp(bufferVec.data, "help") == 0)
				{
					printWelcome();
					continue;
				}else
					if (strcmp(bufferVec.data, "exit") == 0)
					{
						exit(0);
					}

	// not necessary atm
	// trim all spaces in input string 
	//VectorTrim(bufferVec, ' ');
	

	char* buffer = bufferVec.data;
	int len = bufferVec.size;
	int index = 0;
	
	while (index < len)
	{
		if(buffer[index] == ' ')
		{
			//skip spaces
			index++;
		}else
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

				char* outstr;
				int advance = ParseString(&buffer[index], &outstr, 30);

				int ret;
				VectorBinarySearch(elements, outstr, ret, elementcmp_n);

				Element e;
				if (ret >= 0)
				{
					e = elements.data[ret];
				}
				else
				{
					e = ElementVariable(outstr, 0);
					VectorInsert(elements, e, elementcmp);
					
				}
				StackPush(postFix, e);
				index += advance;
			}
			else
			{
				// if char is a process symbol


				char c = buffer[index];
				Process proc = CharToProc(c);
				if (proc == undefined)
				{
					//abort the decoding proces
					setColor(C_RED);
					printf("! unable to solve funcion\n");
					StackClear(postFix);
					StackClear(stack);
					break;
				}
				if (proc == rhBracked)
				{
					Element e = StackPop(stack);

					while (e.type != ItemType::Operator || e.proc != lhBracked)//||  
					{
						StackPush(postFix, e);
						e = StackPop(stack);
					}

				}
				else
				{
					if (proc == lhBracked) {

					}
					else
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


	// solver process
	setColors(C_CYAN, CB_BLACK);
	if (!StackIsEmpty(postFix))
	{
			float result;
			int flag = SolveFunction(postFix , &result);
			if (flag == 1)
			{
				setColor(C_GREEN);
				printf(" = %.2f\n", result);
			}
		
	}

	}

	return 0;
}
