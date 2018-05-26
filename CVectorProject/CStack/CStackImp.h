#pragma once
#ifndef CSTACKIMP_H
#define CSTACKIMP_H
#include "CStackTypedef.h"
#include <stdlib.h>
#include <stdio.h>



#ifdef _MSC_VER
#define TYPE_VAR(a) auto
#define TYPE_OF(a) static_cast<decltype(a)>
#else
#define TYPE_OF(a) (typeof(a))
#define TYPE_VAR(a) typeof(a)
#endif // _MSC_VER

#define StackInit(stack)\
(stack).size = 0; \
(stack).capacity = 2; \
(stack).data = TYPE_OF((vec).data)(malloc(sizeof(*(stack).data) * 2));


#define StackFree(stack)\
    {\
      (stack).size = 0;\
      (stack).capacity = 0;\
      free((stack).data);\
    }

#define StackClear(stack)\
    {\
      (stack).size = 0;\
    }


#define StackPush(stack , val){\
if ((stack).size >= (stack).capacity) {\
		(stack).capacity *= (int) ((stack).capacity*1.5f); \
		(stack).data = TYPE_OF((stack).data) ( realloc((stack).data, (sizeof(*(stack).data))*(stack).capacity));\
	}\
(stack).data[(stack).size] = (val);\
(stack).size++;\
}

#define StackPop(stack , valPtr){\
if((stack).size > 0)\
{\
	(stack).size--;\
	*valPtr = (stack).data[(stack).size];\
}}


#define StackIsEmpty(stack) ((stack).size <= 0 )

 
 

#define StackReplace(stack , value , repVal){\
	int i = 0;\
	for (; i < (stack).size; i++)\
	{\
		if ((stack).data[i] == value) {\
			(stack).data[i] = repVal;\
		}\
	}\
}

 
#define StackLinearSearch(stack , value, retIndex)\
{ \
 int _i = 0;\
while ((_i < (stack).size) && (value != (stack).data[_i])) {\
	_i++;\
	}\
if ((_i < (stack).size)) retIndex = _i;\
else\
					 retIndex = -1;\
}

#define StackDeleteFS(stack , index )({ \
(stack).data[index] = (stack).data[(stack).size - 1]; \
(stack).size--; }) \


#define StackDelete(stack , index )\
	{\
    int i;\
    for( i = (stack).size-1;  i > index   ; i--){\
      (stack).data[i-1] = (stack).data[i];\
    }\
    (stack).size--;\
  }

#define StackReserve( stack,newSize){\
      if(newSize > (stack).size) \
      { \
        (stack).data = typeof((stack).data) (realloc((stack).data ,newSize*sizeof(*(stack).data))); \
        (stack).capacity = newSize; \
      } \
    }

#define StackResize( stack,newSize){\
      if(newSize > 2) \
      { \
        (stack).data = TYPE_OF((stack).data) (realloc((stack).data ,newSize*sizeof(*(stack).data))); \
        (stack).capacity = newSize; \
        (stack).size = newSize;\
      } \
    }


#define StackFill(stack  ,value){\
	int i = 0;\
	for (; i < (stack).size; i++)\
	(stack).data[i] = value;\
}



#define StackShrink(stack){\
    if((stack).size <= 2){ \
      (stack).capacity = 2; \
      (stack).data = TYPE_OF((stack).data)(realloc((stack).data ,sizeof(*(stack).data)* (stack).capacity));\
    }\
  }



#endif // !CSTACKIMP_H

