#include <iostream>
using namespace std;

int global = 0;

void printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)    cout << array[i] << " ";
}

int* quickParticiona(int* array, int p, int r)
{
    if(p >= r) return array;
    int i = p-1;
    int q;
    int x = array[r];
    int aux;
    for(int j=p;j<=r-1;j++)
    {
        if(array[j] <= x)
        {
            i++;
            aux = array[j];
            array[j] = array[i];
            array[i] = aux;
        }
    } 
    //troca obrigatoria do seguinte a chave com o ultimo
    aux = array[i+1];
    array[i+1] = array[r];
    array[r] = aux;
    
    //para imprimir a primeira vez 
    if(global == 0)
    {
        printArray(array,r+1);
        global++;
    }

    q = i+1;
    quickParticiona(array,p,q-1);
    quickParticiona(array,q,r);
}

int quickSort(int* array, int n)
{
    quickParticiona(array,0,n-1);
}

int main()
{
    int n;
    cin >> n;
    int array[n];
    for(int i = 0; i<n; i++)    cin >> array[i];
    quickSort(array,n);
    cout << endl;
    printArray(array,n);
    return 0;   
}
