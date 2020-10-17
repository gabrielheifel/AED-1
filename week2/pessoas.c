#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char nome[30];
   int idade;
   int altura;
}Pessoa;

typedef struct {
   int op, id, tambuffer;
   Pessoa *p;
}Variaveis;

void *pBuffer;
Pessoa *person;
Variaveis *var;

void addPessoa() {
   Pessoa *newperson;   //nova pessoa

   var->id += 1;        //contador 
   var->tambuffer = (sizeof(Variaveis)) + (var->id*sizeof(Pessoa));
   pBuffer = realloc(pBuffer, var->tambuffer);
   if(pBuffer==NULL){
      printf("Memoria insuficiente!\n");
      exit(1);
   }

   newperson = pBuffer + (var->tambuffer - sizeof(Pessoa));

   printf("Nome: ");
   fgets(newperson->nome, 30, stdin);
   printf("Idade: ");
   scanf("%d", &newperson->idade);
   printf("Altura: ");
   scanf("%d", &newperson->altura);
}

int main() {
   
   pBuffer = (Variaveis*) malloc(sizeof(Variaveis));
   if(pBuffer==NULL){
      printf("Falta de memoria\n");
      exit(1);
   }
   var = pBuffer;
   var->id = 0;

   for( ; ; ){
      printf("1) Adicionar pessoa\n4) Sair\nOpcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addPessoa(); break;
         case 4: /*list();*/ exit(1);
         default: printf("Apenas 1 ou 4\n"); break;
      }
   }

   free(pBuffer);
}