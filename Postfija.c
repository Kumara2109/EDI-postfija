#include <stdio.h>
#include <string.h>
#define TAM_PILA 10

typedef struct
{
    char operadores[TAM_PILA];
    int tope;
    
}Pila;


void inicializaPila(Pila *p);
int apila(Pila *p, char operador);
int desapila(Pila *p);
void capturaOp(char op[21]);
void transPostfija(Pila *p, char op[21], int *i);

int main()
{
    Pila pila;
    int i = 0;
    char op[21];
    
    capturaOp(op);
    transPostfija(&pila,op,&i);
    /*while(pila.tope>0)
        desapila(&pila);
    printf("\n");*/
}

void transPostfija(Pila *p, char op[21], int *i)
{
    
    if ((op[*i]>=65 && op[*i]<=90) || (op[*i]>=97 && op[*i]<=122)) //ASCII 65-90=A-Z / 97-122=a-z
    {
        printf("%c",op[*i]);
        (*i)++;
        transformaPostfija(p,op,i);
    }
    else if (op[*i]=='(')
    {
        apila(p,op[*i]);
        (*i)++;
        transformaPostfija(p,op,i);
    }
    else if (op[*i]=='*' || op[*i]=='/')
    {
        if (p->operadores[p->tope]=='*' || p->operadores[p->tope]=='/')
        {
            desapila(p);
            transformaPostfija(p,op,i);
        }
        apila(p,op[*i]);
        (*i)++;
        transformaPostfija(p,op,i);
    }
    else if (op[*i]=='+' || op[*i]=='-')
    {
        if(p->operadores[p->tope]=='*' || p->operadores[p->tope]=='/')
        {
            desapila(p);
            transformaPostfija(p,op,i);
        }
        else if(p->operadores[p->tope]=='+' || p->operadores[p->tope]=='-')
        {
            desapila(p);
            transformaPostfija(p,op,i);
        }
        apila(p,op[*i]);
        (*i)++;
        transformaPostfija(p,op,i);
    }
    else if(op[*i]==')')
    {
        do
        {
            desapila(p);
        }while (p->operadores[p->tope]!='(');
        (*i)++;
        transformaPostfija(p,op,i);
    }
    else if(op[*i]==' ')
    {
        while(p->tope>0)
            desapila(p);
        printf("\n");
    }
}

void capturaOp(char op[21])
{
    
    printf("Ingresa la operación infija que se desea transformar a postfija\n");
    printf("\t-no use espacios\n");
    printf("\t-max 20 caracteres\n");
    scanf("%s",&op[0]);
    fflush(stdin);
    op[strlen(op)+1]=' ';
}

int apila(Pila *p, char operador)
{
    int pudoApilar = 0;

    if(p->tope < TAM_PILA - 1)
    {
        p->tope++;
        p->operadores[p->tope] = operador;
        
        pudoApilar = 1;
    }
    
    return pudoApilar;
}

int desapila(Pila *p)
{
    int pudoDesapilar = 0;
    
    if(p->tope > -1)
    {
        if (p->operadores[p->tope]!='(')
        printf("%c",p->operadores[p->tope]);
        p->tope--;
        pudoDesapilar = 1;
    }
     
    return pudoDesapilar;
}

void inicializaPila(Pila *p)
{
    p->tope = -1;
}
