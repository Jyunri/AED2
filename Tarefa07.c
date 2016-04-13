/*
DIsciplina AED 2 - 08/04/2016

Discente: Juliana de Paula Nader
RA: 86301

Tarefa07: AVLTREE

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>



typedef int TChave;

typedef struct {
    TChave Chave;
    /* outros componentes */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
} TNo;



TArvBin ConstroiArvore(){
    char ch;
    int i;
    TArvBin root;
    //root = (TArvBin)malloc(sizeof(TNo));
    scanf("%c", &ch);
    if (ch == '('){
        scanf("%c", &ch);
        if (ch == 'C'){
            root = (TArvBin)malloc(sizeof(TNo));
            scanf("%d", &root->Item.Chave);
            root->Esq = ConstroiArvore();
            root->Dir = ConstroiArvore();
            scanf("%c", &ch);
            return root;
        }
        else{
            return NULL;
        }
    }
}

int altura(TArvBin t){

    int e, d;
    if (t == NULL)
        return -1;
    e = altura(t->Esq);
    d = altura(t->Dir);
    if (e > d)
        return e+1;
    else
        return d+1;
}


int FB(TArvBin t){
    if(t == NULL)
        return 0;
    return altura(t->Esq)- altura(t->Dir);
}
    
void imprime (TArvBin t) {
    if (t != NULL){
    printf("(C%d", t->Item.Chave);
    imprime(t->Esq);
    imprime(t->Dir);
    printf(")");
    }
    else
        printf("()");
}



void freeArv(TArvBin *pt){
    TArvBin No;
    No = *pt;
    if (No != NULL) {
    freeArv(&No->Esq);
    freeArv(&No->Dir);
    free(No);
    (*pt) = NULL;
    }
}

void LL( TArvBin* pA )
{
    TArvBin pB = (*pA)->Esq;
    if (pB->Dir)
        (*pA)->Esq = pB->Dir;
   else
        (*pA)->Dir =NULL;
    pB->Dir= (*pA);
    (*pA)=pB;


}

void RR(TArvBin *pA )
{
    TArvBin pB=(*pA)->Dir;
   if (pB->Esq)
        (*pA)->Dir=pB->Esq;
   else
        (*pA)->Dir = NULL;
   pB->Esq= (*pA);
   (*pA)=pB;
}

void doubleWithLeftChild( TArvBin*  pA )
{
    TArvBin pB = (*pA)->Esq;
    TArvBin pC = pB->Dir;
    if (pC->Esq)
        pB->Dir= pC->Esq;
    else
        pB->Dir=NULL;

    if (pC->Dir)
        (*pA)->Esq = pC->Dir;
    else
        (*pA)->Esq = NULL;
    pC->Esq=pB;
    pC->Dir= (*pA);
    (*pA)=pC;


}

void  doubleWithRightChild( TArvBin *pA )
{
    TArvBin pB = (*pA)->Dir;
    TArvBin pC = pB->Esq;
    if (pC->Esq)
        pB->Esq = pC->Dir;
    else
        (*pA)->Dir = NULL;
    if (pC->Dir)
        (*pA)->Dir=pC->Esq;
    else
        pB->Esq = NULL;
    pC->Esq= (*pA);
    pC->Dir=pB;
    (*pA)=pC;


}

void balancaNo(TArvBin* t){

    int balance = FB(*t);
    int balance1 = FB((*t)->Esq);
    int balance2 = FB((*t)->Dir);


    if(balance >1 ){
        if( balance1 >0)
            LL( t );
        else if (balance1<0)
            doubleWithLeftChild( t );
    }
    else if( balance< -1 ){
        if( balance2<0 )
            RR( t );
        else if (balance2 >0)
            doubleWithRightChild( t );
    }
}

void balancaArv(TArvBin* t){
    if (*t != NULL){
        balancaArv(&(*t)->Esq);
        balancaArv(&(*t)->Dir);
        balancaNo(t);
    }
}



int EhAVL(TArvBin t) {

    int balance = FB(t);

    if (t == NULL)
        return 1;

    if(!EhAVL(t->Esq))
        return 0;
    if (!EhAVL(t->Dir))
        return 0;

    if (balance < -1 || balance>1)
        return 0;
    else
        return 1;

}

int main()
{
    TArvBin raiz;     // raiz

    int i;
    // Implemente a entrada de dados aqui!

    raiz = ConstroiArvore();

    printf("%d\n",altura(raiz));


    if(!EhAVL(raiz))
        balancaArv(&raiz);

    printf("%d\n",altura(raiz));

    imprime(raiz);

    freeArv(&raiz);

    return 0;
}
