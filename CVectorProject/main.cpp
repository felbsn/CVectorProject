
#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include "CVector/CVector.h"
#include "CStack/CStack.h"




int main(int argc, char ** argv)
{
	
	CVectorInt vec;
	CStackInt stack;

	StackInit(stack);
	VectorInit(vec);

	StackPush(stack, 1);
	StackPush(stack, 2);
	StackPush(stack, 3);
	StackPush(stack, 4);
	StackPush(stack, 5);

	VectorAppend(vec, 30);
	VectorAppend(vec, 13);
	VectorAppend(vec, 3434);

	VectorAppend(vec, 23);


	for (size_t i = 0; i < vec.size; i++)
	{
		printf("%5d ", vec.data[i]);
	}

 
 
	while(!StackIsEmpty(stack))
	{
		int a = 0;
		StackPop(stack, &a);
		printf("out stack %d \n", a);


	}



	int temp;
	scanf("%d", &temp);
	return 0;
}