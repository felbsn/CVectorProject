# CVectorProject

<h3>
Basic utility types , implement in pure c style
</h3>

This is a basic approach to create generic vector/list library in pure c.
However you noticed that 'pure c' contradicted my file extensions , and yes there is a problem but it is a compiler releated problem.

in gcc has typeof specifier already so you can build *.c files without any problem.

Where as it does not works with msvc compiler. Msvc dont have 'typeof' specifier where as my implement depends on a type specifier and 
decltype didnt works as i expect. So i figure out static_cas<delctype(x)> as a solution. 

<h2>Simple Structure</h2>

typedef struct <br>
{<br>
  int size;<br>
  int capacity;<br>
  YourDataType * data;<br>
} MyDaTaVector;<br>
<br>
all you need to do write your vector data structure.
after you can easily use all vector functions in your own defined data type

ex:
struct Foo
{
..
}
typedef Foo Foo; // here we need to define our struct as a new type in order to correctly run vectormaker...

CVectorCreateType(Foo , MyFooVector);

MyFooVector myVec = VectorCreate(myVec);
OR
MyFooVector myVec;
VectorInit(myVec);

... then

YourDataType element;
/*
some process
*/
VectorAppend(vec ,element )
/*
some process
*/
VectorSort(vec , YourDataTypeComparator);



