#ifndef CVECTORUTILS_H
#define CVECTORUTILS_H

#include <stdio.h>
#include "CVectorTypedef.h"
#include "CVectorImp.h"


void VectorGetLine(CVectorChar *buffvec , int maxLen)
{
	VectorReserve(*buffvec, maxLen);
	printf(">");
	fgets(buffvec->data, maxLen, stdin);

	int len = 0;
	while (buffvec->data[len] != '\n') len++;
	buffvec->data[len] = 0;
	buffvec->size = len;
}





#endif // !CVECTORUTILS_H
