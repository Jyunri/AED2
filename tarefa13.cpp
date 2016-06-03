/*input
7
3 4 9 2 5 1 8
5
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
} TNo;

int tipo(TArvBin No)
{
	//1 significa folha(no externo), 0 significa no interno
	return ((No != NULL) && (No->Esq == NULL) && (No->Dir == NULL))?1:0;
}

int Imprime(TArvBin a)
{
    if((a == NULL))
    {
        cout << "(";
        cout << ")";
        return -1;
    }
    cout << "(";
    if (tipo(a))	cout << "C" << a->Item.Chave; //so imprime se for externo
    Imprime(a->Esq);
    Imprime(a->Dir);
    cout << ")";
    return 0;
}


int retornaDigito(TChave x, int digito)
{
	return ((x >> digito) & 1);
}


TArvBin PesquisaRec(TArvBin No, TChave x, int digito)
{
	if(No==NULL)	return NULL;
	if(tipo(No))
	{
		if((No->Item.Chave) == x)	return No;
		return NULL;
	}
	return retornaDigito(x,digito)?PesquisaRec(No->Dir, x, digito+1):PesquisaRec(No->Esq, x, digito+1);
}

//trigger
TArvBin Pesquisa(TArvBin Raiz, TChave x)
{
	// Implemente o seu metodo aqui!
	//cout << "pesquisando "<< x <<endl;	//debug
	return PesquisaRec(Raiz,x,0);
}


TArvBin criaNo(TItem x)
{
	TArvBin no;
	no = (TArvBin)malloc(sizeof(TNo));
	no->Item = x;
	no->Esq = NULL;
	no->Dir = NULL;
	return no;
}

int criaNoInterno(TArvBin* pNo, TItem x, int digito)
{
	TArvBin no = *pNo;	//utilizar no auxiliar para colocar o *pNo no lugar
	*pNo = (TArvBin)malloc(sizeof(TNo));	//realocar antigo *pNo para virar no interno
	switch(retornaDigito(no->Item.Chave,digito))
	{
		case 0:
			(*pNo)->Esq = no;
			(*pNo)->Dir = NULL;
			if(retornaDigito(x.Chave,digito)==0)	return criaNoInterno(&(*pNo)->Esq,x,digito+1);
			(*pNo)->Dir = criaNo(x);
			break;
		case 1:
			(*pNo)->Dir = no;
			(*pNo)->Esq = NULL;
			if(retornaDigito(x.Chave,digito)==1)	return criaNoInterno(&(*pNo)->Dir,x,digito+1);
			(*pNo)->Esq = criaNo(x);
			break;
	}
	return 1;
}

int InsereRec(TArvBin *pNo, TItem x, int digito)
{
	if((*pNo) == NULL){
		(*pNo) = criaNo(x);	//arvore nula
		return 1;
	}
	else if(tipo(*pNo))	//no externo
	{
		if((*pNo)->Item.Chave == x.Chave)	return 0;	//ja existe
		return criaNoInterno(pNo,x,digito);
	}
	return retornaDigito(x.Chave,digito)?InsereRec((&(*pNo)->Dir), x, digito+1):InsereRec((&(*pNo)->Esq), x, digito+1);
}

//trigger
int Insere(TArvBin *pRaiz, TItem x)
{
	// Implemente o seu metodo aqui!
	InsereRec(pRaiz,x,0);
}


int Retira(TArvBin *pRaiz, TChave x)
{
	// Implemente o seu metodo aqui!
	if(*pRaiz==NULL)	return 0;
	TArvBin aux = *pRaiz;
	TArvBin pai = *pRaiz;
	TArvBin irmao;
	int lado;
	int digito = 0;
	while(!tipo(aux))	//enquanto for no interno
	{
		if(retornaDigito(x,digito))
		{
			if((aux->Esq != NULL)&&(!tipo(aux->Dir)))
			{
				pai = aux;	//"pai" atualiza se filho de aux tiver outro irmao e filho de aux for interno
				lado = 0;
			}
			if(tipo(aux->Dir))
			{
				if(aux->Dir->Item.Chave != x) return 0; //nao encontrou elemento
				irmao = aux->Esq;
				aux->Dir = NULL;
				break;
			}
			aux=aux->Dir;
		}
		else
		{
			if((aux->Dir != NULL)&&(!tipo(aux->Esq)))
			{
				pai = aux;	//"pai" atualiza se filho de aux tiver outro irmao e filho de aux for interno
 				lado = 1;
 			}
 			if(tipo(aux->Esq))
 			{
 				if(aux->Dir->Item.Chave != x) return 0; //nao encontrou elemento
				irmao = aux->Dir;
				aux->Esq = NULL;
				break;
 			}
 			aux=aux->Esq;
		}
		digito++;
	}
	//cout << "valor a ser retirado: " << aux->Item.Chave << endl; //debug
	//cout << "valor do filho do pai: " << pai->Dir->Item.Chave << endl; //debug
	//cout << "valor dos sobrinhos: " << irmao->Dir->Item.Chave << endl; //debug
	//cout << "valor dos sobrinhos: " << irmao->Esq->Item.Chave << endl; //debug
	if(!tipo(irmao)) return 1;	//Se o irmao tiver os dois filhos esta feito.
	switch(lado)
	{
		case 0:
			pai->Dir = irmao;
			return 1;
		case 1:
			pai->Esq = irmao; 
			return 1;
	}
}

int main()
{
	// Implemente o seu programa principal aqui!
	int n, chave;
	TItem item;
	TArvBin arvore = NULL;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> item.Chave;
		//cout << "inserindo " << item.Chave; //debug
		Insere(&arvore,item);
	}
	cin >> chave;
	item.Chave = chave;
	Pesquisa(arvore,chave)!=NULL?Retira(&arvore,chave):Insere(&arvore,item);
	Imprime(arvore);

	return 0;
}