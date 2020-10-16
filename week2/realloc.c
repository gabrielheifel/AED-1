#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

   char *frase;
   int n;

   frase = (char*) malloc (30*sizeof(char));
   if(frase==NULL){
      printf("Falta de memoria!");
      exit(1);
   }

   printf("Digite uma string: ");
   fgets(frase, 50, stdin);
   printf("String informada: %s\n", frase);

   n = strlen(frase);
   printf("Tamanho da string: %d\n", n);

   memcpy(frase, frase, n);

   printf("String 'realocada': %s\n", frase);

   free(frase);
   printf("free\n");
}