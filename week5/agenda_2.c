#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "funcAgenda.h"

typedef struct contatos {
   char nome[30];
   char tel[20];
}Contato;

typedef struct variaveis {
   int op, cont, tambuffer, i, j, index;
   char auxNome[30], auxTel[30];
   Contato *quit;      //ponteiro para contato
}Variaveis;

typedef struct nodo {
   Contato *info;
   struct nodo *pNext;
}Nodo;

typedef struct fila {
   Nodo *pFirst;
   Nodo *pLast;
}Fila;

// Declaração dos ponteiros globais
void *pBuffer;
Contato *pContato;
Variaveis *var;
Fila *pFila;

void addDefault() {

   var->cont += 1;        //contador para ver quantos contatos adicionados
   //Novo tambuffer com o numero dos contatos adicionados
   var->tambuffer = (sizeof(Variaveis)) + (var->cont*sizeof(Contato)); 
   pBuffer = realloc(pBuffer, var->tambuffer);     //realoca o novo tamanho
   if(pBuffer==NULL){
      printf("Memoria insuficiente!\n");
      exit(1);
   }
   var = pBuffer;          //variaveis aponta para o Buffer 
   //contato recebe nova posiçao de memoria do buffer + tamanho - 1 contato q vai ser adicionado
   pContato = pBuffer + (var->tambuffer - sizeof(Contato));    
}

void nomesDefault() {
   addDefault();
   strcpy(pContato->nome, "Heifel\n");
   strcpy(pContato->tel, "111111\n");

   addDefault();
   strcpy(pContato->nome, "Gabriel\n");
   strcpy(pContato->tel, "333333\n");

   addDefault();
   strcpy(pContato->nome, "Joao\n");
   strcpy(pContato->tel, "222222\n");

   addDefault();
   strcpy(pContato->nome, "Ana\n");
   strcpy(pContato->tel, "444444\n");
}

void addContato() {

   var->cont += 1;        //contador para ver quantos contatos adicionados
   //Novo tambuffer com o numero dos contatos adicionados
   var->tambuffer = (sizeof(Variaveis)) + (var->cont*sizeof(Contato)); 
   pBuffer = realloc(pBuffer, var->tambuffer);     //realoca o novo tamanho
   if(pBuffer==NULL){
      printf("Memoria insuficiente!\n");
      exit(1);
   }
   var = pBuffer;          //variaveis aponta para o Buffer 
   //contato recebe nova posiçao de memoria do buffer + tamanho - 1 contato q vai ser adicionado
   pContato = pBuffer + (var->tambuffer - sizeof(Contato));    
   
   getchar();
   printf("==== Novo contato ====\n");
   printf("Nome: ");
   fgets(pContato->nome, 30, stdin);
   printf("Telefone: ");
   fgets(pContato->tel, 20, stdin);   

   printf("Feito!\n");
}

void deletar() {
   printf("==== Remover contato ====\n");
   getchar();
   printf("Nome que deseja remover: ");
   fgets(var->auxNome, 30, stdin);

   pContato = pBuffer + (sizeof(Variaveis)); //Contato aponta para o buffer
   var->i = 0;    //contador para percorrer o buffer
   //verificar se exite o nome nos contatos
   while(strcmp(var->auxNome, pContato->nome)!=0 && var->i < var->cont){
      pContato = (Contato*) pContato+1;   //recebe endereço do prox contato
      var->i +=1;
   }
   if(var->i == var->cont){
      printf("Nome não existe na agenda.\n");
   }
   else{
      //verificar qual nome deve ser apagado
      //var ponteiro/contato aponta para o contato encontrado
      var->quit = (Contato*) pContato+1;

      //sobrescreve os contatos que estão depois do contato encontrado
      while(var->i < var->cont){
         strcpy(pContato->nome, var->quit->nome);         
         strcpy(pContato->tel, var->quit->tel);         
         pContato = (Contato*) pContato+1;
         var->quit = (Contato*) var->quit+1;
         var->i+=1;
      }
      //diminui o tamanho do buffer
      var->cont-=1;
      var->tambuffer = (sizeof(Variaveis)) + (var->cont * sizeof(Contato));
      pContato = pBuffer + (var->tambuffer - sizeof(Contato));

      printf("Contato removido!\n");
   }
}

