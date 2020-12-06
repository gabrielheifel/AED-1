#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

/* programa para ilustrar a inserção e exclusão de uma lista vinculada
 usando a técnica "triple ref" que foi redescoberta em Algol 68 cerca de 40
anos atrás, tendo (supostamente) sido conhecido por programadores assembler desde o
amanhecer ...
 
Observe que "tracer" tem um tipo de conteúdo de "ref ref THING" em Algol 68, ou
`THING ** 'em C, o que significa que a localização da memória do próprio" rastreador "
é um `ref 'superior, ou seja," ref ref ref THING "em A68, ou" THING *** "em C.
Portanto, é fácil entender por que essas técnicas se tornaram conhecidas como `tripleref '

Como o próprio nome indica, `tracer 'é usado para localizar um local na lista. E,
usando elenco, para desreferenciá-lo individual ou duplamente, pode-se inspecionar o
conteúdo do elemento atual ou do próximo elemento.

O bom é que embora as rotinas InsertThing e RemoveThing usando
esta técnica geralmente lidará com algo no meio de uma lista
mas as rotinas também são robustas contra os seguintes casos especiais;
 
1) inserir / excluir de / para uma lista nula
2) inserir / excluir de / para uma lista de um único membro
3) inserir / deletar no final de uma lista
4) inserir / excluir no início de uma lista

Todos os itens acima ocorrem sem a necessidade de codificação adicional de 'caso especial'. O oportuno
a detecção de NULL e a atualização (se necessário) do ponteiro para o início da lista acontecem
de forma totalmente automática.

O uso é feito, nas rotinas abaixo, da abreviação comum C de `while (* tracer) 'em vez de
o mais geral `while (* tracer! = NULL) '. Mas fique claro que este atalho depende de
os valores booleanos são representados como 0 e 1 e o ponteiro NULL como 0. É possível imaginar
implementações exóticas de C onde este pode não ser o caso.

NOTA CUIDADOSAMENTE: este é um exemplo de tutorial. A inserção e exclusão
as rotinas foram deliberadamente construídas de modo a entregar o `vazio '. Isso é para
ilustrar que eles não precisam entregar um resultado THING * formal para fins de
atualizando o cabeçalho da lista (digamos).

Em vez disso, o conteúdo do parâmetro formal de entrada chamado `cabeça '
aponta para a variável global `start 'nestes exemplos. O efeito é que o conteúdo de
 `start 'é atualizado, automaticamente e corretamente, em todos
casos especiais em que ocorre "inserir na frente da lista". Sua reação
a esse comportamento pode variar de "Isso é legal!" para "Isso é terrível!".

Portanto, NÃO é necessário que as rotinas devolvam um tradicional
THING * aponta para o novo cabeçalho da lista - para permitir que a atualização seja feita
manualmente em uma operação separada. No entanto, é fácil alterar o
Rotinas InsertThing e RemoveThing para devolver tal coisa *
resultado, se isso for necessário por algum motivo. As instruções `return 'nestes procedimentos
precisaria então ser substituído por `return * head '*/


typedef struct _thing 
{ 
	char *item;
	struct _thing *next;
} THING;

THING *start = NULL;

// create new list element of type THING from the supplied text string
THING *NewElement(char *text)
{
        THING *newp;
        newp = (THING *) malloc (sizeof(THING));
        newp -> item = (char *)malloc(strlen(text) + 1);
        strcpy(newp -> item, text);
        newp -> next = NULL;
        return newp;
}  



//Insert a new element into a singly-linked list
// Note -- duplicate entries are not checked for 
void InsertThing(THING **head, THING *newp)
{
	THING **tracer = head;

	while((*tracer) && 
		  strcmp((*tracer)->item, newp -> item) < 1)
	{
		tracer = &(*tracer)->next;
	}

	newp -> next = *tracer;
	*tracer = newp;
}

// Delete first element on list whose item field matches the given text
// NOTE!! delete requests for elements not in the list are silently ignored :-)
void RemoveThing(THING **head, char *text)
{
	BOOL present = FALSE;
	THING *old;
	THING **tracer = head;
	
	while((*tracer) && !(present = (strcmp(text,(*tracer)->item) == 0 )  ))
		tracer = &(*tracer)->next;

	if(present)
	{
		old = *tracer;
		*tracer = (*tracer)->next;
		free(old -> item); // free off space used by text string
		free(old); // free up remainder of list element 
	}
}

void PrintList(THING **head)
{
	THING **tracer = head;
	while (*tracer) {
		printf("%s \n",(*tracer)->item);
		tracer = &(*tracer)->next;
	}
}


int main(int argc, char **argv)
{
        InsertThing(&start, NewElement("chips"));
        InsertThing(&start, NewElement("wine"));
        InsertThing(&start, NewElement("burgers"));
        InsertThing(&start, NewElement("beer"));
        InsertThing(&start, NewElement("pizza"));
        InsertThing(&start, NewElement("zucchini"));
        InsertThing(&start, NewElement("burgers"));
        InsertThing(&start, NewElement("slaw"));
        printf("\nINITIAL LIST\n");
        PrintList (&start);
        RemoveThing(&start, "pizza");
        RemoveThing(&start, "zucchini");
        RemoveThing(&start, "burgers");
        printf("\nALTERED LIST\n");
        PrintList(&start);
                
}       