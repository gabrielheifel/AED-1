#include <stdio.h>

int main() {

   int t, j=1, *p, *g;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   t = 5;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   p = &t;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   j = 3;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   g = &j;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   *p = (*g + j) * 2;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   *g = 4;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   g = p;
   printf("%d, %d, %p, %p\n", t, j, p, g);
   for(j=0; j<2; j++){
      *g = t*j + 1;
      printf("%d, %d, %p, %p\n", t, j, p, g);
   }
   *p = t + j + *g;
   printf("%d, %d, %p, %p\n", t, j, p, g);

}