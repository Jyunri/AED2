#include <iostream>
#include <stdlib.h>
using namespace std;

#define max 100000


//retorna tamanho de X-Y
int tamanhoSubtracao(int* x, int* y, int a, int b)
{
    int tam = 0;
    int* aux = (int*)calloc(max,sizeof(int));
    //for(int i = 0; i < a; i++)   aux[x[i]]++;
    for(int j = 0; j < b; j++)   aux[y[j]]++;
    for(int k = 0; k < a; k++)    
    { 
        if(aux[x[k]]==0)
        {
            tam++;
            aux[x[k]] = 1;
        } 
    }
    free(aux);
    return tam;
}
    
int menor(int a, int b)
{
    return a<b?a:b;
}

int main()
{
    int a, b;
    cin >> a;
    cin >> b;
    int x[a],y[b];
    for(int i = 0; i<a; i++)    cin >> x[i];
    for(int j = 0; j<b; j++)    cin >> y[j];
    cout << menor(tamanhoSubtracao(x,y,a,b),tamanhoSubtracao(y,x,b,a));
    return 0;
}
