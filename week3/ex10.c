// 10) Considere a função desenvolvida na Linguagem C.
//    int F1 ( unsigned int n)
//    {
//       if(n==0) return n;
//       int i , j;
//       for ( i = j = 1; i<2 *n-1 ; i+=2, j +=i);
//       return j;
//    }
// a) Explique esta função;
// b) Calcule o valor de j para o valor de entrada n = 10;
// c) Implemente uma função similar utilizando 2 loops for;

// a) A função é um contador, retorna o valor de j, que 
//    é o mesmo valor de n, caso o n seja diferente de 0.
//    E i é o dobro de j menos 1.

// b) j = 10

// c)
#include <stdio.h>

int F1(unsigned int n) {
   if(n==0) return 0;
   int i, j;
   for(i=1; i<2 *n-1; i+=2);
   for(j=1; j<n; j+=1);
   printf("i = %d | ", i);
   return j;
}

int main() {
   int n=10, j;
   
   j = F1(n);
   printf("j = %d\n", j);
}