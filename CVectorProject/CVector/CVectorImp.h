#pragma once
#ifndef CVECTORIMP_H
#define CVECTORIMP_H
#include "CVectorTypedef.h"
#include <stdlib.h>
#include <stdio.h>



#ifdef _MSC_VER
#define TYPE_VAR(a) auto
#define TYPE_OF(a) static_cast<decltype(a)>
#else
#define TYPE_OF(a) (typeof(a))
#define TYPE_VAR(a) typeof(a)
#endif // _MSC_VER

#define VectorInit(vec)\
(vec).size = 0; \
(vec).capacity = 2; \
(vec).data = TYPE_OF((vec).data)(malloc(sizeof(*(vec).data) * 2));


#define VectorFree(vec)\
    {\
      vec.size = 0;\
      vec.capacity = 0;\
      free(vec.data);\
    }

#define VectorClear(vec)\
    {\
      vec.size = 0;\
    }

#define VectorContains(vec ,  val, comparator)\
{\
\
}

#define VectorAppend(vec , val){\
if ((vec).size >= (vec).capacity) {\
		(vec).capacity *= (int) ((vec).capacity*1.5f); \
		(vec).data = TYPE_OF((vec).data) ( realloc((vec).data, (sizeof(*(vec).data))*(vec).capacity));\
	}\
(vec).data[(vec).size] = (val);\
(vec).size++;\
}

#define VectorInsert( vec,  val, comparator) {\
if ((vec).size >= (vec).capacity) {\
			\
				(vec).capacity *= (int)((vec).capacity*1.5f); \
				(vec).data = TYPE_OF((vec).data) (realloc((vec).data, (sizeof(*(vec).data))*(vec).capacity)); \
		}\
			int i = 0;\
			while (i < (vec).size && comparator( val , (vec).data[i]) >= 0) { i++; }\
			\
			int j; \
			for (j = (vec).size; j > i; j--)\
			{\
				(vec).data[j] = (vec).data[j - 1];\
			}\
			(vec).size++;\
			(vec).data[i] = val;\
}


#define VectorSort(vec  , functor )\
do{\
     int i;\
      for (i = 0; i < (vec).size; i++){\
      TYPE_VAR(*(vec).data) cur = (vec).data[i];\
       int j = i-1;\
       while (j >= 0 && (functor((vec).data[j] ,cur) ) > 0) \
       {\
           (vec).data[j+1] = (vec).data[j];\
           j = j-1;\
       }\
       (vec).data[j+1] = cur;\
      }\
   }while(0,0)

#define VectorBubleSort(vec , comparator){\
	int i = 0, j = 0 ;\
	for (i = 0; i < (vec).size -1; i++)\
		for (j = 0; j < (vec).size - i - 1; j++)\
			if ( comparator((vec).data[j]  ,(vec).data[j + 1]) >= 0    ){\
				auto tmp = (vec).data[j];\
				(vec).data[j] = (vec).data[j + 1];\
				(vec).data[j + 1] = tmp;\
			}\
		}




#define VectorBinarySearch(vec , value, retIndex , comparator)\
{ \
	int left = 0 , right = (vec).size - 1; \
	int curIndex; \
	retIndex = -1; \
	while (retIndex < 0 && (right >= left))\
	{\
		curIndex = (right + left) / 2; \
		int res = comparator(value  ,  (vec).data[curIndex]); \
		if (res == 0) { retIndex = curIndex; }\
		else\
			if (res > 0)\
			{left = curIndex + 1; }\
			else\
			{right = curIndex - 1; }\
	}; \
}

#define VectorGetCount(vec ,value ,  outVariable){\
	int _i = 0;\
    outVariable = 0;\
	for (; _i < (vec).size; _i++)\
	{\
	if ( (vec).data[_i] == value) outVariable++;\
	}\
}

#define VectorReplace(vec , value , repVal){\
	int i = 0;\
	for (; i < (vec).size; i++)\
	{\
		if ((vec).data[i] == value) {\
			(vec).data[i] = repVal;\
		}\
	}\
}

#define VectorLinearSearchF(vec , value, retIndex , comparator)\
{ \
 int _i = 0;\
while ((_i < (vec).size) && (comparator(value ,(vec).data[_i]) ) != 0) {\
	_i++;\
	}\
if ((_i < (vec).size)) retIndex = _i;\
else\
					 retIndex = -1;\
}


#define VectorLinearSearch(vec , value, retIndex)\
{ \
 int _i = 0;\
while ((_i < (vec).size) && (value != (vec).data[_i])) {\
	_i++;\
	}\
if ((_i < (vec).size)) retIndex = _i;\
else\
					 retIndex = -1;\
}

#define VectorDeleteFS(vec , index )({ \
(vec).data[index] = (vec).data[(vec).size - 1]; \
(vec).size--; }) \


#define VectorDelete(vec , index )\
	{\
    int i;\
	for (i = index; i < vec.size-1; i++) {\
	(vec).data[i] = (vec).data[i + 1];\
	}\
	(vec).size--;\
  }




#define VectorTrim(vec , val)\
	{\
		int i, j = 0;\
		while (j < (vec).size && (vec).data[j] != val) { j++; }\
		if (j < (vec).size)\
		{\
			int passCount = 1;\
			for (i = j; i< vec.size; i++) {\
				int k = passCount + i;\
				while (k < vec.size - 1 && (vec).data[k] == val)\
				{\
					k++;\
					passCount++;\
				}\
				(vec).data[i] = (vec).data[k];\
			}\
			if((vec).data[(vec).size-1] == val )\
			(vec).size--;   \
			(vec).size -= passCount; \
		}\
	}\

#define VectorAppendVec( vec ,  vecOther)\
{\
	if ((vec).capacity - (vecOther).size < 0)\
	{\
		(vec).capacity += (vecOther).size; \
		(vec).data = TYPE_OF((vec).data) (realloc((vec).data, (sizeof(*(vec).data))*(vec).capacity)); \
	}\
	int  i , j = (vec).size;\
	for ( i = 0; i < (vecOther).size; i++)\
	{\
		(vec).data[j] = (vecOther).data[i];\
		j++;\
	}\
(vec).size +=(vecOther).size; \
}\

#define VectorReserve( vec,newSize){\
      if(newSize > (vec).size) \
      { \
        (vec).data = TYPE_OF((vec).data) (realloc((vec).data ,newSize*sizeof(*(vec).data))); \
        (vec).capacity = newSize; \
      } \
    }

#define VectorResize( vec,newSize){\
      if(newSize > 2) \
      { \
        (vec).data = TYPE_OF((vec).data) (realloc((vec).data ,newSize*sizeof(*(vec).data))); \
        (vec).capacity = newSize; \
        (vec).size = newSize;\
      } \
    }


#define VectorFill(vec  ,value){\
	int i = 0;\
	for (; i < (vec).size; i++)\
	(vec).data[i] = value;\
}



#define VectorShrink(vec){\
    if((vec).size <= 2){ \
      (vec).capacity = 2; \
      (vec).data = TYPE_OF((vec).data)(realloc((vec).data ,sizeof(*(vec).data)* (vec).capacity));\
    }\
  }



#endif // !CVECTORIMP_H

