// 8) Faça um programa que leia uma string (de 80 caracteres) chamada linha
// e, com uma função, identifique cada palavra (substring) desta linha
// copiando-a para um novo vetor. Ao final, o programa deve imprimir as
// palavras separadas, uma palavra por linha.
// Dicas: i) faça uma função para identificar o fim e/ou o início de cada substring em linha

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** criaNewString(int *tamString, int countString) {
   char **matrizString;

   //aloca novos espaços para por as strings
   matrizString = (char**)malloc(countString*sizeof(char*));
   if(matrizString==NULL){
      printf("Erro memoria4\n");
      exit(1);
   }
   for(i=0; i<countString; i++){
      matrizString[i] = (char*)malloc((*tamString+i)*sizeof(char));
      if(matrizString[i]==NULL){
         printf("Erro memoria5\n");
         exit(1);
      }
   }

   return matrizString;
}

void separaString(char *linha, int n) {

   int i, j, k, cont=0, countString=0, *tamString;       // countString para contar quantas string tem
   char **matrizString, *substring, nlinha[n], nsub[n];   //vetores [] são para facilitar no dbg

   for(i=0; i<n; i++){
      nlinha[i] = *(linha+i);
   }

   substring = (char*)malloc(n*sizeof(char));
   if(substring==NULL){
      printf("Erro memoria2\n");
      exit(1);
   }

   tamString = (int*)malloc(countString*sizeof(int));
   if(tamString==NULL){
      printf("Erro memoria3\n");
      exit(1);
   }

   matrizString = criaNewString(countString, tamString);

   for(i=0; i<n; i++){
      if(*(linha+i) == ' ' || *(linha+i) == '\n'){     // encontra os espaços
         for(j=cont; j<=i; j++){
            if(*(linha+j) == ' '){
               *(substring+j) = '\n';     // substitui espaço por \n
               nsub[j] = '\n';

               countString++;
               tamString[countString] = strlen(*substring);

               tamString = (int*)realloc(tamString, countString);
               if(tamString==NULL){
                  printf("Erro memoria6\n");
                  exit(1);
               }

               matrizString = (char**)realloc(matrizString, countString);
               if(matrizString==NULL){
                  printf("Erro memoria7\n");
                  exit(1);
               }
               matrizString[countString] = (char*)malloc(*(tamString+countString)*sizeof(char));
               if(matrizString[countString]==NULL){
                  printf("Erro memoria8\n");
                  exit(1);
               }

            }
            else{
               *(substring+j) = *(linha+j);  //copia do inicio da palavra ate espaço
               nsub[j] = nlinha[j];
            }
         }
         cont=j;         
      }
   }

   

   for(i=0; i<n; i++){
      printf("%c", *(substring+i));
   }
   printf("\n");
   
   free(substring);
   free(tamString);
   for(i=0; i<countString; i++){
      free(matrizString[i]);
   }
   free(matrizString);

}

int main() {
   int n;
   char *linha;

   linha = (char*)malloc(80*sizeof(char));
   if(linha==NULL){
      printf("Erro memoria\n");
      exit(1);
   }

   printf("Digite uma frase: ");
   fgets(linha, 80, stdin);

   n = strlen(linha);

   separaString(linha, n);

   free(linha);
}