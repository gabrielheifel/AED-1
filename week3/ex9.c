// 9) Considere a função desenvolvida na Linguagem C, a seguir:
//    char *Teste (char *s1, const char *s2) {
//       char *aux=s1;
//       while (*s1) s1++;
//       for ( ; (*s1 = *s2) != ’\0’ ; s1++, s2++);
//       return aux;
//    }
// O seu objetivo é:
// a) Copiar o conteúdo da região de memória referenciada pelo identificador s1 para a
// região de memória referenciada pelo identificador s2.
// b) Atribuir o valor ‘\0’ para todas as posições de memória entre o endereço referenciado
// pelo identificador s1 até a região de memória referenciada pelo identificador s2.
// c) Comparar o conteúdo de memória que se inicia na posição referenciada pelo
// identificador s1 e ir até a ocorrência de um valor ‘\0’ com o conteúdo da região de
// memória referenciada pelo identificador s2.
// d) Substituir os elementos armazenados na região de memória referenciada pelo
// identificador s1 pelos elementos armazenados na região de memória referenciada pelo
// identificador s2.
// e) Copiar os elementos contidos na região de memória referenciada pelo identificador s2
// após os elementos armazenados na região de memória referenciada pelo identificador s1.

#include <stdio.h>
#include <stdlib.h>

