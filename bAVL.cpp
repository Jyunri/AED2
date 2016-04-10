#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int TChave; 
typedef struct
{ 
  TChave Chave; 
/* outros compomentes */ 
} TItem;  
typedef struct SNo *TArvBin; 
typedef struct SNo { 
  TItem Item; 
  TArvBin Esq, Dir; 
} Arvore; 

int imprime(Arvore* a)
{
    if(a == NULL)
    {
        cout << "(";
        cout << ")";
        return -1;
    }
    cout << "(C" << a->Item.Chave;
    imprime(a->Esq);
    imprime(a->Dir);
    cout << ")";
}
    
Arvore* ConstroiArvore()
{
    char c;
    Arvore* raiz;
    raiz = (Arvore*)malloc(sizeof(Arvore));
    cin >> c;
    if(c == '(')
    {
        cin >> c;
        if(c == 'C')
        {
            raiz = (Arvore*)malloc(sizeof(Arvore));
            cin >> raiz->Item.Chave;
            raiz->Esq = ConstroiArvore();
            raiz->Dir = ConstroiArvore();
            cin >> c;   //Le o fecha parenteses
            return raiz;
        }
        else
        {
            return NULL;
        }
    }
}

int max(int a, int b)
{
    return a>b?a:b;
}

int alturaArvore(Arvore* a,int altura)
{
    if(a==NULL) return -1;
    if(a->Esq==NULL&&a->Dir==NULL)  return altura;
    altura +=1;
    return max(alturaArvore(a->Esq,altura),alturaArvore(a->Dir,altura));
}

int calculaFB(Arvore* a)
{
    if(a==NULL) return 0;
    //if(a->Esq == NULL && a->Dir == NULL)  return 0;
    //if(a->Esq == NULL)  return alturaArvore(a->Dir,0);
    //if(a->Dir == NULL)  return alturaArvore(a->Esq,0);
    return alturaArvore(a->Esq,0) - alturaArvore(a->Dir,0);
}   

int verificaAVL(Arvore* a)
{
    if(a == NULL)   return 1;
    if(verificaAVL(a->Esq))
    {
        if(verificaAVL(a->Dir))
            if(calculaFB(a)>=-1&&calculaFB(a)<=1)   return 1;
    }
    return 0;
}

Arvore* rotacaoLL(Arvore *a)
{
    Arvore* filho = a->Esq;  
    a->Esq = filho->Dir;
    filho->Dir = a;
    return filho;
} 

Arvore* rotacaoRR(Arvore *a)
{
    Arvore* filho = a->Dir;
    a->Dir = filho->Esq;
    filho->Esq = a;
    return filho;
} 

Arvore* rotacaoLR(Arvore *a)
{
    Arvore* filho = a->Esq;
    Arvore* neto = filho->Dir;
    filho->Dir = neto->Esq;
    neto->Esq = filho;
    a->Esq = neto->Dir;
    neto->Dir = a;
    a = neto;
    return a;
} 
    
Arvore* rotacaoRL(Arvore *a)
{
    Arvore* filho = a->Dir;
    Arvore* neto = filho->Esq;
    filho->Esq = neto->Dir;
    neto->Dir = filho;
    a->Dir = neto->Esq;
    neto->Esq = a;
    return neto;
} 

Arvore* balancaNo(Arvore *a)
{  
    if(calculaFB(a)>1)
    {
        if(calculaFB(a->Esq)>0) 
        {
            a = rotacaoLL(a);
            return a;
        }
        else if(calculaFB(a->Esq)<0) 
        { 
            a = rotacaoLR(a);
            return a;
        }
    }
    else if(calculaFB(a)<-1)
    {
        if(calculaFB(a->Dir)<0)
        {
            a = rotacaoRR(a);
            return a;
        }
        else if(calculaFB(a->Dir)>0) 
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

Arvore* balanceamento(Arvore* a)
{   
    if(a!=NULL)
    {
        a->Esq = balanceamento(a->Esq);
        a->Dir = balanceamento(a->Dir);
        a = balancaNo(a);
    }
    return a;
 } 

int main()
{
    Arvore* arvore;
    arvore = ConstroiArvore();
    cout << alturaArvore(arvore,0);
    if(!verificaAVL(arvore))    arvore = balanceamento(arvore);    
    cout << endl << alturaArvore(arvore,0);
    cout << endl;
    imprime(arvore);
}
