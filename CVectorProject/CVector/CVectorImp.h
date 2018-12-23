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

#define CVectorCreateType(TYPE ,NAME)\
typedef struct\
{\
	int size;\
	int capacity;\
	TYPE *data;\
\
} NAME;

#define VectorInit(vec)\
(vec).size = 0; \
(vec).capacity = 2; \
(vec).data = TYPE_OF((vec).data)(malloc(sizeof(*(vec).data) * 2));

#define VectorCreate(vec)\
{0 ,2 ,  TYPE_OF((vec).data)(malloc(sizeof(*(vec).data) * 2)) } 

#define VectorFree(vec)\
    {\
      vec.size = 0;\
      vec.capacity = 0;\
      if(vec.data)free(vec.data);\
    }

#define VectorInitAs(vec , beginSize){\
int _beginSize = beginSize >= 2 ? beginSize : 2;\
(vec).size = 0; \
(vec).capacity = _beginSize; \
(vec).data = TYPE_OF((vec).data)(malloc(sizeof(*(vec).data) * _beginSize));\
}

#define Get(x) data[x]

#define VectorClear(vec)\
    {\
      vec.size = 0;\
    }
#define VectorTop(vec) (vec).data[vec.size-1]

#define VectorPop(vec) (vec).data[(vec).size -= 1]


#define VectorAppend(vec , val){\
if ((vec).size >= (vec).capacity) {\
		(vec).capacity *= (int) ((vec).capacity*1.5f); \
		(vec).data = TYPE_OF((vec).data) ( realloc((vec).data, (sizeof(*(vec).data))*(vec).capacity));\
	}\
(vec).data[(vec).size] = (val);\
(vec).size++;\
}

#define VectorInsert( vec,  value, comparator) {\
if ((vec).size >= (vec).capacity) {\
			\
				(vec).capacity *= (int)((vec).capacity*1.5f); \
				(vec).data = TYPE_OF((vec).data) (realloc((vec).data, (sizeof(*(vec).data))*(vec).capacity)); \
		}\
			TYPE_VAR(*(vec).data) val = value;\
			int _i = 0;\
			while (_i < (vec).size && comparator( val , (vec).data[_i]) == 0) { _i++; }\
			int _j; \
			for (_j = (vec).size; _j > _i; _j--)\
			{\
				(vec).data[_j] = (vec).data[_j - 1];\
			}\
			(vec).size++;\
			(vec).data[_i] = val;\
}


#define VectorSort(vec  , functor )\
do{\
     int i;\
      for (i = 0; i < (vec).size; i++){\
      TYPE_VAR(*(vec).data) cur = (vec).data[i];\
       int j = i-1;\
       while (j >= 0 && (functor((vec).data[j] ,cur) ) <= 0) \
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


#define VectorContainsF(vec ,  val, comparator, out)\
{int _i = 0;\
out = 0;\
while( _i < (vec).size && out == 0 ){\
out = comp((vec).data[_i] , val); _i++;}\
}

#define VectorContains(vec , val, out)\
{int _i = 0;\
out = 0;\
while( _i < (vec).size && out == 0 ){\
if((vec).data[_i] == val) out++; \
_i++;}\
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

#define VectorDeleteF(vec , index  ,destructor)\
	{\
    int i;\
	for (i = index; i < vec.size-1; i++) {\
	(vec).data[i] = (vec).data[i + 1];\
	}\
	(vec).size--;\
  }

#define VectorEnquene(vec) \
	(vec).data[0];\
	VectorDelete(vec , 0);
 


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
      } \
	  if(newSize >= 0) (vec).size = newSize;	\
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


#define VectorClone(vec , out)\
{\
VectorInitAs(out ,(vec).size);\
(out).size = (vec).size;\
memcpy( (out).data , (vec).data , sizeof((*(vec).data) * (vec).size ));\
}




#endif // !CVECTORIMP_H

