#include <iostream>

using namespace std;

void imprimeVetor(int vetor[], int n)
{
	for(int i = 1; i <=n; i++)	cout << vetor[i] << ",";
}

int shift(int org,int j,int k)
{
	int t = ((k+(j-1))%org);	//imita hash/lista circular.
	return t!=0?t:org;
}

int main()
{
	int n;	//numero de vertices
	int arcototal = 0;	//perimetro do poligono inicial
	int maiorArco = 0;	//ira definir a menor razao possivel da PA do poligono regular
	int menorArco;	//ira definir a maior razao possivel da PA do poligono regular
	cin >> n;
	int arco;
	int distancia[n+1];	//vetor de distancia entre vertice i ate a ORIGEM 0. (normalizado para comecar no indice 1)

	for(int i = 1; i <=n; i++)
	{
		cin >> arco;
		if(arco>maiorArco)	maiorArco = arco;	//calcula maior arco
		arcototal+=arco;	//calcula perimetro do arco
		distancia[i] = arcototal;	//calcula posicoes ocupadas
	}
	menorArco = arcototal/3;	//calcula a maxima razao

	int posicao[arcototal];	//vetor de posicoes dos vertices
	for(int i = 1; i<=arcototal; i++)	posicao[i] = 0;	//nenhuma posicao ocupada
	for(int i = 1; i<=n; i++)	posicao[distancia[i]] = 1;	//insere as posicoes ocupadas no vetor de posicao

	int retira = 0;
	int retiraMin = arcototal;


	//testa as razoes possiveis da PA gerando um vetor ideal de posicoes a partir de cada vertice

	int ideal[arcototal+1];	//crio um vetor ideal que vai servir de gabarito

	for(int i =  maiorArco; i<=menorArco; i++)
	{
		for(int m = 1; m <= arcototal; m++)	ideal[m] = 0;	//inicializo vetor ideal
		int pa = 1;	//primeiro termo da pa eh 1
		while(pa<=arcototal)
		{
			ideal[pa] = 1;	//popula o vetor ideal seguindo a regra das razoes
			pa+=i;	//incrementa com razao;
		}

		//a partir de cada vertice origem
		 for(int j = 1; j <= n; j++)
		 {
			//percorrendo cada vertice a partir de origem
			for(int k = 1; k <=arcototal; k++)
			{
				int translada = shift(arcototal,j,k);	//quantidade de vezes que deve transladar a posicao inicial
				//cout << translada;	//debug
				if(ideal[k])	//tem que ter vertice
				{
					if(!posicao[translada])
					{
						retira = arcototal;	//valor alto para nao servir mesmo
						break;	//nao tem vertice. vertice nao serve para fazer poligono
					}
				}
				else	//nao pode ter vertice
				{
					if(posicao[translada])
					{
						//cout << "retirou na posicao " << translada; //debug
						retira++;	//tenho que retirar esse vertice
					}
				}
			}
			if(retira < retiraMin) retiraMin = retira;	//menor numero de nos necessarios
			//cout << " retira: " <<retiraMin; //debug
			//cout << endl; //debug;
			retira = 0;	//reinicia retira
		}
	}

	if((n-retiraMin) < 3) retiraMin = -1;	//nao da pra retirar pois nao se forma poligono com menos de 3 lados
	//cout << maiorArco << endl; // debug;
	//cout << menorArco << endl; // debug;
	//cout << arcototal << endl; // debug;

	// //debug
	// cout << "Vetor distancia";
	// imprimeVetor(distancia,n);
	// cout << endl;
	// cout << "Posicoes ocupadas no arco: ";
	// imprimeVetor(posicao,arcototal);
	// cout << endl;
	// cout << "Vetor ideal: ";
	// imprimeVetor(ideal,arcototal);
	// cout << endl;
	// //debug

	cout << retiraMin;

	return 0;
}