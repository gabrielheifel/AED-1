#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
   char nome[30];
   int idade;
}Pessoas;

typedef struct {
   Pessoas *pessoa;
   Pessoas *topo;
   Pessoas *base;
   int limite;
}Pilha;

void Reset(Pilha *pilha) {
   pilha->pessoa = NULL;
   pilha->topo = NULL;
   pilha->base = NULL;
   pilha->limite = 0;      // Pilha limite = contador de quantas pessoa tem
}

bool Empty(Pilha *pilha) {
   return pilha->pessoa == NULL;
}

bool Full(Pilha *pilha) {
   return false;
}

bool PUSH(Pilha *pilha, Pessoas *item) {
   Pessoas *pessoa;

   pilha->limite++;
   pessoa = (Pessoas*)malloc(sizeof(Pessoas)*pilha->limite);
   if(!pessoa){  // Se for NULL
      printf("Erro alocando memoria");
      return;
   }

   

}

int menu() {
   int op;
   printf("\nEscolha:");
   printf("\n - 0: Insere pessoa");
   printf("\n - 1: Deleta pessoa do topo");
   printf("\n - 2: Deleta pessoa por nome");
   printf("\n - 3: Limpa pilha");
   printf("\n - 4: Lista na tela as pessoa");
   printf("\n - 5: Sair do programa");
   scanf("%d", &op);
   return op;
}

int main() {
   int op;

   do{
      op = menu();
      switch(op){
         case 0: break;
         case 1: break;
         case 2: break;
         case 3: break;
         case 4: break;
         default: break;
      }
   }while(op!=5);
}