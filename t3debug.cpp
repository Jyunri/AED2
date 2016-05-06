#include <iostream>
#include <stdlib.h>

using namespace std;

int** aloca(int altura, int largura)
{
	int **matriz;
	matriz = (int**)calloc(altura,sizeof(int*));
	for(int i = 0; i<altura; i++)
		matriz[i] = (int*)calloc(largura,sizeof(int));
	return matriz;
}

void freeMatriz(int** matriz,int altura)
{
	for(int i = 0; i<altura; i++)
		free(matriz[i]);
	free(matriz);
}

void imprime(int** matriz, int altura, int largura)
{
	for(int i = 0; i<altura; i++)
	{
		for(int j = 0; j<largura; j++)	cout << matriz[i][j] << " ";
		cout << endl;
	}
}

int maiorTamanho(int** matriz, int altura, int largura, int limiteInf, int limiteSup)
{
	int auxi, auxj;
	int diagonal = 0;
	int maior = 0;

	cout << "altura max: " << altura << endl;
	cout << "largura max: " << largura << endl;

	for(int i = 0; i < altura; i++)
	{
		for(int j = 0; j < largura; j++)
		{
			if(matriz[i][j] >= limiteInf)
			{
				auxi = i;
				auxj = j;
				cout << "Analisando: " << endl;
				while(matriz[auxi][auxj] <= limiteSup)
				{
					cout << matriz[auxi][auxj] << " ";
					diagonal++;
					if(auxj+1 >= largura)	break;
					if(auxi+1 >= altura)	break;
					auxj+=1;
					auxi+=1;
				}
				cout << endl;
				if(diagonal > maior) maior = diagonal;
				diagonal = 0;
			}
		}
		cout << endl;
	}
	return maior;
}

int main()
{
	int altura, largura;
	int consultas;
	int limiteInf, limiteSup;

	cin >> altura;
	cin >> largura;
	int** matriz;
	int** mconsultas;

	matriz = aloca(altura,largura);
	for(int i = 0; i<altura; i++)
		for(int j = 0; j<largura; j++)	cin >> matriz[i][j];

	cin >> consultas;
	mconsultas = aloca(consultas,2);
	for(int i = 0; i<consultas; i++)
		for(int j = 0; j<2; j++)	cin >> mconsultas[i][j];

	imprime(matriz,altura,largura);
	cout << endl;

	cout << "consultas: "<< consultas << endl;
	imprime(mconsultas,consultas,2);
	cout << endl;

	//
	for(int i = 0;  i < consultas; i++)
	{
		limiteInf = mconsultas[i][0];
		limiteSup = mconsultas[i][1];
		cout << maiorTamanho(matriz,altura,largura,limiteInf,limiteSup) << endl;
	}

	//free
	freeMatriz(matriz,altura);
	freeMatriz(mconsultas,2);

	return 0;
}
