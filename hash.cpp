#include <iostream>

using namespace std;

typedef struct
{
	int Chave;
}TItem;


typedef struct
{
	TItem *Item;
	int m, n;
}THash;

THash* cria(int m)
{
	THash *newHash;
	newHash = (THash*)malloc(sizeof(THash));	//Alocar tabela hash
	newHash->n = 0;	//A tabela inicia sem nenhum elemento
	newHash->m = m;	//Armazena tamanho da tabela
	newHash->Item = (TItem*)malloc(m*sizeof(TItem));	//Alocar vetor de itens da tabela
	for(int i = 0; i<m; i++)	newHash->Item[i].Chave = NULL;	//cada item deve iniciar como nulo
	return newHash;
}

void imprime(THash* hash)
{
	for(int i = 0; i<(hash->m);i++)
	{
		cout << "[" << i << "]";
		for(int i = 0; i)
		cout << endl;

	}
}

int pesquisa()
{
	return 0;
}

int insere()
{
	return 0;

}

int remove()
{
	return 0;

}

int main()
{
	THash* hash;
	int m,n, elemento;
	cin >> m;
	cin >> n;
	hash = cria(m);
	hash -> Item[0].Chave = 9;
	// for(int i = 1; i<=n; i++)
	// {
	// 	cin >> elemnto;
	// 	insere(elemento);
	// }
	//cin >> elemento;
	//pesquisa(elemento)?insere(elemento):remove(elemento);
	imprime(hash);




}