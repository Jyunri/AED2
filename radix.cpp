#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)    cout <<array[i]<<" ";
}

int acumula(int* c, int k)
{
    for(int i=1; i<k;i++)
        c[i]+=c[i-1];
}

//recebe o valor correspondente ao digito. Ex: 234. f(234,2) = 3
int valorDigito(int numero,int indice)
{
    return (numero / (int)pow(10, indice)) % 10;
}

int maiorChave(int* array,int n,int digito)
{
    int max = 0;
    for(int i =0; i<n;i++)
        if(valorDigito(array[i],digito)>max)    max = array[i];
    return max;
}

int* counting(int* a,int n, int digito)
{
    int b[n];
    int k = maiorChave(a,n,digito)+1;
    int* c = (int*)calloc(k,sizeof(int));
    for(int j=0; j<n; j++)    c[valorDigito(a[j],digito)]++;
    acumula(c,k);
    for(int i = n-1; i>=0; i--)
    {
        b[c[valorDigito(a[i],digito)]-1] = a[i];
        c[valorDigito(a[i],digito)]--;
    }
    for(int j = 0; j<n; j++)
        a[j] = b[j];
    
    free(c);
} 

int maisSignificativo(int* array,int n)
{
    int max = 0;
    int digito;
    for(int i =0; i<n;i++)
    {
        digito = (int)ceil(log10(array[i]));
        if(digito>max)   max = digito;
    }
    return max;
}

int radix(int* a, int n)
{
    int d = maisSignificativo(a,n);
    for(int i = 0; i<d; i++)
        counting(a,n,i);
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i =0; i<n;i++)  cin >> a[i];
    radix(a,n);
    printArray(a,n);
}
        
