#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int TChave;
typedef struct
{
    TChave chave;
}TItem;

typedef struct
{
    TItem *item;
    int n, max;
}TDicionario;

void imprime(TDicionario *d)
{
    int i;
    for(i = 0; i < d->n; i++)
        cout << d->item[i].chave << " ";
}

TDicionario* inicializa()
{
    TDicionario* d;
    d = (TDicionario*)malloc(sizeof(TDicionario));
    d->item = (TItem*)malloc(sizeof(TItem));
    d->n = 0;
    d->max = 1;
    return d;
}

int pesquisa(TDicionario* d, TChave elemento)
{
    int i;
    for (i = d->n; i>=0; i--)
    { 
        if(d->item[i].chave == elemento)   break;
        if(i==0)    return -1;
    }
    return i;
}
    
int insere(TDicionario* d, TChave elemento)
{
    d->item[d->n].chave = elemento; 
    d->n++;
    if(d->n == d->max)    d->item = (TItem*)realloc(d->item,2*d->max*sizeof(TItem));
}

int retira(TDicionario* d, TChave elemento)
{
    int indice = pesquisa(d,elemento);
    if(indice == -1)   return -1;
    d->item[indice] = d->item[d->n-1];
    d->n--;
    if(d->n == d->max/4)   
    {
        d->item = (TItem*)realloc(d->item,(d->max/2)*sizeof(TItem));
        d->max = d->max/2;
    } 
}

 
int main()
{
    TDicionario* dicionario = inicializa();
    int add,remove;
    int elemento;
    cin >> add;
    cin >> remove;
    for(int i = 1; i<=add; i++)
    {
        cin >> elemento;
        insere(dicionario,elemento);
    }
    for(int j = 1; j<=remove; j++)
    {
        cin >> elemento;
        retira(dicionario,elemento);
    }
    imprime(dicionario);
    free(dicionario);
}



