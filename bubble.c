#include <stdio.h>

void printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)
    {
        printf("%d ",array[i]);
    }
    puts(" ");
}

int * bubble(int* array, int n)
{
    int aux;
    int count = 0;
    int move = 0;

    printf("Bubble sort:\n\n");
    printArray(array,n);

    for(int i = n-1; i>1; i--)
    {
        for(int j = 0; j<i; j++)    
        {
            if(array[j]>array[j+1])
            {
              aux = array[j+1];
              array[j+1] = array[j];
              array[j] = aux; 
              move++;
            }
        }
        printArray(array,n);
        count++;
        if(move == 0)   break;
        move = 0;
    }
    printf("\nNumero de iteracoes: %d", count);
    puts("");
    puts("");
    return array;
}


int main()
{   
   int array[7] = {3,4,9,2,5,1,8}; 
   bubble(array,7);
} 
