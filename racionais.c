#include <stdio.h>

typedef struct
{
    int Numerador;
    int Denominador;
}TNumeroRacional;

int initialize(TNumeroRacional *numero)
{
    if(numero==NULL)    return 0;
    printf("Digite o numerador\n");
    scanf("%d",&numero->Numerador);

    printf("Digite o denominador\n");
    scanf("%d",&numero->Denominador);

    printf("\n"); 
    return 1;
}

float soma(TNumeroRacional a, TNumeroRacional b)
{
    float num = ((b.Denominador*a.Numerador) + (a.Denominador*b.Numerador));
    float den = a.Denominador * b.Denominador;
    return num/den;
}

float subtracao(TNumeroRacional a, TNumeroRacional b)
{
    float num = ((b.Denominador*a.Numerador) - (a.Denominador*b.Numerador));
    float den = a.Denominador * b.Denominador;
    return num/den;
}

float multiplicacao(TNumeroRacional a,TNumeroRacional b)
{
    float num = a.Numerador * b.Numerador;
    float den = a.Denominador * b.Denominador;
    return num/den;
}

float divisao(TNumeroRacional a, TNumeroRacional b)
{
    float num = a.Numerador * b.Denominador;
    float den = a.Denominador * b.Numerador;
    return num/den;
}

int iguais(TNumeroRacional a,TNumeroRacional b)
{
    return (a.Numerador/a.Denominador)==(b.Numerador/b.Denominador);
}

void main(){
    TNumeroRacional a;
    TNumeroRacional b;
    initialize(&a);
    initialize(&b);
    printf("Qual operacao vc deseja executar?\n1-Soma\n2-Subtracao\n3-Multiplicacao\n4-Divisao\n5-Iguais\n");
    int choice;
    getchar();
    scanf("%d",&choice);
    switch(choice){
        case 1: printf("%.2f\n",soma(a,b)) ; break;
        case 2: printf("%.2f\n",subtracao(a,b)); break;
        case 3: printf("%.2f\n",multiplicacao(a,b)) ; break;
        case 4: printf("%.2f\n",divisao(a,b)) ; break;
        case 5: if (iguais(a,b)) printf("iguais\n"); else printf("diferentes\n"); break;
    }
}
