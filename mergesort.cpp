#include <iostream>
#include <stdio.h>
using namespace std;

void printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)
    {
        cout << array[i] <<",";
    }
    cout << endl;
}

int* interpolate(int* array, int n, int* aux)
{
    int q = n-1;
    int p = q+1-n;
    int r = q/2;
    int k = q;
    int a = p;
    int b = q;
    for(int i = p;i<=r;i++) aux[i] = array[i];
    for(int j = r+1;j<=q;j++,k--) aux[j] = array[k];
    cout << "Pre Interpolate:" << endl;
    printArray(array,n);
    for(k=p;k<=q;k++)
    {   
        if(aux[a]<=aux[b])
        {
            array[k] = aux[a];
            a++;
        }
        else
        {
            array[k] = aux[b];
            b--;
        }
    }     
    cout << "Interpolate Result:" << endl;
    printArray(array,n);
    return array;
}

int* mergeRecursive(int* array, int n, int* aux)
{
    if(n == 1)  return array;
    mergeRecursive(array,n/2,aux);    //r-p+1 eh o numero de elementos entre p ate a metade
    //mergeRecursive(array,n/2,aux);    //q-r+1 eh o numero de elementos entre a metade ate o q
    return interpolate(array,n,aux);
}

int* merge(int* array, int* aux, int n)
{
    mergeRecursive(array,n,aux);
}

int main()
{
    int n;
    cin >> n;
    int array[n], aux[n];
    for(int i =0; i<n; i++) cin >> array[i];
    merge(array,aux,n);
    printArray(array,n);
    return 0;
}
