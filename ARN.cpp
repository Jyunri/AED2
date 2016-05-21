
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int TChave; 
typedef struct
{ 
  TChave Chave; 
/* outros compomentes */ 
} TItem;  
typedef struct SNo* TArvBin; 
typedef struct SNo { 
  TItem Item; 
  TArvBin Esq, Dir;
  int cor;
} TNo; 

int imprime(TArvBin a)
{
    if(a == NULL)
    {
        cout << "(";
        cout << ")";
        return -1;
    }
    cout << "(";
    a->cor==0?cout << "N":cout << "R"; 
    cout << a->Item.Chave;
    imprime(a->Esq);
    imprime(a->Dir);
    cout << ")";
}
    
TArvBin constroiArvore()
{
    return NULL;
}


int max(int a, int b)
{
    return a>b?a:b;
}

int inverte(TArvBin *a)
{   
    if(a!=NULL)
    {
        if((*a)->cor==0)    (*a)->cor=1;
        else    (*a)->cor=0;
    }
}

int colore(TArvBin *a)
{
    inverte(&(*a));
    inverte(&((*a)->Esq));
    inverte(&((*a)->Dir));
}

void rotacaoE(TArvBin *a)
{   
    TArvBin filho = (*a)->Dir;
    (*a)->Dir = filho->Esq;
    filho->Esq = *a;
    *a = filho;
}

void rotacaoD(TArvBin *a)
{   
    TArvBin filho = (*a)->Esq;
    (*a)->Esq = filho->Dir;
    filho->Dir = *a;
    *a = filho;
}

int verificaRubro(TArvBin a)
{
    return (a!=NULL&&a->cor==1)?1:0;  
}

int BalancaEsq(TArvBin *pai, TArvBin *filho, TArvBin *avo)
{
    if(verificaRubro((*avo)->Dir))    colore(avo);   //tio rubro
    else
    {
        if((*pai)->Dir == *filho)   rotacaoE(pai);    //pai e filhos de lados opostos. 
        inverte(pai);
        inverte(avo);
        rotacaoD(avo);
    }
}

int BalancaDir(TArvBin *pai, TArvBin *filho, TArvBin *avo)
{
    if(verificaRubro((*avo)->Esq))    colore(avo);   //tio rubro
    else
    {
        if((*pai)->Esq == *filho)  rotacaoD(pai);    //pai e filhos de lados opostos.
        inverte(pai);
        inverte(avo);
        rotacaoE(avo);
    }
    return 1;
}

int BalancaNo(TArvBin *pai, TArvBin *filho, TArvBin *avo)
{
    if(avo == NULL) return 0;   //avo nao pode ser nulo
    if((*pai)->cor == 0)  return 1; //nada precisa ser feito
    if((*filho)->cor == 0)  return 0; //filho veio com cor errada, toda insercao eh rubra
    if(*pai == (*avo)->Esq) BalancaEsq(pai,filho,avo);  //pai eh o filho esquerdo do avo => tio eh filho direito
    else    BalancaDir(pai,filho,avo);   //pai eh filho direito do avo  => tio eh filho esquerdo
    return 0;
}

int insereRec(TArvBin *a, int elemento, TArvBin *pai)
{
    if(*a==NULL)
    {
        *a = (TArvBin)malloc(sizeof(TNo));
        (*a)->Esq = NULL;
        (*a)->Dir = NULL;
        (*a)->Item.Chave = elemento;
        (*a)->cor = 1; //toda insercao eh rubra
        return 1;
    }
    if(elemento<((*a)->Item.Chave))
    {
        insereRec(&((*a)->Esq),elemento,&(*a));
        BalancaNo(a,&((*a)->Esq),pai);
        return 1;
    }
    if(elemento>((*a)->Item.Chave))
    {
        insereRec(&((*a)->Dir),elemento,&(*a));
        BalancaNo(a,&((*a)->Dir),pai);
        return 1;
    }
}

int insere(TArvBin *a, int elemento)
{
    insereRec(a,elemento,NULL);
    (*a)->cor = 0;
}

int bh(TArvBin a)
{
    int altura = 0;
    if(a==NULL) return 0;
    if(a->cor==0)   altura +=1;
    if(a->Esq==NULL&&a->Dir==NULL)  return altura;
    altura += max(bh(a->Esq),bh(a->Dir));
    return altura;
}

int verificaARN(TArvBin a)
{
    if(!verificaARN(a->Esq))    return 0;
    if(!verificaARN(a->Dir))    return 0;
    if(a->cor==1)
    {
        if(a->Esq->cor==1)  return 0;
        if(a->Dir->cor==1)  return 0;
    }
    if(bh(a->Esq)!=bh(a->Dir))  return 0;
    return 1;
}

int main()
{
    TArvBin arvore = constroiArvore();
    int n, elemento;
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        cin >> elemento;
        insere(&arvore,elemento);
       
        /*
        debug print 
        cout << "arvore ate entao" << endl;
        imprime(arvore);
        cout << endl;
        */
    } 
    cout << bh(arvore) << endl;
    imprime(arvore);
}
