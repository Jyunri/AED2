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

void imprime(TDicionario *d)
{
}

TDicionario* Tdicionario_inicia()
{
    TDicionario *d;
    d = (TDicionario*)malloc(sizeof(TDicionario));
    d->n = 0;
    d->raiz = NULL;
    return d;
}

TNo* pesquisa(int elemento, TNo* raiz)
{
    if(raiz == NULL) return raiz;
    if(elemento == raiz->item.chave)    return raiz;
    if(elemento < (raiz->item.chave))  return pesquisa(elemento,raiz->esq);
    return pesquisa(elemento,raiz->dir);
} 

int insere(TDicionario* d, int elemento)
{
    TNo* novo;
    novo = (TNo*)malloc(sizeof(TNo));
    novo->item.chave = elemento;
    novo->esq = NULL;
    novo->dir = NULL;

    TNo* aux = d->raiz;
    TNo* teste = d->raiz->esq;
   /* while(1)
    {
        if(elemento < aux->item.chave)
        {
            if(aux->esq==NULL)
            {
                aux->esq = novo; 
                d->n++;
                break;
            }
            aux = aux->esq;
        }
        else
        {
            if(aux->dir==NULL)
            {
                aux->dir = novo; 
                d->n++;
                break;
            }
            aux = aux->dir;
        }
    }*/
    return 0;
}    

int retira(TDicionario* d, int elemento)
{
    return 0;
}
        
int main()
{
    TDicionario* d = Tdicionario_inicia();
    int elemento;
    TNo* indice;
    while(1)
    {
        cin >> elemento;
        if(elemento<0)  break;
        insere(d,elemento);
    }
    
    //cin >> elemento;
    //indice =  pesquisa(elemento,d->raiz);
    //indice != NULL?retira(d,elemento):insere(d,elemento);
    cout << d->n;
    free(d);
}

