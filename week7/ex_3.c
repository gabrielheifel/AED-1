#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long TipoChave;

typedef struct registro {
  TipoChave Chave;
} Registro;

typedef struct No * Apontador;
typedef Apontador TipoDicionario;

typedef struct No {
  Registro Reg;
  Apontador pEsq, pDir;
} No;

Apontador raiz = NULL;

int Altura(No* pRaiz) {
  int iEsq, iDir;

  if(pRaiz == NULL)
    return 0;
  
  iEsq = Altura(pRaiz->pEsq);
  iDir = Altura(pRaiz->pDir);

  if(iEsq > iDir)
    return iEsq+1;
  else
    return iDir+1;
}

int FB (No* pRaiz) {  //fator de balanceamento
  if(pRaiz == NULL)
    return 0;
  
  return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

// Rotacoes
void RSE(No** ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->pDir;
  (*ppRaiz)->pDir = pAux->pEsq;
  pAux->pEsq = (*ppRaiz);
  (*ppRaiz) = pAux;
}

void RSD(No** ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->pEsq;
  (*ppRaiz)->pEsq = pAux->pDir;
  pAux->pDir = (*ppRaiz);
  (*ppRaiz) = pAux;
}

// Rotacoes duplas
int BalancaEsq(No** ppRaiz) {
  int fbe = FB( (*ppRaiz)->pEsq );
  if(fbe > 0){
    RSD(ppRaiz);
  }
  else if(fbe < 0){
    RSE( &((*ppRaiz)->pEsq) );
    RSD(ppRaiz);
    return 1;
  }
  return 0;
}

int BalancaDir(No** ppRaiz) {
  int fbd = FB( (*ppRaiz)->pDir );
  if(fbd < 0){
    RSE(ppRaiz);
  }
  else if(fbd > 0){
    RSD( &((*ppRaiz)->pDir) );
    RSE(ppRaiz);
    return 1;
  }
  return 0;
}

int Balanceamento(No** ppRaiz) {
  int fb = FB(*ppRaiz);
  if(fb > 1)
    return BalancaEsq(ppRaiz);
  else if( fb < -1)
    return BalancaDir(ppRaiz);
  else
    return 0;
}

int Insere(No **ppRaiz, Registro* x) {
  if(*ppRaiz == NULL){
    *ppRaiz = (No*)malloc(sizeof(No));
    (*ppRaiz)->Reg = *x;
    (*ppRaiz)->pEsq = NULL;
    (*ppRaiz)->pDir = NULL;
    return 1;
  }
  else if( (*ppRaiz)->Reg.Chave > x->Chave){
    if( Insere(&(*ppRaiz)->pEsq, x) ){
      if(Balanceamento(ppRaiz))
        return 0;
      else
        return 1;
    }
  }
  else if( (*ppRaiz)->Reg.Chave < x->Chave){
    if( Insere(&(*ppRaiz)->pDir, x) ){
      if(Balanceamento(ppRaiz))
        return 0;
      else
        return 1;
    }
    else 
      return 0;
  }
  else{
    printf("Valor duplicado!\n");
    return 0;
  }
}

No* ProcuraMenor(No* atual) {
  No *no1 = atual;
  No *no2 = atual->pEsq;
  while(no2 != NULL){
    no1 = no2;
    no1 = no2->pEsq;
  }
  return no1;
}

int Remove(No **ppRaiz, int valor) {
  if(*ppRaiz == NULL){
    printf("Arvore vazia");
    return 0;
  }
  int result;
  if(valor < (*ppRaiz)->Reg.Chave){
    if((result=Remove(&(*ppRaiz)->pEsq, valor))==1)
      Balanceamento(raiz);
  }
  else if(valor > (*ppRaiz)->Reg.Chave){
    if((result=Remove(&(*ppRaiz)->pDir, valor))==1)
      Balanceamento(raiz);
  }
  if(valor == (*ppRaiz)->Reg.Chave){
    if(((*ppRaiz)->pEsq==NULL || (*ppRaiz)->pDir==NULL)){
      No *oldNode = (*ppRaiz);
      if((*ppRaiz)->pEsq != NULL)
        *ppRaiz = (*ppRaiz)->pEsq;
      if((*ppRaiz)->pDir != NULL)
        *ppRaiz = (*ppRaiz)->pDir;
      free(oldNode);
    }
    else{
      No *temp= ProcuraMenor((*ppRaiz)->pDir);
      (*ppRaiz)->Reg.Chave = temp->Reg.Chave;
      Remove(&(*ppRaiz)->pDir, (*ppRaiz)->Reg.Chave);
    }
    return 1;
  }
  return result;
}

int EhArvoreArvl(No* pRaiz) {
  int fb;
  if(pRaiz == NULL)
    return 1;
  if(!EhArvoreArvl(pRaiz->pEsq))
    return 0;
  if(!EhArvoreArvl(pRaiz->pDir))
    return 0;
  
  fb = FB(pRaiz);
  if((fb > 1) || (fb < -1))
    return 0;
  else
    return 1;
}

int main() {
  int n, i, *salvaValor;
  Registro *r;

  printf("Informe o numero de nós(n): ");
  scanf("%d", &n);

  salvaValor = (int*)malloc(n*sizeof(int));

  srand(time(0));

  for(i=0; i<n; i++){
    r->Chave = rand()%100;
    salvaValor[i]=r->Chave;
    Insere(&raiz, r);
  }

  if(EhArvoreArvl(raiz) == 1)
    printf("OK!\n");

  for(i=0; i<n; i++){
    Remove(&raiz, salvaValor[i]);
  }
}