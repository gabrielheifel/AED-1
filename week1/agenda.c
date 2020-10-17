#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char nome[30];
   char telefone[20];
}Contato;

typedef struct {
   int cont, op, id, tambuffer;
}Variaveis;

// Declaração dos ponteiros
void *pBuffer;
Contato *pContato;
Variaveis *var;

void addContato() {
   Contato *newcontato;   //nova pessoa

   var->cont += 1;        //contador 
   var->tambuffer = (sizeof(Variaveis)) + (var->id*sizeof(Contato));
   pBuffer = realloc(pBuffer, var->tambuffer);
   if(pBuffer==NULL){
      printf("Memoria insuficiente!\n");
      exit(1);
   }
   var = pBuffer;
   newcontato = pBuffer + (var->tambuffer - sizeof(Contato));
   
   getchar();
   printf("Novo contato\n");
   printf("Nome: ");
   fgets(newcontato->nome, 30, stdin);
   printf("Telefone: ");
   fgets(newcontato->telefone, 20, stdin);   

   printf("Feito\n");
}

void menu() {

   for( ; ; ){
      printf("1) Adicionar contato\n");
      printf("2) Apagar contato\n");
      printf("3) Listar\n");
      printf("4) Sair\n");
      printf("Opcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addContato(); break;
         case 4: /*list();*/ exit(1);
         default: printf("Apenas 1 ou 4\n"); break;
      }
   }
}

int main() {
   
   pBuffer = malloc(sizeof(Variaveis))+sizeof(Contato);
   if(pBuffer==NULL){
      printf("Falta de memoria\n");
      exit(1);
   }
   var = pBuffer;
   var->cont = 0;

   menu();

   free(pBuffer);
}