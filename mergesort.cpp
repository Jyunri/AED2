#include <iostream>
#include <stdio.h>
using namespace std;

void printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)
    {
        cout << array[i] <<" ";
    }
    cout << endl;
}

int* interpolate(int* array, int* aux, int p, int q, int r)
{
    int k = q;
    int a = p;
    int b = q;
    for(int i = p;i<=r;i++) aux[i] = array[i];
    for(int j = r+1;j<=q;j++,k--) aux[j] = array[k];
//    cout << "Pre Interpolate:" << endl;
//    printArray(array,n);
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
 //   cout << "Interpolate Result:" << endl;
 //  printArray(array,n);
    return array;
}

int* mergeRecursive(int* array,int p, int q, int* aux)
{
    int flag;
    if(p >= q)  return array;
    int r = (p+q)/2;
    mergeRecursive(array,p,r,aux);
    mergeRecursive(array,r+1,q,aux);
    interpolate(array,aux,p,q,r);
}

int* merge(int* array, int* aux, int n)
{
    mergeRecursive(array,0,n-1,aux);
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
