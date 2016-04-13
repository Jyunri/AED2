#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int TChave;

typedef struct
{
    TChave chave;
}TItem;

typedef struct SNo* TArvBin;

typedef struct SNo
{
    TItem item;
    TArvBin esq, dir;
}TNo;

typedef TArvBin Tapontador;

typedef struct
{
    TArvBin raiz;
    int n;
}TDicionario;


int imprime(TNo* raiz)
{
    if(raiz == NULL){
        //cout << endl << "arvore vazia";
        return -1;
    }
    if(raiz->esq!=NULL)  imprime(raiz->esq);
    if(raiz->dir!=NULL)  imprime(raiz->dir);
    cout << raiz->item.chave << " ";
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

    return novo;
}
    
int insere(TDicionario* d,TNo** raiz, int elemento)
{
    if(*raiz == NULL)
    {
        *raiz = (criaNo(elemento));
        //cout << endl << "Criado no " << (*raiz)->item.chave;
        d->n++;
        //cout << endl << "endereco raiz insere " << raiz;
        return 1;
    }
    if(elemento < (*raiz)->item.chave) insere(d,&((*raiz)->esq),elemento);
    else if(elemento > (*raiz)->item.chave) insere(d,&((*raiz)->dir),elemento);
    return 0;
}    

TNo* sucessor(TNo* raiz)
{
    TNo* noSucessor;
    if(raiz !=NULL) 
    {
        if(raiz->esq == NULL)
        {
            noSucessor = raiz;
            if(raiz->dir!=NULL) raiz = raiz->dir;   
            return noSucessor;
        }
        return sucessor(raiz->esq);
    }
    return NULL;
}

int retira(TDicionario* d,TNo* raiz, int elemento)
{
    if(raiz == NULL)    return -1;
    if(elemento < raiz->item.chave) return retira(d,raiz->esq,elemento);
    else if(elemento > raiz->item.chave) return retira(d,raiz->dir,elemento);
    if(raiz->esq==NULL && raiz->dir==NULL)  return 0;
    else if(raiz->esq==NULL) raiz = raiz->dir;
    else if(raiz->dir==NULL) raiz = raiz->esq;
    else raiz = sucessor(raiz->dir); 
    d->n--;
    return 0;
}
        
int main()
{
    TDicionario* d = Tdicionario_inicia();
    int elemento;
    int indice;
    while(1)
    {
        cin >> elemento;
        if(elemento<0)  break;
        insere(d,&(d->raiz),elemento);
        //cout << endl << "endereco raiz main " << &d->raiz;
    }
    //imprime(d->raiz);
    cin >> elemento;
    indice =  pesquisa(elemento,d->raiz);
    indice != -1?retira(d,d->raiz,elemento):insere(d,&(d->raiz),elemento);
    cout << d->n;
    free(d);
}

