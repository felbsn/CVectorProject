#pragma once
#ifndef CSTACKTYPEDEF_H
#define CSTACKTYPEDEF_H



typedef struct CStackInt_s
{
	int size;
	int capacity;
	int *data;

} CStackInt;

typedef struct CStackChar_s
{
	int size;
	int capacity;
	char *data;
}  CStackChar;





#endif // !CSTACKTYPEDEF_H
