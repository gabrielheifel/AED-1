#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char nome[30];
   int idade;
   int altura;
}Pessoa;

typedef struct {
   int cont, tambuffer;
   Pessoa *p;      //ponteiro para pessoa
}Variaveis;

// Declaração dos ponteiros
void *pBuffer;
Pessoa *pPessoa;
Variaveis *var;

void addPessoa() {

   var->cont += 1;        //contador para ver quantos pessoa adicionados
   //Novo tambuffer com o numero de pessoa adicionados
   var->tambuffer = (sizeof(Variaveis)) + (var->cont*sizeof(Pessoa)); 
   pBuffer = realloc(pBuffer, var->tambuffer);     //realoca o novo tamanho
   if(pBuffer==NULL){
      printf("Memoria insuficiente!\n");
      exit(1);
   }
   var = pBuffer;          //variaveis aponta para o Buffer 
   //contato recebe nova posiçao de memoria do buffer + tamanho - 1 contato q vai ser adicionado
   pPessoa = pBuffer + (var->tambuffer - sizeof(Pessoa));    
   
   getchar();
   printf("==== Nova Pessoa ====\n");
   printf("Nome: ");
   fgets(pPessoa->nome, 30, stdin);
   printf("Idade: ");
   scanf("%d", &pPessoa->idade);
   printf("Altura: ");
   scanf("%d", &pPessoa->altura);   

   printf("Feito!\n");
}

void list() {
   printf("==== Listar pessoas ====\n");
   pPessoa = pBuffer + (sizeof(Variaveis));

   for(int i = 0; i < var->cont; i++){
      printf("=== Pessoa %d ===\n", i);
      printf("Nome: %s", pPessoa[i].nome);
      printf("Idade: %d\n", pPessoa[i].idade);
      printf("Altura: %d\n", pPessoa[i].altura);
   }
}

int main() {
   
   pBuffer = malloc(sizeof(Variaveis));
   if(pBuffer==NULL){
      printf("Falta de memoria\n");
      exit(1);
   }
   var = pBuffer;
   var->cont = 0;
   int op;

   while(op!=4){
      printf("\nDigite:\n");
      printf("1) Adicionar pessoa\n");
      printf("4) Sair\n");
      printf("Opcao: ");
      scanf("%d", &op);

      if(op==1){
         addPessoa();
      }else{
         break;
      }
   }

   list();
   printf("\n");
   free(pBuffer);
}