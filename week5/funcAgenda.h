#ifndef FUNCAGENDA_H_INCLUDED
#define FUNCAGENDA_H_INCLUDED

typedef struct {
   char nome[30];
   char tel[20];
}Contato;

typedef struct {
   int op, cont, tambuffer, i;
   char find[30];
   Contato *quit;      //ponteiro para contato
}Variaveis;

// Declaração dos ponteiros globais
void *pBuffer;
Contato *pContato;
Variaveis *var;

void addContato();
void deletar();
void list();
void menu();

#endif // FUNCAGENDA_H_INCLUDED