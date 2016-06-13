#include <iostream>
#include <vector>
#include <stdlib.h>
#define MAXVERTICES 1000

using namespace std;

typedef int TCusto;

typedef int TVertice;

typedef struct
{
	TCusto Custo;
}TAresta;

typedef struct
{
	TVertice Vertice;
	TAresta Aresta;
}TAdjacencia;

typedef struct
{
	vector<TAdjacencia> list[MAXVERTICES];
	int NVertices;
	int NArestas;
}TGrafo;

void imprimeListas(TGrafo *g)
{
	for(int i = 0; i < g->NVertices; i++)
	{
		cout << "[" <<i<<"]";
		for(int j = 0; j < g->list[i].size(); j++)	cout << g->list[i].at(j).Vertice << "("<< g->list[i].at(j).Aresta.Custo << ") ->";
		cout << endl;
	}
}


TVertice buscaMenorCaminho(TGrafo *g,int distancia[],int visitados[])
{
	int existe = 0;
	TVertice menor = -1;
	for(int i = 0; i<g->NVertices; i++)
	{
		if(!visitados[i])	//se o vertice nao foi visitado
		{
			if(distancia[i]>=0)	//se a distancia nao for infinita
			{
				//confirma que existiu pelo menos um vertice nao visitado alcancavel
				if(!existe)
				{
					existe = 1;
					menor = i;
				}
				else
				{
					if(distancia[i] < distancia[menor]) menor = i;	//atualiza menor caso necessario
				}
			}
		}
	}
	return menor;
}

void menorCaminho(TGrafo *g, TVertice inicial)
{
	TVertice menor;
	int distancia[g->NVertices];
	int antecessor[g->NVertices];
	int visitados[g->NVertices];
	for(int i = 0; i < g->NVertices; i++)
	{
		distancia[i] = -1;
		antecessor[i] = -1;
		visitados[i] = 0;
	}
	distancia[inicial] = 0;

	//debug
	for(int i = 0;i<g->NVertices;i++)	cout << distancia[i] << ", ";
	cout << endl;

	for(int i = 0; i< g->NVertices; i++)
	{
		//busca vertice com menor distancia ENTRE os vertice nao visitados (ja inclui o primeiro da fila de prioridade)
	 	menor = buscaMenorCaminho(g,distancia,visitados);
	 	if(menor == -1)	break;	//deu ruim, nao existe menor caminho alcancavel. No caso do ultimo vertice nao vai haver problema pois ele nao precisa alcancar ninguem.
	 	visitados[menor] = 1;	//indica que o vertice com menor caminho foi visitado

	 	//atualiza distancia dos vertices vizinhos ao menor caminho
	 	for(int i = 0; i < g->list[menor].size();i++)
	 	{
	 		if(distancia[g->list[menor].at(i).Vertice] == -1)	distancia[g->list[menor].at(i).Vertice] = g->list[menor].at(i).Aresta.Custo;
	 		else
	 		{
	 			//if(antecessor[menor] == -1)
	 			

	 		}
	 	}
	 	//debug
	 	cout << ""
	 	for(int i = 0;i<g->NVertices;i++)	cout << distancia[i] << ", ";
	 	cout << endl;
	}
}

int main()
{
	int n, m, u, v, p;
	TGrafo *g;
	g = (TGrafo*)malloc(sizeof(TGrafo));
	cin >> n >> m;
	g->NVertices = n+2;	//n eh o numero de pilares + borda + acampamento
	g->NArestas = m;

	//constroi grafo
	for(int i = 1; i <= m; i++)
	{
		cin >> u >> v >> p;
		TAdjacencia adj;
		adj.Vertice = v;
		adj.Aresta.Custo = p;
		g->list[u].push_back(adj);
	}

	menorCaminho(g, 0);
	imprimeListas(g);	//debug
}