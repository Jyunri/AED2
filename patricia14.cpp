/*input
4
K M L D
K


14
K M L D F C A Y N E Z W B J
C


7
3 4 9 2 5 1 8
5

2
1 2
2

3
2 1 5
5

*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef char TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem; 

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
	int digito;
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
    else	cout << "D" << a->digito;	//imprime digito se for no interno
    Imprime(a->Esq);
    Imprime(a->Dir);
    cout << ")";
    return 0;
}

int retornaDigito(TChave x, int digito)
{
	return (((x-64) >> digito) & 1);
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

TArvBin Pesquisa(TArvBin Raiz, TChave x)
{
	// Implemente o seu metodo aqui!
	if(Raiz==NULL)	return NULL;
	if(!tipo(Raiz))	//no interno
	{
		if(retornaDigito(x,Raiz->digito))	return Pesquisa(Raiz->Dir, x);
		else return Pesquisa(Raiz->Esq,x);
	}
	if(Raiz->Item.Chave == x)	return Raiz;	//no externo, pesquisa com sucesso
	return NULL;	//no externo, pesquisa sem sucesso
}

TArvBin criaNoInterno(int separa,TArvBin Esq, TArvBin Dir)
{
	TArvBin no = (TArvBin)malloc(sizeof(TNo));
	no->digito = separa;
	no->Esq = Esq;
	no->Dir = Dir;
	return no;
}

int Separa(TArvBin *pRaiz, TArvBin *pNo, TItem x)
{
	int separa = 0;	//diz em que digito a chave eh diferente da raiz
	int before = 1;	//diz se vai inserir antes ou depois da raiz da arvore
	while(1)
	{
		if(retornaDigito((*pNo)->Item.Chave, separa) != retornaDigito(x.Chave, separa))	break;
		separa++;
	}
	//percorre a arvore novamente
	TArvBin *no = pRaiz;

	//se no for externo ou separa for menor que o digito atual (ok, pode inserir)
	if(tipo(*pNo)||(((*pNo)->digito)<separa))
	{
	//se digito for 0	cria no interno, atribuindo um novo no a esquerda e atribui o no atual a direita
	//se digito for 1	cria no interno, atribuindo um novo no a direita e atribui o no atual a esquerda
		if(retornaDigito(x.Chave,separa))	*pNo = criaNoInterno(separa,criaNo(x),*pNo);
		else								*pNo = criaNoInterno(separa,*pNo,criaNo(x));
	}

	//se no for interno ou separa for maior que o digito atual
	else
	{
	//se digito for 0, tenta criar no interno a esquerda
		Separa(pRaiz, &(*pNo)->Esq, x);
	//se digito for 1, tenta criar no interno a direita
		Separa(pRaiz, &(*pNo)->Dir, x);
	}

/*
	while(!tipo(*no)&&((*no)->digito<separa))	//enquanto for no interno e digito do *no for menor que separa
	{
		if(retornaDigito(x.Chave,(*no)->digito))	no = no->Dir;
		else	no = no->Esq;
		before = 0;
	}

	cout << "Endereco da raiz da arvore 3 : "<< *pRaiz << endl;
	cout << "Endereco do no 3: "<< *no << endl;


	if(!tipo(*no))cout << "digito do *no: " << (*no)->digito << endl;
	if(!tipo(*no))cout << "digito da raiz: " << (*pRaiz)->digito << endl;
	else cout << "valor do *no: " << (*no)->Item.Chave << endl;

	novo = *no;

	//Criando novo no
	(*no) = (TArvBin)malloc(sizeof(TNo));
	(*no)->digito = separa;

	//Colocando os filhos do novo no
	if(retornaDigito(x.Chave, separa))	//digito do novo no eh 1
	{
		(*no)->Dir = criaNo(x);
		(*no)->Esq = novo;
	}
	else
	{
		(*no)->Esq = criaNo(x);
		(*no)->Dir = novo;
	}
	if(!tipo(*no))cout << "digito do *no: " << (*no)->digito << endl;
	if(!tipo(*no))cout << "digito da raiz: " << (*pRaiz)->digito << endl;

	cout << "Endereco do novo *no: "<< novo << endl;
	cout << "Endereco do *no: "<< *no << endl;
	cout << "Endereco da raiz da arvore: "<< *pRaiz << endl;
	if(before)	*pRaiz = *no;
	Imprime(*pRaiz);
	cout << endl;
	*/
	return 0;
}

