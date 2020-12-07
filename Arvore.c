/*
REMOVER
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
        numRandom = rand() % 10000;
        printf("| Inserindo: %d ", numRandom);
        Inserir(pRaiz, numRandom);
    }
    while (1)
    {
        //Exibe menu de opcoes
        printf("| 1 - Imprimir\n");
        printf("| 2 - Altura\n");
        printf("| 3 - Remover\n");
        printf("| 4 - Pesquisar\n");
        printf("| 5 - Sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            //Imprimir arvore
            i = 0;
            Print(*pRaiz, i);

            printf("\n");
            break;
        case 2:
            //Altura da arvre
            altura = Altura(*pRaiz);
            printf("| Altura eh: %d\n", altura);
            break;
        case 3:
            //Remover
            i = 0;
            Print(*pRaiz, i);
            printf("| Digite o numero para remover: ");
            scanf("%d", &i);
            if (Remove(pRaiz, i) == 1)
                printf("| Numero removido\n");
            else
                printf("| Numero nao removido\n");
            break;
        case 4:
            //Pesquisar
            i = 0;
            Print(*pRaiz, i);
            printf("| Digite o numero para pesquisar: ");
            scanf("%d", &i);
            if (Pesquisa(*pRaiz, i) == 1)
                printf("| Numero encontrado\n");
            else
                printf("| Numero nao encontrado\n");
            break;
        case 5:
            //Sair
            printf("| Arvore eh avl: ");
            i = EhArvoreAvl(*pRaiz);
            if (i == 1)
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

int Remove(TipoNo **pRaiz, int valor)
{
    TipoNo *pAux;
    if (pRaiz == NULL)
        return 0;
    if (Pesquisa(*pRaiz, valor) == 1)
    {
        printf("| Numero encontrado\n| Removendo...\n");
        return 1;
    }
    return 0;
}
int Pesquisa(TipoNo *pRaiz, int valor)
{
    if (pRaiz == NULL)
        return 0;
    if (pRaiz->info.valor == valor)
        return 1;
    else if (pRaiz->info.valor > valor)
        Pesquisa(pRaiz->pLeft, valor);
    else if (pRaiz->info.valor < valor)
        Pesquisa(pRaiz->pRight, valor);
}
void Print(TipoNo *pRaiz, int i)
{
    int aux;
    aux = 0;
    //Se raiz for nula, volta
    if (pRaiz == NULL)
    {
        return;
    }
    //Contador usado pros espacos
    i = i + 1;
    //Printa direito
    Print(pRaiz->pRight, i);
    for (aux = 0; aux < i; aux++)
        printf("\t");
    //Printa valor
    printf("%d\n", pRaiz->info.valor);
    //Printa esquerdo
    Print(pRaiz->pLeft, i);
    return;
    /*else
    {
        printf("[%d]",pRaiz->info.valor);
        if(pRaiz->pLeft!=NULL)
        {
            printf("\nEsquerda: ");
            Print(pRaiz->pLeft);
        }
        if(pRaiz->pRight!=NULL)
        {
            printf("\nDireita: ");
            Print(pRaiz->pRight);
        }
    }*/
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
            printf("ERRO MEMORIA INSERIR\n");
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
            //Faz o balanco pra reajustar
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
            //Faz o balanco pra reajustar
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
    //Faz os giros necessarios na esquerda
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
    //Faz os giros necessarios na direita
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
    //Calcula a altura dos lados
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
    //Diz a diferença de altura dos lados
    //pra saber se ta balanceado
    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->pLeft) - Altura(pRaiz->pRight);
}
void Sair(TipoNo **pRaiz)
{
    //Limpa a memoria
    if (pRaiz == NULL)
        return;
    Clear(*pRaiz);
    free(pRaiz);
}
void Clear(TipoNo *pRaiz)
{
    //Limpa a memoria dos nos
    if (pRaiz == NULL)
        return;
    Clear(pRaiz->pLeft);
    Clear(pRaiz->pRight);
    free(pRaiz);
}
int EhArvoreAvl(TipoNo *pRaiz)
{
    //Retorna se a arvore eh avl
    //Eh avl se o fator de balanceamento estiver entre -1 e 1
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