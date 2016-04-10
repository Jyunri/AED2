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
    int esq, dir;
    int meio;
    
    esq = 0;
    dir = (d->n-1);
    meio = (esq + dir)/2;
    if(elemento == d->item[0].chave) return 0;

    while(esq<=dir)
    {
        if(elemento == d->item[meio].chave) return meio;
        else if(elemento > d->item[meio].chave) esq = meio + 1;
        else dir = meio-1;
        meio = (esq + dir)/2;
    }
    return -1;
}
    
int insere(TDicionario* d, TChave elemento)
{
    if(d->n == 0)
    {
        d->item[0].chave = elemento;
        d->n++;
        return 0;
    }
    for(int i = d->n-1; i>=0; i--)
    {
        if(elemento>=d->item[i].chave)
        {
            d->item[i+1].chave = elemento;
            break;
        }
        else
        {    
            d->item[i+1] = d->item[i];
            if(i == 0)  d->item[0].chave = elemento;
        }
    }
    d->n++;
    if(d->n == d->max)    d->item = (TItem*)realloc(d->item,2*d->max*sizeof(TItem));
    d->max *= 2;
}

int retira(TDicionario* d, TChave elemento)
{
    int indice = pesquisa(d,elemento);
    if(indice == -1)   return -1;
    for(int i = indice; i<(d->n)-1; i++)    d->item[i] = d->item[i+1];
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
    int elemento;
    int indice;
    while(1)
    {
        cin >> elemento;
        if(elemento<0)  break;
        insere(dicionario,elemento);
    }
    
    cin >> elemento;
    indice =  pesquisa(dicionario,elemento);
    indice>=0?retira(dicionario,elemento):insere(dicionario,elemento);
    cout << dicionario->n;
    free(dicionario);
}

