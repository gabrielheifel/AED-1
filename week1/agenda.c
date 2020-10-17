#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char nome[30];
   char tel[20];
}Contato;

typedef struct {
   int op, cont, tambuffer, i;
   char find[30];
   Contato *quit;      //ponteiro para contato
}Variaveis;

// Declaração dos ponteiros
void *pBuffer;
Contato *pContato;
Variaveis *var;

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

void delete() {
   printf("==== Remover contato ====\n");
   getchar();
   fgets(var->find, 30, stdin);

   pContato = pBuffer + (sizeof(Variaveis)); //Contato aponta para o buffer
   var->i = 0;    //contador para percorrer o buffer
   //verificar se exite o nome nos contatos
   while(strcmp(var->find, pContato->nome)!=0 && var->i < var->cont){
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
      pContato == pBuffer + (var->tambuffer - sizeof(Contato));

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

void menu() {

   while(var->op!=4){
      printf("\nDigite:\n");
      printf("1) Adicionar contato\n");
      printf("2) Apagar contato\n");
      printf("3) Listar contatos\n");
      printf("4) Sair\n");
      printf("Opcao: ");
      scanf("%d", &var->op);

      switch(var->op) {
         case 1: addContato(); break;
         case 2: delete(); break;
         case 3: list(); break;
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

   menu();

   free(pBuffer);
}