#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int Tchave;

typedef struct
{
    Tchave chave;
}Titem;

typedef struct SNo* TArvBin;

typedef struct SNo
{
    Titem item;
    TArvBin esq, dir;
    int fb;
}TNo;

typedef TArvBin Tapontador;

typedef struct
{
    TArvBin raiz;
    int n;
}TDicionario;


int imprime(TNo* a)
{
    if(a == NULL)
    {
        cout << "(";
        cout << ")";
        return -1;
    }
    cout << "(C" << a->item.chave;
    imprime(a->esq);
    imprime(a->dir);
    cout << ")";
}
    
int imprimeFB(TNo* a)
{
    if(a == NULL)   return -1;
    imprimeFB(a->esq);
    imprimeFB(a->dir);
    cout << endl << a->item.chave << ", fb: " << a->fb;
}

int max(int a, int b)
{
    return a>b?a:b;
}

TDicionario* Tdicionario_inicia()
{
    TDicionario *d;
    d = (TDicionario*)malloc(sizeof(TDicionario));
    d->n = 0;
    d->raiz = NULL;
    return d;
}

int pesquisa(int elemento, TNo* raiz)
{
    if(raiz == NULL) return -1;
    if(elemento == raiz->item.chave)    return 1;
    if(elemento < (raiz->item.chave))  return pesquisa(elemento,raiz->esq);
    return pesquisa(elemento,raiz->dir);
} 

TNo* criaNo(int elemento)
{
    TNo* novo;
    novo = (TNo*)malloc(sizeof(TNo));
    novo->item.chave = elemento;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->fb = 0;

    return novo;
}
 
void rotacaoLL(TNo **a)
{
    TNo* filho = (*a)->esq;  
    //ajuste dos fb
    if(filho->fb == 1){  (*a)->fb = 0; filho->fb = 0;}
    else{ (*a)->fb = 1; filho->fb = -1;} //nunca entra em insercao, pai ruim filho ok

    (*a)->esq = filho->dir;
    filho->dir = *a;
    *a = filho;
} 

void rotacaoRR(TNo **a)
{
    TNo* filho = (*a)->dir;
    //ajuste dos fb
    if(filho->fb == -1){  (*a)->fb = 0; filho->fb = 0;}
    else {(*a)->fb = -1; filho->fb = 1;}
    
    (*a)->dir = filho->esq;
    filho->esq = *a;
    *a = filho;
} 

void rotacaoLR(TNo **a)
{
    TNo* filho = (*a)->esq;
    TNo* neto = filho->dir;
    //ajuste dos fb
    if(neto->fb == 1)  {(*a)->fb = -1; filho->fb = 0;}
    else if(neto->fb == -1) {(*a)->fb = 0; filho->fb = 1;}
    else {(*a)->fb = 0; filho->fb = 0;}
    neto->fb = 0;

    filho->dir = neto->esq;
    neto->esq = filho;
    (*a)->esq = neto->dir;
    neto->dir = *a;
    *a = neto;
} 
    
void rotacaoRL(TNo **a)
{
    TNo* filho = (*a)->dir;
    TNo* neto = filho->esq;
    //ajuste dos fb
    if(neto->fb == 1)  {(*a)->fb = 0; filho->fb = -1;}
    else if(neto->fb == -1) {(*a)->fb = 1; filho->fb = 0;}
    else {(*a)->fb = 0; filho->fb = 0;}
    neto->fb = 0;
    
    filho->esq = neto->dir;
    neto->dir = filho;
    (*a)->dir = neto->esq;
    neto->esq = *a;
    *a = neto;
} 

int balancaNoEsq(TNo **raiz)
{  
    if((*raiz)->esq->fb > 0){   rotacaoLL(raiz); return 1;}
    else if((*raiz)->esq->fb < 0) {rotacaoLR(raiz); return 1;}
    else{ rotacaoLL(raiz);   return 0;}   //soh ocorre na remocao
}

int balancaNoDir(TNo **raiz)
{  
    if((*raiz)->dir->fb > 0) {  rotacaoRL(raiz); return 1;}
    else if((*raiz)->dir->fb < 0) {rotacaoRR(raiz); return 1;}
    else {rotacaoRR(raiz);   return 0;}   //soh ocorre na remocao
}

    

