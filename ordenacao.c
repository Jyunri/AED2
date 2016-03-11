#include <stdio.h>

void printArray(int* array, int n)
{
    for(int i = 0; i<n; i++)
    {
        printf("%d ",array[i]);
    }
    puts(" ");
}

int * insertion(int* array, int n)
{
    int count = 0;

    printf("Insertion sort:\n\n");
    printArray(array,n);

    for(int i = 2; i<n; i++){
        array[0] = array[i];
        for(int j = i-1; j>=0; j--)    
        {   
            if(array[0]>=array[j])
            {
                array[j+1] = array[0];
                break;
            }
            else
            {
                array[j+1]  = array[j];
            }
        }
        printArray(array,n);
        count++;
    }
    printf("\nNumero de iteracoes: %d", count);
    puts("");
    puts("");
    return array;
}

int * selection(int* array, int n)
{
    int aux;
    int count = 0;
    int min;
    
    printf("Selection sort:\n\n");
    printArray(array,n);

    for(int i = 0; i<n-1; i++)
    {
        min = i;
        for(int j = i; j<n; j++)    
        {
            if(array[min]>array[j]){
                min = j;
            }
        }

        aux = array[min];
        array[min] = array[i];
        array[i] = aux; 
        
        printArray(array,n);
        count++;
        
    }
    printf("\nNumero de iteracoes: %d", count);
    puts("");
    puts("");
    return array;
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
    int arrayB[7] = {3,4,9,2,5,1,8}; 
    int arrayI[8] = {0,3,4,9,2,5,1,8}; 
    int arrayS[7] = {3,4,9,2,5,1,8}; 
    bubble(arrayB,7);
    insertion(arrayI,8);
    selection(arrayS,7);
} 
