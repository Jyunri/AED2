#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    char name;
    int ** matriz;
}TMatriz;

int initializeMatrix(TMatriz *m)
{
    printf("Digite o nome da matriz\n");
    scanf(" %c",&m->name);
    printf("Digite o tamanho da matriz\n");
    scanf("%d",&m->n);
    m->matriz = (int**)malloc((m->n)*sizeof(int*));
    for (int i =0; i < (m->n); i++)
    {
        m->matriz[i] = (int*)malloc((m->n)*sizeof(int));
    }
}

void freeMatrix(TMatriz *m)
{
    for (int i =0; i < (m->n); i++)
    {
        free(m->matriz[i]);
    }
    free(m->matriz);
}

void readMatrix(TMatriz *m)
{
    for (int i = 0; i < (m->n); i++)
    {
        for(int j = 0; j < (m->n); j++)
        {
            printf("Digte o valor da posicao %c[%d][%d]\n",m->name,i,j);
            scanf("%d",&m->matriz[i][j]);
        }
    }
}

int soma(TMatriz a, TMatriz b)
{
    if((a.n)!=(b.n))    return 0;
    puts("Soma das matrizes:");
    for (int i = 0; i < (a.n); i++)
    {
        for (int j = 0; j < (b.n); j++)
        {
            printf("%d ",a.matriz[i][j]+b.matriz[i][j]);
        }
        puts("");
    }
    return 1;
}

//TO-DO terminar funcao
int multiplica(TMatriz a, TMatriz b)
{
    if((a.n)!=(b.n))    return 0;
    int resultado = 0;
    puts("Multiplicacao das matrizes:");
    for (int i = 0; i < (a.n); i++)
    {
        for (int j = 0; j < (b.n); j++)
        {
            for (int k = 0; k < (b.n); k++)
            {
                resultado += a.matriz[i][k]*b.matriz[k][j];
            }        
            printf("%d ",resultado);
            resultado = 0;
        }
        puts("");
    }
}

void main()
{
    TMatriz t1, t2;
    initializeMatrix(&t1);    
    readMatrix(&t1);
    initializeMatrix(&t2);    
    readMatrix(&t2);
    if(!soma(t1,t2))    puts("Tamanhos diferentes");
    if(!multiplica(t1,t2))    puts("Tamanhos diferentes");
    freeMatrix(&t1);
    freeMatrix(&t2);
}