int sucessor(TNo** pai, TNo** filho)
{
    TNo* aux;
    if(*filho !=NULL) 
    {
        if((*filho)->esq == NULL)
        {
            aux = *filho;
            (*pai)->item = aux->item;
            *filho = (*filho)->dir;   
            free(aux);
            return 1;
        }
        else
        {
            if(sucessor(&(*pai),(&((*filho)->esq))))   //diminuiu
                switch((*filho)->fb){
                    case -1: return balancaNoDir(filho);
                    case 0: (*filho)->fb--;  return 0;
                    case 1: (*filho)->fb--;  return 1;
                }
        }
    }
    return 0;//erro
}

int insere(TNo** raiz, int elemento)
{
    if(*raiz == NULL)
    {
        *raiz = (criaNo(elemento));
        //cout << endl << "endereco raiz insere " << raiz;
        return 1;
    }
    if(elemento < (*raiz)->item.chave)
    {
        if(insere(&((*raiz)->esq),elemento))    //ao inserir, arvore cresceu
        {
            switch((*raiz)->fb) //cenario anterior
            {
            case 0:
                (*raiz)->fb += 1;
                return 1;   //arvore cresceu
            case 1:
                balancaNoEsq(raiz);
                return 0;   //arvore nao cresceu
            case -1:
                (*raiz)->fb += 1;    //arvore perfeita 
                return 0; //arvore nao cresceu
            }
        }
    }
    else if(elemento > (*raiz)->item.chave)
    {
        if(insere(&((*raiz)->dir),elemento))    //ao inserir, arvore cresceu
        {
            switch((*raiz)->fb) //cenario anterior
            {
            case 0:
                (*raiz)->fb -= 1;
                return 1;   //arvore cresceu
            case 1:
                (*raiz)->fb -= 1;   
                return 0;   //arvore nao cresceu
            case -1:
                balancaNoDir(raiz);
                return 0; //arvore nao cresceu
            }
        }
    }
    return 0;   //erro na insercao
}    

int retira(TDicionario* d,TNo** raiz, int elemento)
{
    TNo* aux;
    if(raiz == NULL)    return -1;
    if(elemento < (*raiz)->item.chave)
    {
        if(retira(d,&((*raiz)->esq),elemento)) //arvore esq diminuiu
        {
            switch((*raiz)->fb)
            {
            case 0:
                (*raiz)->fb -= 1;
                return 0;   //arvore nao diminuiu
            case 1:
                (*raiz)->fb -= 1;   
                return 1;   //arvore dimninuiu
            case -1:
                return balancaNoDir(raiz);
            }
        }
    }
    else if(elemento > (*raiz)->item.chave) 
    {
        if(retira(d,&((*raiz)->dir),elemento))
        {
            switch((*raiz)->fb)
            {
            case 0:
                (*raiz)->fb += 1;
                return 0;   //arvore nao diminuiu
            case 1:
                return balancaNoEsq(raiz);
            case -1:
                (*raiz)->fb += 1;     
                return 1; //arvore diminuiu
            }
        }
    }
    else    //elemento encontrado
    {   
        aux = *raiz;
        if((*raiz)->esq==NULL) *raiz = (*raiz)->dir;
        else if((*raiz)->dir==NULL) *raiz = (*raiz)->esq;
        else
        {
            d->n--;
            return sucessor(&(*raiz),&((*raiz)->dir)); 
        }
        free(aux); 
        d->n--;
        return 1;   //diminuiu
    }
    return 0;
}
int main()
{
    TDicionario* d = Tdicionario_inicia();
    int entradas,elemento;
    int indice;
    int i = 1;
    cin >> entradas;
    while(i<=entradas)
    {
        cin >> elemento;
        insere(&(d->raiz),elemento);
        //imprime(d->raiz);
        d->n++;
        i++;
    }
    cin >> elemento;
    indice =  pesquisa(elemento,d->raiz);
    indice != -1?retira(d,&(d->raiz),elemento):insere(&(d->raiz),elemento);
    imprime(d->raiz);
    imprimeFB(d->raiz);
    free(d);
}

