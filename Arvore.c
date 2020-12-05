/*
REMOVER
EHARVOREAVL no MENU
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Arvore.h"
void Menu()
{
    int nNodos, i, numRandom, op, altura;
    printf("| Digite o numero de nodos: ");
    scanf("%d", &nNodos);
    if (nNodos <= 0)
    {
        printf("| Saindo\n");
        return;
    }
    //Declaro raiz
    TipoNo **pRaiz = (TipoNo **)malloc(sizeof(TipoNo *));
    if (!pRaiz)
    {
        printf("ERRO MEMORIA MENU\n");
        exit(1);
    }
    *pRaiz = NULL;
    //Gerar numero aleatorio
    srand(time(0));
    printf("| Preenchendo arvore\n");
    for (i = 0; i < nNodos; i++)
    {
        //Insere numeros aleatorios gerados
        numRandom = rand() % 100;
        printf("| Inserindo: %d ", numRandom);
        Inserir(pRaiz, numRandom);
    }
    while (1)
    {
        //Exibe menu de opcoes
        printf("| 1 - Imprimir\n");
        printf("| 2 - Altura\n");
        printf("| 3 - Sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            //Imprimir arvore
            Print(*pRaiz);
            printf("\n");
            break;
        case 2:
            //Altura da arvre
            altura = Altura(*pRaiz);
            printf("| Altura eh: %d\n", altura);
            break;
        case 3:
            //Sair
            printf("| Arvore eh avl: ");
            i = EhArvoreAvl(pRaiz);
            if(i==1)
                printf("TRUE\n");
            else 
                printf("FALSE\n");
            Sair(pRaiz);
            return;
            break;
        default:
            Sair(pRaiz);
            return;
            break;
        }
    }
}
void Print(TipoNo *pRaiz)
{  
    //Se raiz for nula, volta
    if(pRaiz==NULL)
    {
        return;
    }
    else
    {
        //Manda imprimir filho esquerdo, nodo, filho direito
        Print(pRaiz->pLeft);
        printf("%d ",pRaiz->info.valor);
        Print(pRaiz->pRight);
    }
}
int Inserir(TipoNo **pRaiz, int numRandom)
{
    //Se raiz/nodo for nulo
    if (*pRaiz == NULL)
    {
        //Aloca memoria e salva os dados
        //Aponta pro nodo
        TipoNo *pNodo = (TipoNo *)malloc(sizeof(TipoNo));
        if (!pNodo)
        {
            printf("ERRO MEMORIA INSeRIR\n");
            exit(1);
        }
        pNodo->info.valor = numRandom;
        pNodo->pLeft = NULL;
        pNodo->pRight = NULL;
        *pRaiz = pNodo;
        printf(" - OK\n");
        return 1;
    }
    else if ((*pRaiz)->info.valor > numRandom)
    {
        //Se o valor for menor, insere no lado esquerdo
        if (Inserir(&(*pRaiz)->pLeft, numRandom))
        {
            Balancear(pRaiz);
            return 1;
        }
        else
            return 0;
    }
    else if ((*pRaiz)->info.valor < numRandom)
    {
        //Se o valor for maior, insere no lado direito
        if (Inserir(&(*pRaiz)->pRight, numRandom))
        {
            Balancear(pRaiz);
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
void GiraDir(TipoNo **pRaiz)
{
    //Faz o giro pra direita
    //Nodo recebe o filho esquerdo
    //Filho esquerdo recebe o filho direito do nodo
    //FIlho direito do nodo recebe o pai
    //Pai recebe o nodo
    TipoNo *pNodo;
    pNodo = (*pRaiz)->pLeft;
    (*pRaiz)->pLeft = pNodo->pRight;
    pNodo->pRight = (*pRaiz);
    (*pRaiz) = pNodo;
}
void GiraEsq(TipoNo **pRaiz)
{
    //Faz o giro pra esquerda
    //Nodo recebe o filho direito
    //Filho direito recebe o filho esquerdo do nodo
    //FIlho esquerdo do nodo recebe o pai
    //Pai recebe o nodo
    TipoNo *pNodo;
    pNodo = (*pRaiz)->pRight;
    (*pRaiz)->pRight = pNodo->pLeft;
    pNodo->pLeft = (*pRaiz);
    (*pRaiz) = pNodo;
}
int Balancear(TipoNo **pRaiz)
{
    //Fator de balanceamento
    //Se for maior de 1 ou menor de -1
    //Siginifica que esta desbalanceada
    //Pra direita ou pra esquerda
    int fator;
    fator = FB(*pRaiz);
    if (fator > 1)
    {
        return CorrigeEsq(pRaiz);
    }
    else if (fator < -1)
    {
        return CorrigeDir(pRaiz);
    }
    return 0;
}
int CorrigeEsq(TipoNo **pRaiz)
{
    int fatorEsq;
    fatorEsq = FB((*pRaiz)->pLeft);
    if (fatorEsq > 0)
    {
        GiraDir(pRaiz);
        return 1;
    }
    else if (fatorEsq < 0)
    {
        GiraEsq(&(*pRaiz)->pLeft);
        GiraDir(&(*pRaiz));
        return 1;
    }
    return 0;
}
int CorrigeDir(TipoNo **pRaiz)
{
    int fatorDir;
    fatorDir = FB((*pRaiz)->pRight);
    if (fatorDir < 0)
    {
        GiraEsq(pRaiz);
        return 1;
    }
    else if (fatorDir > 0)
    {
        GiraDir(&(*pRaiz)->pRight);
        GiraEsq(&(*pRaiz));
        return 1;
    }
    return 0;
}
int Altura(TipoNo *pRaiz)
{
    int alturaEsq, alturaDir;
    if (pRaiz == NULL)
        return 0;
    alturaEsq = Altura(pRaiz->pLeft);
    alturaDir = Altura(pRaiz->pRight);
    if (alturaEsq > alturaDir)
        return (alturaEsq + 1);
    else
        return (alturaDir + 1);
}
int FB(TipoNo *pRaiz)
{
    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->pLeft) - Altura(pRaiz->pRight);
}
void Sair(TipoNo **pRaiz)
{
    if (pRaiz == NULL)
        return;
    Clear(*pRaiz);
    free(pRaiz);
}
void Clear(TipoNo *pRaiz)
{
    if (pRaiz == NULL)
        return;
    Clear(pRaiz->pLeft);
    Clear(pRaiz->pRight);
    free(pRaiz);
}
int EhArvoreAvl(TipoNo *pRaiz)
{
    int fator;
    if (pRaiz == NULL)
        return 1;
    if (!EhArvoreAvl(pRaiz->pLeft))
        return 0;
    if (!EhArvoreAvl(pRaiz->pRight))
        return 0;
    fator = FB(pRaiz);
    if ((fator > 1) || (fator < -1))
        return 0;
    else
        return 1;
}