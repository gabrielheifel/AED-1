// 8) Faça um programa que leia uma string (de 80 caracteres) chamada linha
// e, com uma função, identifique cada palavra (substring) desta linha
// copiando-a para um novo vetor. Ao final, o programa deve imprimir as
// palavras separadas, uma palavra por linha.
// Dicas: i) faça uma função para identificar o fim e/ou o início de cada substring em linha

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void separaString(char *linha, int n) {
   int i, j, cont=0;
   char *substring, nlinha[n], nsub[n];   //vetores [] são para facilitar no dbg

   for(i=0; i<n; i++){
      nlinha[i] = *(linha+i);
   }

   substring = (char*)malloc(n*sizeof(char));
   if(substring==NULL){
      printf("Erro memoria2\n");
      exit(1);
   }

   for(i=0; i<n; i++){
      if(*(linha+i) == ' ' || *(linha+i) == '\n'){     // encontra os espaços
         for(j=cont; j<=i; j++){
            if(*(linha+j) == ' '){
               *(substring+j) = '\n';     // substitui espaço por \n
               nsub[j] = '\n';
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