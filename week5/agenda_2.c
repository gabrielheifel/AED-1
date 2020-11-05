#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcAgenda.h"

int main() {
   
   pBuffer = malloc(sizeof(Variaveis));
   if(pBuffer==NULL){
      printf("Falta de memoria\n");
      exit(1);
   }
   var = pBuffer;
   var->cont = 0;

   menu();

   free(pBuffer);
}