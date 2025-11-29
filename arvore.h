#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct dados
{
    int id;
    char cliente[51];
    char vendedor[51];
    char matricula[5];
    Data data;
    float valor;
}Dados;

typedef struct NoArvore {
    Dados info;
    struct NoArvore* left;
    struct NoArvore* right;
} NoArvore;

typedef struct Arvore {
    struct NoArvore *raiz;
} Arvore;


Arvore* IniciaArvore() {
    Arvore* novaArvore = (Arvore*)malloc(sizeof(Arvore));
    if (novaArvore != NULL) {
        novaArvore->raiz = NULL;
    }
    return novaArvore;
}

void empty_stdin (void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}




char * percorreArvore(NoArvore* arvore, char *a){
    if (arvore != NULL){
        if(strcasecmp(arvore->info.vendedor, a)==0){
            return arvore->info.matricula;
        }
        char* matricula = percorreArvore(arvore->left, a);
        if (matricula != NULL) {
            return matricula;
        }
        matricula = percorreArvore(arvore->right, a);
        if (matricula != NULL) {
            return matricula;
        }
        return NULL;
    }
    return NULL;
}

int VaziaArvore(Arvore* arvore) {
    if (arvore->raiz == NULL){
        return 0;
    }
    return 1;
}

void gerarMatricula(char* matricula) {
    int num = rand() % 1000;
    sprintf(matricula, "V%03d", num);
}

int generateRandomID()
{
    return (rand() % (9999 - 1000 + 1)) + 1000;
}

int BuscarArvore(NoArvore* root, int info) {
    if (root == NULL) {
        return 0;
    }
    if (root->info.id == info) {
        return 1;
    }
    if (info > root->info.id) {
        return BuscarArvore(root->right, info);
    }
    else {
        return BuscarArvore(root->left, info);
    }
}

NoArvore* encontraMaior(NoArvore* no) {
    if (no == NULL) {
        return NULL;
    }
    while (no->right != NULL) {
        no = no->right;
    }
    return no;
}

NoArvore* RemoveGalho(NoArvore* no, int achar) {

    if (no == NULL)
    {
        return NULL;
    }

    if (achar < no->info.id) {
        no->left = RemoveGalho(no->left, achar);
    }
    else if (achar > no->info.id) {
        no->right = RemoveGalho(no->right, achar);
    }
    else {
        if (no->left == NULL && no->right == NULL) {
            free(no);
            printf("\nRemovido com sucesso\n");
            return NULL;
        }
        else if (no->left == NULL) {
            NoArvore* temp = no->right;
            free(no);
            printf("\nRemovido com sucesso\n");
            return temp;
        }
        else if (no->right == NULL) {
            NoArvore* temp = no->left;
            free(no);
            printf("\nRemovido com sucesso\n");
            return temp;
        }
        else {
            NoArvore* aux = encontraMaior(no->left);
            no->info = aux->info;
            no->left = RemoveGalho(no->left, aux->info.id);
        }
    }
    return no;
}

void LiberaNos(NoArvore* no){
    if(no->right != NULL){
            LiberaNos(no->right);
        }
        if(no->left != NULL){
        LiberaNos(no->left);
    }
        free(no);
}

Arvore* RemoveArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL){
        return NULL;
    }
    LiberaNos(arvore->raiz);
    free(arvore);
    return NULL;
}

int quantidadeNos (NoArvore* no, int contagem) {
        if (no!=NULL)
        {
            contagem++;
            if (no -> left == NULL && no -> right == NULL) {
                return contagem;
            }
            if (no -> left != NULL) {
                contagem = quantidadeNos(no -> left, contagem);
            }
            if (no -> right != NULL) {
                contagem = quantidadeNos(no -> right, contagem);
            }
        }
        return contagem;
}

