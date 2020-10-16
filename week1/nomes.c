// Gabriel Heifel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nomes {
   char *name;
   int id;
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
   novoNome->id+=1;

   // free(novoNome);
}

void delete(Nomes *p) {
   printf("\n===== REMOVER NOME =====\n");

   Nomes *remove, *anterior;
   char *quit;
   int i = 0;

   quit = (char*) malloc (20*sizeof(char));

   printf("Nome a excluir: ");
   getchar();
   fgets(quit, 20, stdin);

   remove = p;
   anterior = p->prox;

   while((strcmp(anterior->name, quit)!=0)&&(i<anterior->id)){
      remove = anterior;
      anterior = anterior->prox;
      i++;
   }

   if(i == anterior->id){
      printf("Nome não exite no bd\n");
   }
   else{

      if(anterior != NULL){
         remove->prox = anterior->prox;
         free(anterior);
         printf("Nome deletado\n");
      }
   }

   free(quit);
}

void list(Nomes *p) {
   Nomes *x;

   for(x=p->prox; x!=NULL; x=x->prox){
      printf("Nome: %s", x->name);
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