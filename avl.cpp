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
                break;
            case 1:
                (*raiz)->fb += 1;   
                return balancaNoEsq(&((*raiz)->esq));
                //return 0;   //arvore nao cresceu
                break;
            case -1:
                (*raiz)->fb += 1;    //arvore perfeita 
                return 0; //arvore nao cresceu
                break;  
            }
        }
    }
    
    else if(elemento > (*raiz)->item.chave) insere(&((*raiz)->dir),elemento);
    return 0;
}    

TNo* sucessor(TNo** raiz)
{
    TNo* noSucessor;
    if(*raiz !=NULL) 
    {
        if((*raiz)->esq == NULL)
        {
            noSucessor = *raiz;
            if((*raiz)->dir!=NULL) *raiz = (*raiz)->dir;   
            return noSucessor;
        }
        return sucessor(&((*raiz)->esq));
    }
    return NULL;
}

int retira(TDicionario* d,TNo** raiz, int elemento)
{
    TNo* aux;
    if(raiz == NULL)    return -1;
    if(elemento < (*raiz)->item.chave) return retira(d,&((*raiz)->esq),elemento);
    else if(elemento > (*raiz)->item.chave) return retira(d,&((*raiz)->dir),elemento);
    if((*raiz)->esq==NULL && (*raiz)->dir==NULL)  free(*raiz);
    else if((*raiz)->esq==NULL) *raiz = (*raiz)->dir;
    else if((*raiz)->dir==NULL) *raiz = (*raiz)->esq;
    else
    {
        aux = sucessor(&((*raiz)->dir)); 
        (*raiz)->item.chave = aux->item.chave;
        free(aux);
    }
    d->n--;
    return 0;
}
 
void rotacaoLL(TNo **a)
{
    TNo* filho = (*a)->esq;  
    (*a)->esq = filho->dir;
    filho->dir = *a;
    *a = filho;
} 

void rotacaoRR(TNo **a)
{
    TNo* filho = (*a)->dir;
    (*a)->dir = filho->esq;
    filho->esq = *a;
    *a = filho;
} 

void rotacaoLR(TNo **a)
{
    TNo* filho = (*a)->esq;
    TNo* neto = filho->dir;
    filho->dir = neto->esq;
    neto->esq = filho;
    (*a)->esq = neto->dir;
    neto->dir = *a;
    *a = neto;
} 
    
TNo* rotacaoRL(TNo **a)
{
    TNo* filho = (*a)->dir;
    TNo* neto = filho->esq;
    filho->esq = neto->dir;
    neto->dir = filho;
    (*a)->dir = neto->esq;
    neto->esq = *a;
} 
/*
TNo* balancaNoEsq(TNo **noEsq)
{  
    if(*noEsq->fb > 1)
    {
        if(calculaFB(a->esq)>0) 
        {
            a = rotacaoLL(&a);
            return a;
        }
        else if(calculaFB(a->esq)<0) 
        { 
            a = rotacaoLR(&a);
            return a;
        }
    }
    else if(calculaFB(a)<-1)
    {
        if(calculaFB(a->dir)<0)
        {
            a = rotacaoRR(&a);
            return a;
        }
        else if(calculaFB(a->dir)>0) 
        {
            a = rotacaoRL(a);
            return a;
        }
    }
    else
    {
        return a;
    }
    return a;
}
*/
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
        if(elemento<0)  break;
        insere(&(d->raiz),elemento);
        d->n++;
        if(elemento==9)    rotacaoRR(&(d->raiz));
        i++;
    }
    cin >> elemento;
    indice =  pesquisa(elemento,d->raiz);
    cout << "Encontrou? " << indice << endl;
    //indice != -1?retira(d,&(d->raiz),elemento):insere(d,&(d->raiz),elemento);
    imprime(d->raiz);
    imprimeFB(d->raiz);
    free(d);
}