NoArvore* InsereArvore(NoArvore* root, int id, char* cliente, char* vendedor, char* matricula, Data data, float valor)
{
if (root == NULL)
    {
        NoArvore* NovoNo = (NoArvore*)malloc(sizeof(NoArvore));
        if (NovoNo == NULL)
    {
            return NULL;
    }

        NovoNo->info.id = id;
        strcpy(NovoNo->info.cliente, cliente);
        strcpy(NovoNo->info.vendedor, vendedor);
        strcpy(NovoNo->info.matricula, matricula);
        NovoNo->info.data = data;
        NovoNo->info.valor = valor;

        NovoNo->left = NULL;
        NovoNo->right = NULL;

        printf("\nVenda ID %d inserida com sucesso.\n", id);
        return NovoNo;
    }

    if (id < root->info.id) {
        root->left = InsereArvore(root->left, id, cliente, vendedor, matricula, data, valor);
    }
    else if (id > root->info.id) {
        root->right = InsereArvore(root->right, id, cliente, vendedor, matricula, data, valor);
    }

    return root;
}

void desenharLinha() {
    printf("+--------+-----------------+-----------+-----------------+------------+-------------+\n");
}

void desenharDivisor() {
    printf("+--------+-----------------+------------+-------------+\n");
}

void lerTexto(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void imprimeNo(NoArvore* no) {
    printf("| %-6d | %-15.15s | %-9s | %-15.15s | %02d/%02d/%04d | R$ %9.2f |\n",no->info.id,no->info.vendedor,no->info.matricula,no->info.cliente,no->info.data.dia, no->info.data.mes, no->info.data.ano,no->info.valor);
}

void imprimeNoBusca(NoArvore* no) {
    if (no != NULL){
        printf("| %06d | %-15.15s | %02d/%02d/%04d | R$ %9.2f |\n",no->info.id,no->info.cliente,no->info.data.dia, no->info.data.mes, no->info.data.ano,no->info.valor);
    }
}

void imprimeVendas(NoArvore* no) {
    printf("%d | %s | %02d/%02d/%04d | R$ %.2f\n",
           no->info.id, no->info.cliente, no->info.data.dia,
           no->info.data.mes, no->info.data.ano, no->info.valor);
}

void imprimeAcimaouAbaixo(NoArvore* no, float valor, int o)
{
    if(no!= NULL){
    imprimeAcimaouAbaixo(no->left, valor, o);
    if (o == 1 && no->info.valor > valor){
        imprimeNo(no);
    }
    else if (o == 2 && no->info.valor < valor){
        imprimeNo(no);
    }
    imprimeAcimaouAbaixo(no->right, valor, o);
    }
}

void imprimearvoreOrder(NoArvore* no, int o)
{
    if(no != NULL)
{

    if (o == 1)
    {
        imprimearvoreOrder(no->left, o);
        imprimeNo(no);
        imprimearvoreOrder(no->right, o);
    } else
    {
        imprimearvoreOrder(no->right, o);
        imprimeNo(no);
        imprimearvoreOrder(no->left, o);
    }

}
}



void imprimeArvore(Arvore* arvore)
{
        if (arvore->raiz == NULL)
    {
        printf("\n Nenhuma venda cadastrada\n");
    }
else
{

    int opt;
        printf("\n=== LISTAGEM GERAL DE VENDAS ===\n");
        printf("Escolha a ordem:\n");
        printf("[1] Crescente (ID)\n");
        printf("[2] Decrescente (ID)\n");
        printf("Opcao: ");
        scanf("%d", &opt);
        empty_stdin();
    if (opt == 1 || opt == 2)
    {
        printf("\n=== LISTAGEM DE VENDAS ===\n");
        desenharLinha();
        printf("| %-6s | %-15s | %-9s | %-15s | %-10s | %-11s |\n",
               "ID", "Vendedor", "Matricula", "Cliente", "Data", "Valor");
        desenharLinha();

        imprimearvoreOrder(arvore->raiz, opt);

        desenharLinha();
    }
    else
        {
            printf("\nValor inserido invalido\n");
        }
}
    system("pause");
}

float somaValores(NoArvore* raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    return raiz->info.valor + somaValores(raiz->left) + somaValores(raiz->right); // fiz essa funçao de somar recursivamente ;
}



NoArvore* inserirNovaVenda(Arvore* arvore)
{
    NoArvore *nova = (NoArvore*)malloc(sizeof(NoArvore));
    Data data;
    struct tm *hoje;
    time_t segundos;
    time(&segundos);
    hoje = localtime(&segundos);
    Dados dados;

    printf("\n==================================\n");
    printf("                    CADASTRO DE NOVA VENDA      \n");
    printf("==================================\n");

    int min = 1000;
    int max = 9999;

    dados.id = (rand() % (max - min + 1)) + min;

    printf("ID gerado: %d\n", dados.id);
    printf("Digite o nome do Cliente: ");
    lerTexto(dados.cliente,50);

    printf("Digite o nome do Vendedor: ");
    lerTexto(dados.vendedor,50);
   char* matriculaEncontrada = percorreArvore(arvore->raiz, dados.vendedor);

   int confirmacao;
    if (matriculaEncontrada != NULL)
    {
        printf("\nATENCAO: Vendedor '%s' ja encontrado com matricula [%s].\n", dados.vendedor, matriculaEncontrada);
        do {
            printf("Deseja usar este cadastro existente? \n");
            printf("[1] Sim;\n");
            printf("[2] Nao;\n");
            printf("Opcao: ");
            scanf("%d", &confirmacao);
            empty_stdin();

            if (confirmacao != 1 && confirmacao != 2) printf("Opcao invalida.\n");
        } while (confirmacao != 1 && confirmacao != 2);

        if (confirmacao == 1) {
            strcpy(dados.matricula, matriculaEncontrada);
            printf(">> Matricula mantida: %s\n", dados.matricula);
        } else {
            gerarMatricula(dados.matricula);
            printf(">> Nova matricula gerada: %s\n", dados.matricula);
        }
    }
    else
    {
        gerarMatricula(dados.matricula);
        printf(">> Novo vendedor. Matricula gerada: %s\n", dados.matricula);
    }
    do {
        printf("Digite a data de nascimento (dd mm aaaa):\n");
        scanf("%d %d %d", &dados.data.dia, &dados.data.mes, &dados.data.ano);
        empty_stdin();
        if(dados.data.dia>31 || dados.data.dia <1 || dados.data.mes <1 || dados.data.mes>12 || dados.data.ano<1990 || dados.data.ano >hoje->tm_year+1900 || ((dados.data.dia>hoje->tm_mday && dados.data.mes>=hoje->tm_mon+1) || dados.data.ano>hoje->tm_year+1900)){
            printf("Data invalida\n");
        }
  }while(dados.data.dia>31 || dados.data.dia <1 || dados.data.mes <1 || dados.data.mes>12 || dados.data.ano<1990 || dados.data.ano >hoje->tm_year+1900 || ((dados.data.dia>hoje->tm_mday && dados.data.mes>=hoje->tm_mon+1) || dados.data.ano>hoje->tm_year+1900));
    do{
        printf("Digite o valor da venda: ");
        if(scanf("%f", &dados.valor) == 0) {
             printf("Valor invalido (digite apenas numeros)\n");
             empty_stdin();
             dados.valor = -1;
        } else {
             empty_stdin();
        }
    } while(dados.valor <= 0);
    printf("\nVenda confirmada!\n");
    arvore->raiz = InsereArvore(arvore->raiz, dados.id, dados.cliente, dados.vendedor, dados.matricula, dados.data, dados.valor);
    return arvore->raiz;
}
void buscarVendasVendedor(NoArvore *no, char *busca, int porMatricula)
{
    if(no!=NULL)
    {
            if ((porMatricula && strcasecmp(no->info.matricula, busca) == 0) || (!porMatricula && strcasecmp(no->info.vendedor, busca) == 0))
                {
                    imprimeNo(no);
                }
    buscarVendasVendedor(no->right, busca, porMatricula);
    buscarVendasVendedor(no->left, busca, porMatricula);
    }
    else
    {
        printf("Nao ha venda registrada");
    }
}
void buscarFuncaoTres(NoArvore *no, char *palavra, int opcao){
     if(no != NULL){
        if(opcao == 1){
            if (strcasecmp(no->info.matricula, palavra) == 0){
                imprimeNoBusca(no);
            }
            buscarFuncaoTres(no->right, palavra,opcao);
            buscarFuncaoTres(no->left, palavra,opcao);
        }
        else{
            if (strcasecmp(no->info.vendedor, palavra) == 0)
            {
                imprimeNoBusca(no);
            }
            buscarFuncaoTres(no->right, palavra,opcao);
            buscarFuncaoTres(no->left, palavra,opcao);
        }
    }
 }
void buscarPorNome(NoArvore *no, char *nome)
{
    if(no != NULL)
{
    if (strcasecmp(no->info.vendedor, nome) == 0)
    {
        imprimeNo(no);
    }
    buscarPorNome(no->right, nome);
    buscarPorNome(no->left, nome);
}
}

void menuBuscarVendedor(Arvore *a){
    int opcao;
    char busca[51];
    if ((VaziaArvore(a))==0){
        printf("\n>> Nenhuma venda cadastrada para buscar.\n");
        system("pause");
    }
else{
    do{
        printf("\n=== BUSCAR VENDAS ===\n");
        printf("1. Por Matricula\n");
        printf("2. Por Nome\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        empty_stdin();
        if(opcao < 1 || opcao > 2){
                printf("\nOpcao de busca invalida.\n");
                system("pause");

        }
    }while(opcao > 2 || opcao <= 0);
    if (opcao == 1)
    {
        printf("Digite a matricula (ex: V000): ");
        lerTexto(busca,50);
    }
    else
    {
        printf("Digite o nome do vendedor: ");
        lerTexto(busca,50);
    }
        desenharDivisor();
        printf("| %-6s | %-15s | %-10s | %-11s |\n",
               "ID", "Cliente", "Data", "Valor");
        desenharDivisor();
        buscarFuncaoTres(a->raiz, busca,opcao);
        system("pause");




}
}

void Venda_maior_menor(Arvore *arvore)
{
    if(arvore->raiz == NULL)
    {
        printf("\nNao ha vendas registradas no momento\n");
        system("pause");
    }
    else
    {
        float valor;
        int opcao;
        printf("\n=== FILTRAR POR VALOR ===\n");
        printf("[1] Listar vendas MAIORES que X\n");
        printf("[2] Listar vendas MENORES que X\n");
        printf("Escolha a opcao: ");
        scanf("%d", &opcao);
        empty_stdin();

        do{
            printf("Digite o valor de referencia (R$): ");
        if(scanf("%f", &valor) == 0) {
             printf("Valor invalido (digite apenas numeros)\n");
             empty_stdin();
             valor = -1;
        } else {
             empty_stdin();
        }
    } while(valor <= 0);
        desenharLinha();
        printf("| %-6s | %-15s | %-9s | %-15s | %-10s | %-11s |\n",
           "ID", "Vendedor", "Matricula", "Cliente", "Data", "Valor");
        desenharLinha();
        imprimeAcimaouAbaixo(arvore->raiz,valor,opcao);
        system("pause");
    }
}
void estatisticas(Arvore *arvore)
{
    if (VaziaArvore(arvore)== 1){
    int totalVendas = quantidadeNos(arvore->raiz, 0);
    float faturamentoTotal = somaValores(arvore->raiz);
    float Media = faturamentoTotal / totalVendas;
    if(totalVendas == 0){
        Media = 0.0;
    }
        printf("\n");
        printf("+---------------------------+-------------------+\n");
        printf("|    RESUMO DE VENDAS       |      VALORES      |\n");
        printf("+---------------------------+-------------------+\n");
        printf("| Total de Vendas           | %-17d |\n", totalVendas);
        printf("+---------------------------+-------------------+\n");
        printf("| Faturamento Total (Bruto) | R$ %-14.2f |\n", faturamentoTotal);
        printf("+---------------------------+-------------------+\n");
        printf("| Ticket Medio por Venda    | R$ %-14.2f |\n", Media);
        printf("+---------------------------+-------------------+\n");

}
    else
    {
        printf("\n[!] Nao ha vendas registradas para gerar estatisticas.\n");    }
        system("pause");
}
Arvore* removerVenda(Arvore*arvore){
    int id;
    if ((VaziaArvore(arvore))==1){
    printf("\n Remover Venda\n");
    printf("Digite o ID da venda a ser removida: ");
    scanf("%d", &id);
    empty_stdin();
    if (BuscarArvore(arvore->raiz, id)){
        printf("\nVenda removida!\n");
        arvore->raiz = RemoveGalho(arvore->raiz, id);
        system("pause");
        return arvore;
    }
    else{
        printf("Venda com ID %d nao encontrada!\n", id);
        system("pause");
        return arvore;
    }
    }

else
{
        printf("\nNenhuma venda cadastrada para remover.\n");
        return arvore;
}
}
#endif // ARVORE_H_INCLUDED
