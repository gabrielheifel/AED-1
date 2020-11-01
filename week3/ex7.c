// 7) Faça um programa que lê n números decimais (n fornecido pelo
// usuário), armazenando-os em um vetor. Logo após, uma função deve
// retirar os números duplicados que eventualmente possam existir neste
// vetor, deixando apenas uma ocorrência de cada número. Ao final, o vetor
// resultante deve ser impresso na tela.

#include <stdio.h>
#include <stdlib.h>

void tiraDup(int *vet, int n) {
   int i, j, k, aux;

   for(i=0; i<n; i++){
      aux = *(vet+i);
      for(j=i+1; j<n; j++){
         if(aux == *(vet+j)){
            for(k=j; k<n; k++){
               *(vet+k) = *(vet+(k+1));
            }
            n--;      //conta quantos numeros foram retirados
         }
      }
   }
   vet = (int*) realloc(vet, n * sizeof(int));

   for(i=0; i<n; i++){
      printf("%d", *(vet+i));
   }
   printf("\n");
}

int main() {
   int n, *vet, i;

   printf("Digite o valor de n: ");
   scanf("%d", &n);

   vet = (int*)malloc(n*sizeof(int));
   if(vet==NULL){
      printf("Falta de memoria\n");
      exit(1);
   }

   printf("Digite os números: ");
   for(i=0; i<n; i++){
      scanf("%d", vet+i);
   }

   tiraDup(vet, n);

   free(vet);
}