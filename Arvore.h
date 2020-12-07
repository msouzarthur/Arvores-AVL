typedef struct
{
    int valor;
}TipoData;

typedef struct No
{
    TipoData info;
    struct No *pLeft;
    struct No *pRight;
} TipoNo;

void Menu();
void GiraDir(TipoNo **pRaiz);
void GiraEsq(TipoNo **pRaiz);
void Sair(TipoNo **pRaiz);
void Clear(TipoNo *pRaiz);
void Print(TipoNo *pRaiz, int i);
int Inserir(TipoNo **pRaiz, int numRandom);
int Balancear(TipoNo **pRaiz);
int CorrigeEsq(TipoNo **pRaiz);
int CorrigeDir(TipoNo **pRaiz);
int Altura(TipoNo *pRaiz);
int FB(TipoNo *pRaiz);
int EhArvoreAvl(TipoNo *pRaiz);
int Pesquisa(TipoNo *pRaiz, int valor);
int Remove(TipoNo **pRaiz, int valor);