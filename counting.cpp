#include <iostream>
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

int* counting(int* a,int* b, int* c, int n,int k)
{
    acumula(c,k);
    for(int i = n-1; i>=0; i--)
    {
        b[c[a[i]]-1] = a[i];
        c[a[i]]--;
    }
    for(int j = 0; j<n; j++)
        a[j] = b[j];
} 

int maiorChave(int* array,int n)
{
    int max = 0;
    for(int i =0; i<n;i++)
        if(array[i]>max)    max = array[i];
    return max;
}

int main()
{
    int n, k;
    cin >> n;
    int a[n],b[n];
    for(int i =0; i<n;i++)  cin >> a[i];
    k = maiorChave(a,n)+1;
    int* c = (int*)calloc(k,sizeof(int));
    for(int j=0; j<n; j++)
    {
        c[a[j]]++;
    }
    counting(a,b,c,n,k);  
    printArray(a,n);
}
        
