/*
display the content of setting file, for demo purpose.
author:pat<ssabpisa@purdue.edu>
*/
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"

int main(int argc, const char *argv[]){
   FILE * j = fopen(argv[1], "rb");
   if(j == NULL){
      perror(argv[1]);
      return EXIT_FAILURE;
   }
  
   printf("\n====== Configuration (%s) =====\n\n",argv[1]);     
   int * n = malloc(sizeof(int) * 20);
   char * c = malloc(sizeof(char) * 20);
   fread(c, sizeof(char),20,j);
   fread(n,sizeof(int),20,j); 
   printf("Master Device (admin): %s\n",c);
   printf("Filter Allow: ");
   int i = 0;
   while(i<20){
     printf("%d ",n[i++]);
   }
   printf("\n");
   return EXIT_SUCCESS;

}
