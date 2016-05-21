/*input

*/
#include <stdio.h>
#include <stdlib.h>

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

int retornaDigito(TChave x, int digito)
{
	return ((x >> digito) & 1);
}

TArvBin Pesquisa(TArvBin Raiz, TChave x)
{
	// Implemente o seu metodo aqui!
	if(Raiz==NULL)	return NULL;

}

int Insere(TArvBin *pRaiz, TItem x)
{
	// Implemente o seu metodo aqui!
	if(*pRaiz == NULL)	(*praiz)->Item = x;

}

int Retira(TArvBin *pRaiz, TChave x)
{
	// Implemente o seu metodo aqui!
}

int main()
{
	// Implemente o seu programa principal aqui!
	int n, int chave;
	TArvBin arvore = NULL;
	for(int i = 0; i < n; i++)
	{
		cin >>  chave;
		Insere(&arvore,chave);
	}
	cin >> chave;
	Pesquisa(arvore,chave)?Retira(&arvore,chave):Insere(&arvore,chave);
	Imprime(arvore);

	return 0;
}