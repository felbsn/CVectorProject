#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include "Examples/FunctionSolver.h"

int main(int argc, char ** argv)
{
	

	while (1)
	{
		char *str = 0;
		if (argc > 1)
		{
			FILE *fi = fopen(argv[1], "r");


			if (fi)
			{
				str = (char*)malloc(sizeof(char) * 1024);
				*str = 0;
				while (!feof(fi))
				{
					char lineBuffer[256];
					fgets(lineBuffer, 255, fi);
					strcat(str, lineBuffer);

				}
			}
			else
			{
				printf("Cannot open file !");
			}
		}
		else
		{
			printf("-> You have to pass file name as an argument to process file...\n");
			
		}
		SolverRoutine(str);
		
		system("pause");
	}
}

