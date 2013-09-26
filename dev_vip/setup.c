#include <stdio.h>
#include <stdlib.h>
#include "settings.h"

int main(int argc, const char *argv[]){
   Settings * sob = calloc(sizeof(Settings),1); 
   FILE * fout = fopen("settings.bdat","wb");  
   //printf("Enter Streaming Mode: ");
   //scanf("%d",sob->streamingMode);
   sob->streamingMode = RT_STREAM;
   fwrite(sob, sizeof(Settings), 10,fout);
      
   return EXIT_SUCCESS;
}
