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

// a) A função é retorna a raiz de n.

// b) j = 100

// c)
#include <stdio.h>

int F1(unsigned int n) {
   if(n==0) return 0;
   int i, j=0, k;
   // for ( i = j = 1; i<2 *n-1 ; i+=2, j +=i);
   for(i=0; i<n; i++){
      for(k=0; k<n; k++){
         j++;
      }
   }
   // for(i=j=1; i<n; i++, j++){
   //    for(k=0; k<n; k++, j++);
   // }

   return j;
}

int main() {
   int n=4, j;
   
   j = F1(n);
   printf("j = %d\n", j);
}
