
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

void percorreArvore(NoArvore* arvore, char *vendedorBuscado, char* matricula, int *encontrou)
{
    if (arvore != NULL)
{
    if (strcasecmp(arvore->info.vendedor, vendedorBuscado) == 0 && *encontrou == 0)
    {
        strcpy(matricula, arvore->info.matricula);
        *encontrou = 1;
    }

    percorreArvore(arvore->left, vendedorBuscado, matricula, encontrou);
    percorreArvore(arvore->right, vendedorBuscado, matricula, encontrou);
}
}

int VaziaArvore(Arvore* arvore) {
    if (arvore->raiz == NULL)
    {
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

void LiberaNos(NoArvore* no)
{
        if(no->right != NULL)
        {
            LiberaNos(no->right);
        }
        if(no->left != NULL)
    {
        LiberaNos(no->left);
    }
        free(no);
}

Arvore* RemoveArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL)
    {
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
            if (no -> left != NULL)
            {
                contagem = quantidadeNos(no -> left, contagem);
            }
            if (no -> right != NULL)
            {
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


void imprimeNo(NoArvore* no)
{
    printf("%d | %s | %s | %s | %02d/%02d/%04d | R$ %.2f\n",no->info.id, no->info.vendedor, no->info.matricula,no->info.cliente, no->info.data.dia, no->info.data.mes,no->info.data.ano, no->info.valor);
}

void imprimeVendas(NoArvore* no) {
    printf("%d | %s | %02d/%02d/%04d | R$ %.2f\n",
           no->info.id, no->info.cliente, no->info.data.dia,
           no->info.data.mes, no->info.data.ano, no->info.valor);
}

void imprimeAcimaouAbaixo(NoArvore* no, float valor, int o)
{
    if(no!= NULL)
{

    imprimeAcimaouAbaixo(no->left, valor, o);

    if (o == 1 && no->info.valor > valor)
    {
        imprimeNo(no);
    }
    else if (o == 2 && no->info.valor < valor)
    {
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
    { // Ordem decrescente: direita, raiz, esquerda
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
    printf("\nCrescente [1] ou Decrescente [2]?: ");
    scanf("%d", &opt);

    if (opt == 1 || opt == 2)
         {
            printf("\nID | Vendedor | Matrícula | Cliente | Data de Transacao | Valor(R$)\n");
            printf("-------------------------------------------------------------------\n");
            imprimearvoreOrder(arvore->raiz, opt);
        }
    else
        {
            printf("\nValor inserido invalido\n");
        }
}
}



float somaValores(NoArvore* raiz)
{
    int soma = 0;
    if (raiz == NULL)
    {
        return 0;
    }
    else
{
    soma= raiz->info.valor + somaValores(raiz->right) + somaValores(raiz->left);
}
    return soma;
}




#endif // ARVORE_H_INCLUDED
