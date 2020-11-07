#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "funcAgenda.h"

typedef struct contatos {
   char nome[30];
   char tel[20];
}Contato;

typedef struct variaveis {
   int op, cont, tambuffer, i, j;
   char auxNome[30], auxTel[30];
   Contato *quit;      //ponteiro para contato
}Variaveis;

// Declaração dos ponteiros globais
void *pBuffer;
Contato *pContato;
Variaveis *var;

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

void insertionSort(int formaOrd) {     //formaOrd == 1 ? alfabetica : numerica
   pContato = pBuffer + (sizeof(Variaveis));  //Contato aponta para o buffer

   for(var->j=1; var->j<var->cont; (var->j)++){
      var->i = var->j-1;
      strcpy(var->auxNome, pContato[var->j].nome);
      strcpy(var->auxTel, pContato[var->j].tel);

      if(formaOrd == 1){
         //strcmp < 0 == string1 menor que string2
         while((var->i>=0) && ((strcmp(var->auxNome,pContato[var->i].nome)) <0)){
            strcpy(pContato[var->i+1].nome, pContato[var->i].nome);
            strcpy(pContato[var->i+1].tel, pContato[var->i].tel);

            (var->i)--;
         }
      }else{
         while((var->i>=0) && ((strcmp(var->auxTel,pContato[var->i].tel)) <0)){
            strcpy(pContato[var->i+1].nome, pContato[var->i].nome);
            strcpy(pContato[var->i+1].tel, pContato[var->i].tel);

            (var->i)--;
         }
      }

      strcpy(pContato[var->i+1].nome, var->auxNome);
      strcpy(pContato[var->i+1].tel, var->auxTel);
   }
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
      printf("Opcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addContato(); break;
         case 2: deletar(); break;
         case 3: list(); break;
         case 5: insertionSort(1); break;
         case 6: insertionSort(2); break;
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

   nomesDefault();

   menu();

   free(pBuffer);
}