#include <stdio.h>

typedef struct{
    int n;
    int inteiros[20];
}TConjunto;

TConjunto criarConjunto(){
    TConjunto conjunto;
    conjunto.n = 0;
    return conjunto;
}

void lerConjunto(TConjunto *c){
    printf("Insira o numero de elementos do conjunto\n");
    scanf("%d",&c->n); 
    printf("Insira os elementos do conjunto\n");
    for(int i =0; i<(c->n); i++){
        scanf("%d",&c->inteiros[i]);
    }
}

int is_there(int array[],int n, int value){
    for(int i=0;i<n;i++){
        if (array[i] == value)  return 1;
    }
    return 0;
}

int * fUniao(TConjunto c1, TConjunto c2){
    TConjunto uniao = criarConjunto(); 
    int posicaoUniao = 0; 
    for(int i=0; i<c1.n ; i++)
    {
        uniao.inteiros[i] = c1.inteiros[i];
        uniao.n++;
    }
    for(int j=0;j<c2.n; j++)
    {
        if(!is_there(uniao.inteiros,uniao.n,c2.inteiros[j]))
        {
            uniao.inteiros[c1.n+posicaoUniao]=c2.inteiros[j];
            posicaoUniao++;
            uniao.n++;            
        }
    }   
    printf("A uniao dos conjuntos eh:\n"); 
    for(int i =0; i < uniao.n ; i++)
    {
        printf("%d,",uniao.inteiros[i]);
    } 
    printf("\n");    
    return uniao.inteiros;
}

int * fIntercecao(TConjunto c1, TConjunto c2){
    TConjunto intercecao = criarConjunto(); 
    for(int i = 0; i < c1.n; i++)
    { 
        for(int j=0;j<c2.n; j++)
        {
            if(c1.inteiros[i] == c2.inteiros[j])
            {
                if(!is_there(intercecao.inteiros,intercecao.n,c2.inteiros[j]))
                {
                    intercecao.inteiros[intercecao.n]=c2.inteiros[j];
                    intercecao.n++;            
                }
            }
        }   
    } 
    printf("A intercecao dos conjuntos eh:\n"); 
    for(int i =0; i < intercecao.n ; i++)
    {
        printf("%d,",intercecao.inteiros[i]);
    }
    printf("\n");    
    return intercecao.inteiros; 
}

int fIguais(TConjunto c1, TConjunto c2)
{
    int match = 0;
    for(int i = 0; i < c1.n; i++)
    {
        for(int j = 0; j <c2.n; j++)
        {
            if(c1.inteiros[i] == c2.inteiros[j])
            {
                match = 1; //encontrou elemento no c2
                break;
            }
        }
        if(match == 0)  return 0;
        match = 0;
    }
    for(int i = 0; i < c2.n; i++)
    {
        for(int j = 0; j <c1.n; j++)
        {
            if(c1.inteiros[j] == c2.inteiros[i])
            {
                match = 1; //encontrou elemento no c2
                break;
            }
        }
        if(match == 0)  return 0;
        match = 0;
    }
    return 1;
} 

void fImprime(TConjunto c)
{
    for(int i = 0; i < c.n ; i++)
        printf("%d, ",c.inteiros[i]);
    printf("\n");
}

void main(){
    TConjunto c1 = criarConjunto();
    TConjunto c2 = criarConjunto();
    lerConjunto(&c1);
    lerConjunto(&c2);
    fUniao(c1,c2);    
    fIntercecao(c1,c2);
    printf(fIguais(c1,c2)?"Conjuntos iguais\n":"Conjuntos diferentes\n");
    fImprime(c1);
    fImprime(c2);
}
