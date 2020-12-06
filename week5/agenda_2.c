#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "funcAgenda.h"

typedef struct contatos {
   char nome[30];
   char tel[20];
}Contato;

typedef struct variaveis {
   int op, cont, tambuffer, i, j, auxOrd;
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

   // ADD NO BUFFER
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
   strcpy(pContato->tel, "555555\n");
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

// MATRIZ
char** criaMatriz() {
   char **matriz;
   //vetor de string salva as informaçoes para ordena-las
   matriz = (char**)malloc(sizeof(char*)*var->cont);
   if(matriz==NULL){
      printf("memoria insuficiente\n");
      exit(1);
   }
   for(var->i=0; var->i<var->cont; (var->i)++){
      matriz[var->i] = (char*)malloc(sizeof(char)*20);
      if(matriz[var->i]==NULL){
         printf("memoria insuficiente\n");
         exit(1);
      }
   }

   return matriz;
}

void liberaMatriz(char **matriz){
   for(var->i=var->cont-1; var->i>=0; (var->i)--){
      free(matriz[var->i]);
   }
   free(matriz);
}

// FILA
Fila *RESET() {
   Fila *pFila;

   pFila = (Fila*) malloc (sizeof(Fila));

   pFila->pFirst = NULL;
   pFila->pLast = NULL;

   return pFila;
}

void CLEAR() {
   while(pFila->pFirst!=NULL){
      Nodo *auxDel = pFila->pFirst;
      pFila->pFirst = pFila->pFirst->pNext;
      free(auxDel);
   }
   free(pFila);
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

void imprimeFila() {
   Nodo *pNodo;

   if(pFila->pFirst == NULL){
      printf("Fila Vazia! Imprime\n");
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

   CLEAR();             //apaga a fila
   pFila = RESET();     //reinicia a fila
}

void ordenar(int formaOrd) {     //formaOrd == 1 ? alfabetica : numerica
   pContato = pBuffer + (sizeof(Variaveis));  //Contato aponta para o buffer
   
   char **matriz = criaMatriz();

   // Index vetor para ordenar os endereços das posições do contatos
   int *index = (int*)malloc(sizeof(int)*var->cont);
   if(index==NULL){
      printf("memoria insuficiente\n");
      return;
   }
   // Seta index e matriz que será ordenada
   for(var->i=0, var->j=0; var->i<var->cont; (var->i)++){
      index[var->i]=var->i;
      if(formaOrd==1){
         strcpy(matriz[var->i], pContato[var->i].nome);
      }else{
         strcpy(matriz[var->i], pContato[var->i].tel);

      }
   }
   
   // Ordenaçao insertionSort
   for(var->j=1; var->j<var->cont; (var->j)++){
      var->i=var->j-1;
      strcpy(var->auxNome, matriz[var->j]);
      // index[var->i] = var->j;

      //strcmp < 0 == string1 menor que string2
      while((var->i>=0) && ((strcmp(var->auxNome,matriz[var->i])) <0)){
         strcpy(matriz[var->i+1], matriz[var->i]);
         var->auxOrd = index[var->i+1];
         index[var->i+1] = index[var->i];
         index[var->i] = var->auxOrd;

         (var->i)--;
      }
      strcpy(matriz[var->i+1], var->auxNome);
   }

   // Passa os endereços dos valores ordenados para a fila
   for(var->i=0; var->i<var->cont; (var->i)++){
      printf("%d, ", index[var->i]);
      
      pContato = (Contato*) pContato+(index[var->i]); // contato no endereço ordenado
      PUSH(pContato);
      pContato = pBuffer + (sizeof(Variaveis));       // contato volta a apoontar para o buffer
   }
   printf("\n");

   free(index);
   liberaMatriz(matriz);
}

// MAIN
void menu() {

   while(var->op!=9){
      printf("\nDigite:\n");
      printf("1) Adicionar contato\n");
      printf("2) Apagar contato\n");
      printf("3) Listar contatos\n");
      printf("4) Ordenar ordem alfabetica\n");
      printf("5) Ordenar ordem numerica\n");
      printf("6) Imprime fila ordenada\n");
      printf("9) Sair\n");
      printf("Opcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addContato(); break;
         case 2: deletar(); break;
         case 3: list(); break;
         case 4: ordenar(1); break;
         case 5: ordenar(2); break;
         case 6: imprimeFila();
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

   CLEAR();
   free(pBuffer);
}