int InsereRec(TArvBin *pRaiz, TArvBin *pNo, TItem x)
{
	if((*pNo) == NULL){
		(*pNo) = criaNo(x);	//arvore nula
		return 1;
	}
	else if(tipo(*pNo))	//no externo
	{
		if((*pNo)->Item.Chave == x.Chave)	return 0;	//ja existe
		return Separa(pRaiz,pNo,x);
	}
	return retornaDigito(x.Chave,(*pNo)->digito)?InsereRec(pRaiz, (&(*pNo)->Dir), x):InsereRec(pRaiz, (&(*pNo)->Esq), x);
}

//trigger
int Insere(TArvBin *pRaiz, TItem x)
{
	// Implemente o seu metodo aqui!
	cout << "valor a ser inserido: " << x.Chave << endl;
	InsereRec(pRaiz,pRaiz,x);
	cout << endl;
}

int Retira(TArvBin *pRaiz, TChave x)
{
	// Implemente o seu metodo aqui!
	if(*pRaiz==NULL)	return 0;
	TArvBin aux = *pRaiz;
	TArvBin pai = *pRaiz;
	TArvBin irmao;
	int lado, d;
	while(!tipo(aux))	//enquanto for no interno
	{
		d = (aux)->digito;
		if(retornaDigito(x,d))	//encaminha para direita
		{
			//cout << pai->digito << endl;
			if(tipo(aux->Dir))	//filho eh externo, candidato a ser quem queremos retirar
			{
				if(aux->Dir->Item.Chave != x) return 0; //nao encontrou elemento
				//cout << "valor a ser retirado: " << aux->Dir->Item.Chave << endl; //debug
				irmao = aux->Esq;
				aux->Dir = NULL;
				*aux = *irmao;
				//if(tipo(irmao))	(pai->Dir) = irmao;	//se irmao for externo, pai a esquerda recebe irmao
				//else pai = irmao;	//se irmao for externo, o irmao substitui o pai
				break;
			}
			pai = aux;	//se proximo aux for interno, pai recebe antigo aux
			aux = aux->Dir;
		}
		else
		{
			//cout << pai->digito << endl;
			if(tipo(aux->Esq))	//filho eh externo, candidato a ser quem queremos retirar
			{
				if(aux->Esq->Item.Chave != x) return 0; //nao encontrou elemento
				//cout << "valor a ser retirado: " << aux->Esq->Item.Chave << endl; //debug
				irmao = aux->Dir;
				aux->Esq = NULL;
				//if(tipo(irmao))	(pai->Esq) = irmao;	//se irmao for externo, pai a esquerda recebe irmao
				//else pai = irmao;	//se irmao for externo, o irmao substitui o pai
				*aux = *irmao;
				break;
			}
			pai = aux;	//se proximo aux for interno, pai recebe antigo aux
			aux = aux->Esq;
		}
	}
	if((*pRaiz)->Item.Chave==x)	*pRaiz = NULL;
	//cout << "valor do filho do pai: " << pai->Dir->Item.Chave << endl; //debug
	//cout << "valor dos sobrinhos: " << irmao->Dir->Item.Chave << endl; //debug
	//cout << "valor dos sobrinhos: " << irmao->Esq->Item.Chave << endl; //debug
}

int main()
{
	// Implemente o seu programa principal aqui!
	int n;
	TChave chave;
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
	//if(Pesquisa(arvore,chave)!=NULL)	cout <<	 "arvore encontrada"; //debug
	//Pesquisa(arvore,chave)!=NULL?Retira(&arvore,chave):Insere(&arvore,item);
	Imprime(arvore);

	return 0;
}