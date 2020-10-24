// Implementar em C um programa que utilize uma matriz com vetor de ponteiros
// e que ofereça as seguintes opções para o usuário:

// 1) Criar e redimencionar uma matriz m x n, onde n e m são fornecidos pelo usuário;
// 2) Realizar a leitura dos elementos da matriz;
// 3) Fornecer a soma dos elementos da matriz;
// 4) Retornar em um vetor (utilizando ponteiros) os elementos de uma determinada coluna da matriz;
// 5) Imprimir a matriz
// 6) Sair do programa

// Observações:
// 1) A matriz deve ser alocada dinamicamente no programa por meio do uso da função malloc.
// 2) O programa deve ser modularizado e utilizar os seguintes protótipos de subalgoritmos:

// a. int ** criaMatriz(int m, int n)
// b. void leiaMatriz(int **mat, int m, int n)
// c. int somaMatriz(int **mat, int m, int n) }
// d. int* colunaMatriz(int ** mat, int m, int n, int ncoluna)
// e. void liberaMatriz(int **mat, int ncoluna)
// f. void imprimeMatriz(int **mat, int m, int n)
// g. void imprimeVetor (int *vet, int n) { }

// 3) O subalgoritmo int* colunaMatriz(int ** mat, int m, int n, int ncoluna)  deve criar 
// um novo vetor (ponteiro para vetor) e retornar o mesmo para o programa principal que será responsável 
// pela impressão dos valores a partir da chamada de void imprimeVet (int *vet, int n) { }

#include <stdio.h>
#include <stdlib.h>

int** criaMatriz(int *m, int *n, int *flag) {
   int **mat, op, i;
   
   if(*flag==1) printf("\n\t=== Matriz ja foi criada! ===");
   printf("\n\tSelecione:\n");
   printf("\t1)Criar matriz\n");
   printf("\t2)Redimencionar matriz\n");
   printf("\tOpcao: ");
   scanf("%d", &op);

   if(op==1){
      if(*flag==1){
         printf("\n\tMatriz ja foi criada, tente redimenciona-la!\n");
      }else{
         //alocando linhas
         mat = (int **) malloc ((*m) * sizeof(int *));
         if(mat==NULL){
            printf("MEMORIA INSUFICIENTE\n");
            exit(1);
         }
         //alocando colunas
         for(i=0; i<(*m); i++){
            mat[i] = (int *) malloc ((*n) * sizeof(int));
            if(mat[i]==NULL){
               printf("MEMORIA INSUFICIENTE\n");
               exit(1);
            }
         }
         printf("\tMatriz criada!\n");
         *flag = 1;
      }
   }
   if(op==2){
      int aux = *m;     //aux para dar malloc em novos vetores
      //verifica se a matriz ja foi alocada
      if(*flag==1){
         printf("\tInformar novo numero de linhas: ");
         scanf("%d", &(*m));
         printf("\tInformar novo numero de colunas: ");
         scanf("%d", &(*n));
         //realoca vetor de vetores
         mat = (int **) realloc(mat, (*m) * sizeof(int *));
         if(mat==NULL){
            printf("MEMORIA INSUFICIENTE\n");
            exit(1);
         }
         for(i=0; i<(*m); i++){
            if(i<=aux){    //se o vetor da linha i já foi alocado
               mat[i] = (int *) realloc(mat[i], (*n) * sizeof(int));
               if(mat[i]==NULL){
                  printf("MEMORIA INSUFICIENTE\n");
                  exit(1);
               }
            }else{         //se o vetor da linha i ainda n foi alocado
               mat[i] = (int *) malloc((*n) * sizeof(int));
               if(mat[i]==NULL){
                  printf("MEMORIA INSUFICIENTE\n");
                  exit(1);
               }
            }
         }
         printf("\n\tMatriz redimencionada!\n");
      }else{
         printf("\n\tMatriz ainda nao foi criada! Crie primeiro.\n");
      }
   }
   return mat;
}

void leiaMatriz(int **mat, int m, int n) {
   int i, j;
   for(i=0; i<m; i++){
      for(j=0; j<n; j++){
         mat[i][j] = rand()%25;
      }
   }
   printf("\tMatriz preenchida com numeros aleatorios\n");
}

void imprimeMatriz(int **mat, int m, int n) {
   int i, j;
   printf("\n");
   for(i=0; i<m; i++){
      printf("\t");
      for(j=0; j<n; j++){
         printf("%d ", mat[i][j]);
      }
      printf("\n");
   }
}

// mudei a funcao para void porque nao seria necessario ter um return
void somaMatriz(int **mat, int m, int n) {
   int i, j, soma=0;
   for(i=0; i<m; i++){
      for(j=0; j<n; j++){
         soma += mat[i][j];
      }
   }
   printf("\n\tValores da matriz somados = %d\n", soma);
}

int* colunaMatriz(int **mat, int m, int n) {
   int *vet, i, ncoluna;

   printf("\n\tInforme o numero da coluna: ");
   scanf("%d", &ncoluna);

   vet = (int*) malloc (m * sizeof(int));
   if(vet==NULL){
      printf("MEMORIA INSUFICIENTE\n");
      exit(1);
   }
   for(i=0; i<m; i++){
      vet[i] = mat[i][ncoluna];
   }
   return vet;
}

void imprimeVetor(int *vet, int m) {
   int i;
   printf("\t");
   for(i=0; i<m; i++){
      printf("%d ", vet[i]);
   }
   printf("\n");
}

// libera matriz precisa das linhas ao invez das colunas
void liberaMatriz(int **mat, int m){
   int i;
   for(i=m-1; i>=0; i--){
      free(mat[i]);
   }
   free(mat);
}

int menu() {
   int op;

   printf("\n\tInforme a opcao:\n");
   printf("\t1) Criar ou Redimencionar Matriz\n");
   printf("\t2) Ler elementos da Matriz\n");
   printf("\t3) Soma dos elementos da Matriz\n");
   printf("\t4) Retorna elementos de uma coluna da Matriz\n");
   printf("\t5) Imprime Matriz\n");
   printf("\t6) Sair\n");
   printf("\tOpcao: ");
   scanf("%d", &op);

   return op;
}

int main() {
   // flag para ver se a matriz já foi alocada
   int m, n, op, flag, **mat, *vet;

   printf("Informar numero de linhas: ");
   scanf("%d", &m);
   printf("Informar numero de colunas: ");
   scanf("%d", &n);

   do{
      op = menu();
      switch(op) {
            case 1: mat = criaMatriz(&m, &n, &flag); break;
            case 2: leiaMatriz(mat, m, n); break;
            case 3: somaMatriz(mat, m, n); break;
            case 4: vet = colunaMatriz(mat, m, n); imprimeVetor(vet, m); break;
            case 5: imprimeMatriz(mat, m, n); break;
            default: break;
      }
   }while(op!=6);

   liberaMatriz(mat, m);

   free(vet);
}