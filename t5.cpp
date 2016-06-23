#include <iostream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector> //lista
#include <queue> //fila

using namespace std;
#define MAX 202

typedef struct
{
	int visitados[MAX][MAX][MAX];
	int capacidade_a, capacidade_b, capacidade_c;
}Tgrafo;

typedef struct
{
	int quantidade_a;
	int quantidade_b;
	int quantidade_c;
}TVertice;

int menor(int a, int b)
{
	return a<b?a:b;
}



void imprimeVisitados(Tgrafo *g)
{
	for(int i = 0; i<(g->capacidade_a)+1; i++)
	{
		for(int j = 0; j<(g->capacidade_b)+1; j++)
		{
			for(int k = 0; k < (g->capacidade_c)+1; k++)
				cout << "visitados[" <<i<<"]["<<j<<"]["<<k<<"]: "<<g->visitados[i][j][k]<< endl;
		}
	}
}


int getCapacidade(Tgrafo *g, int x)
{
	switch(x)
	{
		case 1: return g->capacidade_a;
		case 2: return g->capacidade_b;
		case 3: return g->capacidade_c;
	}
	return 0;
}

int getDestino(int a, int b, int c, int x)
{
	switch(x)
	{
		case 1: return a;
		case 2: return b;
		case 3: return c;
	}
	return 0;
}





void busca(Tgrafo *g,int a,int b, int c, int origem)
{
	queue<TVertice> fila;
	TVertice primeiro;

	//colocando o vertice origem na fila
	TVertice v_origem;
	v_origem.a = 0;
	v_origem.b = 0;
	v_origem.c = c;
	fila.push(v_origem)

	g->visitados[0][0][c] = 1;	//marcando origem como visitado

	while(!fila.empty())	//enquanto fila nao for vazia
	{
		TVertice primeiro = fila.front();	//pega primeiro da fila
		fila.pop();	//retira primeiro da fila

		for(int origem; origem <=3; origem++)	//considera os 3 baldes como origem
		{
			for(int destino = 1; destino <= 3; destino++)	//considera os 3 baldes como destino
			{
				if(destino != origem)	//se destino for diferente da origem
				{
					if(!g->visitados[a][b][c])
					{
						g->visitados[a][b][c] = 1;	//marca como visitado
						cout << "visitando vertice (" <<a<<","<<b<<","<<c<<")"<<endl;
						int c_origem = getCapacidade(g,origem);
						int r_destino = getCapacidade(g,destino)-getDestino(a,b,c,destino);
						int despejo = min(c_origem,r_destino);

						//desconta da origem
						switch(origem)
						{
							case 1: a-=despejo; break;
							case 2: b-=despejo; break;
							case 3: c-=despejo; break;
						}

						//adiciona ao destino
						switch(i)
						{
							case 1: a+=despejo; break;
							case 2: b+=despejo; break;
							case 3: c+=despejo; break;
						}

						cout << "a: " << a << endl;
						cout << "b: " << b << endl;
						cout << "c: " << c << endl;

					}
				}
			}
		}
	}
}


int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	Tgrafo *g = (Tgrafo*)malloc(sizeof(Tgrafo));
	g->capacidade_a = a;
	g->capacidade_b = b;
	g->capacidade_c = c;

	//definir todos os vertices como nao visitados
	for(int i = 0; i<a+1; i++)
	{
		for(int j = 0; j<b+1; j++)
		{
			for(int k = 0; k < c+1; k++)
				g->visitados[i][j][k] = 0;
		}
	}
	//g->visitados[0][0][c] = 1; //marca estado inicial como visitado

	busca(g,0,0,c,3);

	//imprimeVisitados(g);

	return 0;
}