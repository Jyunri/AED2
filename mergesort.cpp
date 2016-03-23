#include <iostream>
using namespace std;

int* interpolate(int* array, int n, int* aux)
{
    int q = n-1;
    int p = q+1-n;
    int r = q/2;
    int k = q;
    for(int i = p;i<=r;i++) aux[i] = array[i];
    for(int j = r+1;j<=q;j++,k--) aux[j] = array[k];
}

int* mergeRecursive(int* array, int n, int* aux)
{
    if(n == 1)  return array;
    int q = n-1;
    int p = q+1-n;
    int r = q/2;
    mergeRecursive(array,r-p+1,aux);    //r-p+1 eh o numero de elementos entre p ate a metade
    mergeRecursive(array,q-r+1,aux);    //q-r+1 eh o numero de elementos entre a metade ate o q
    interpolate(array,q-p+1,aux);
}

int* merge(int* array, int n)
{
    int* aux;
    mergeRecursive(array,n,aux);
}

int main()
{
    int n;
    cin >> n;
    int array[n], aux[n];
    for(int i =0; i<n; i++) cin >> array[i];
    merge(array,n);
    return 0;
}
