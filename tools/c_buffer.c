#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//enum{SUCCESS,FAIL};



void copy_to_permanent_storage(int dataToCopy, FILE *fptr1); //the function to store the messages permanently

void copy_to_permanent_storage(int dataToCopy, FILE *fptr1)
{
	fprintf(fptr1, "%d", dataToCopy);

}
