// Gabriel Heifel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nomes {
   char *name;
   struct nomes *prox;
}Nomes;


Nomes* create_string() {
   Nomes *inicio;

   inicio = (Nomes*)malloc(sizeof(Nomes));
   inicio->prox = NULL;

   printf("string criada\n");
   return inicio;
}

void add(Nomes *p) {
   printf("\n===== ADICIONAR NOME =====\n");
   
   Nomes *novoNome;

   novoNome = (Nomes*) malloc (sizeof(Nomes));
   if(novoNome==NULL){
      printf("Memória insuficiente\n");
      exit(1);
   }

   novoNome->name = (char*) malloc (20*sizeof(char));
   
   printf("Novo nome: ");
   getchar();
   fgets(novoNome->name, 20, stdin);

   novoNome->prox = p->prox;
   p->prox = novoNome;

   // free(novoNome);
}

void delete(Nomes *p) {
   printf("\n===== REMOVER NOME =====\n");

   Nomes *remove, *anterior;
   char *quit;
   // int *flag;

   quit = (char*) malloc (20*sizeof(char));
   // flag = (int*) malloc (sizeof(int));

   printf("Nome a excluir: ");
   getchar();
   fgets(quit, 20, stdin);

   remove = p;
   anterior = p->prox;
   // flag = 0;

   while((remove!=NULL)&&(strcmp(anterior->name, quit)!=0)){
      remove = anterior;
      anterior = anterior->prox;
   }

   if(anterior != NULL){
      remove->prox = anterior->prox;
      free(anterior);
      printf("Nome deletado\n");
   }
}

void list(Nomes *p) {
   Nomes *x;

   if(p == NULL){
      printf("Vazio\n");
      return;
   }

   for(x=p->prox; x!=NULL; x=x->prox){
      printf("Nome: ", x->name);
      printf("\n");
   }
}

int menu(Nomes *p) {
   int *opcao;

   opcao = (int*)malloc(sizeof(int));

   for( ; ; ){
      printf("\n");
      printf("1) Adicionar nome\n");
      printf("2) Remover nome\n");
      printf("3) Listar\n");
      printf("4) Sair\n");
      printf("Opcao: ");

      scanf("%d", opcao);
   
      switch (*opcao) {
         case 1: add(p); break;
         case 2: delete(p); break;
         case 3: list(p); break;
         case 4: exit(1);
         default: printf("Apenas numeros entre 1 - 4."); break;
      }
   }

   free(opcao);
}

int main() {

   Nomes *p;
   p = create_string();
   
   menu(p);

   free(p);

   return 0;
}