void list() {
   printf("==== Listar contatos ====\n");
   pContato = pBuffer + (sizeof(Variaveis));

   for(var->i = 0; var->i < var->cont; (var->i)++){
      printf("=== Contato %d ===\n", var->i);
      printf("Nome: %s", pContato[var->i].nome);
      printf("Telefone: %s\n", pContato[var->i].tel);
   }
}

Fila *RESET() {
   Fila *pFila;

   pFila = (Fila*) malloc (sizeof(Fila));

   pFila->pFirst = NULL;
   pFila->pLast = NULL;

   return pFila;
}

void PUSH(Contato *pContato) {
   Nodo *pNovo;

   pNovo = (Nodo*) malloc (sizeof(Nodo));
   if(pNovo == NULL){
      printf("Erro memoria PUSH");
      return;
   }
   pNovo->info = pContato;
   pNovo->pNext = NULL;

   if(pFila->pLast != NULL)
      pFila->pLast->pNext = pNovo;
   else
      pFila->pFirst = pNovo;
   
   pFila->pLast = pNovo;
}

int POP(Contato *pContato) {
   Nodo *pNodo;

   if(pFila->pFirst == NULL){
      printf("Fila Vazia! POP\n");
      return 0;
   }
   else{
      pNodo = pFila->pFirst;
      pContato = pFila->pFirst->info;
      pFila->pFirst = pFila->pFirst->pNext;
   }

   if(pFila->pFirst == NULL)
      pFila->pLast = NULL;
   
   free(pNodo);
   return 1;
}

void imprimeFila() {
   Nodo *pNodo;

   if(pFila->pFirst == NULL){
      printf("Fila Vazia Imprime\n");
      return;
   }
   else{
      printf("==== Listar contatos ordenados ====\n");
      var->i=0;
      for(pNodo = pFila->pFirst; pNodo != NULL; pNodo = pNodo->pNext, (var->i)++){
         printf("=== Contato %d ===\n", var->i);
         printf("Nome: %s", pNodo->info->nome);
         printf("Telefone: %s\n", pNodo->info->tel);
      }
   }
}

void ordenar(int formaOrd) {     //formaOrd == 1 ? alfabetica : numerica
   pContato = pBuffer + (sizeof(Variaveis));  //Contato aponta para o buffer

   var->i = 0;
   if(formaOrd == 1){
      strcpy(var->auxNome, pContato[var->i].nome);

      //strcmp < 0 == string1 menor que string2
      for(var->i=0; var->i<=var->cont; (var->i)++){
         if((strcmp(var->auxNome, pContato[var->i].nome)) > 0){
            strcpy(var->auxNome, pContato[var->i].nome);
            var->index = var->i;    // index encontra a posição do menor valor
         }
      }
   }else{
      strcpy(var->auxTel, pContato[var->i].tel);

      for(var->i=0; var->i<=var->cont; (var->i)++){
         if((strcmp(var->auxTel, pContato[var->i].tel)) > 0){
            strcpy(var->auxTel, pContato[var->i].tel);
            var->index = var->i;
         }
      }
   }
   PUSH(pContato+var->index);
}

void Clear() {
   while(pFila->pFirst!=NULL){
      Nodo *auxDel = pFila->pFirst;
      pFila->pFirst = pFila->pFirst->pNext;
      free(auxDel);
   }
   free(pFila);
}

void menu() {

   while(var->op!=4){
      printf("\nDigite:\n");
      printf("1) Adicionar contato\n");
      printf("2) Apagar contato\n");
      printf("3) Listar contatos\n");
      printf("4) Sair\n");
      printf("5) Ordenar ordem alfabetica\n");
      printf("6) Ordenar ordem numerica\n");
      printf("7) Imprime fila ordenada\n");
      printf("Opcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addContato(); break;
         case 2: deletar(); break;
         case 3: list(); break;
         case 5: ordenar(1); break;
         case 6: ordenar(2); break;
         case 7: imprimeFila();
         default: break;
      }
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
   pFila = RESET();

   nomesDefault();

   menu();

   Clear();
   free(pBuffer);
}