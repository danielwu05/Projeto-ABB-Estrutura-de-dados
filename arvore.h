#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define COUNT 5 // remover dps иж teste
/*
int VaziaArvore (Raiz * arvore)// - retorna 1 se for nulo e 0 se nao for o caso
Raiz* RemoveArvore (Raiz* arvore)// - remove a arvore inteira
Arvore * encontraMenor (Arvore* arvore)// /- encontra o menor valor da raiz e retorna o seu endereco
Arvore* RemoveGalho (Arvore* arvore, int achar) - remove o no da arvore contendo o valor procurado
Arvore* InsereArvore (Arvore* root, int info) - insere no na arvore


*/


typedef struct Tree {
    int id;
    char cliente[50];
    char vendedor[50];
    int matricula;
    int data, mes, ano;
    float valor;
    struct Tree* left;
    struct Tree* right;
}Arvore;

typedef struct Root {
    struct Tree * root;
}Raiz;
Raiz* IniciaArvore () {
    return NULL;
}
int VaziaArvore (Raiz * arvore) {
    if (arvore -> root == NULL) {
        return 1;
    }
    return 0;
}

int generateRandomValue(int option) {
    srand(time(NULL));
    if(option % 2 == 0){
        return (rand()%(1000 - 9999)+1000);
    }
    else{
        return (rand()%(0 - 9));
    }

}

int BuscarArvore (Arvore* root, int info) {
    if (root == NULL) {
        return 0;
    }
    if (root -> id == info) {
        return 1;
    }
    if (info > root -> id) {
        return BuscarArvore(root->right, info);
    }
    else if (info < root -> id) {
        return BuscarArvore(root->left, info);
    }
}

Arvore * encontraMenor (Arvore* arvore) {
    if (arvore == NULL) {
        return NULL;
    }
    while (arvore -> left != NULL) {
        arvore = arvore -> left;
    }
    return arvore;
}
Arvore* RemoveGalho (Arvore* arvore, int achar) {
    int aux;
    system("cls");
    if (arvore == NULL) {
        printf("\n n existe\n");
        return NULL;
    }
    else {
        if (arvore -> data < achar) {
            arvore -> right = RemoveGalho(arvore -> right, achar);
        }
        else if (arvore -> data > achar) {
            arvore -> left = RemoveGalho(arvore -> left, achar);
        }
        else{
            if (arvore -> left == NULL && arvore -> right == NULL) {
                free (arvore);
                printf("\nremovido c/ sucesso\n");
                return NULL;
            }
            else if (arvore -> left == NULL) {
                Arvore *aux = arvore -> right;
                free (arvore);
                printf("\nremovido c/ sucesso\n");
                return aux;
            }
            else if (arvore -> right == NULL) {
                Arvore *aux = arvore -> left;
                free (arvore);
                printf("\nremovido c/ sucesso\n");
                return aux;
            }
            else {
                Arvore *aux = encontraMenor(arvore -> right);
                arvore -> data = aux -> data;
                arvore -> right = RemoveGalho(arvore -> right , aux -> data);
            }
        }
        return arvore;
    }
}
void LiberaArvore (Arvore* arvore) {
    LiberaArvore(arvore -> left);
    LiberaArvore(arvore -> right);
    free(arvore);
}
Raiz* RemoveArvore (Raiz* arvore) {
    if (arvore == NULL) {
        return NULL;
    }
    LiberaArvore(arvore -> root);
    free(arvore);
    return NULL;
}
int quantidadeNos (Arvore* arvore, int contagem) {
        if (arvore!=NULL){
            contagem++;
            if (arvore -> left == NULL && arvore -> right == NULL) {
                return contagem;
            }
            if (arvore -> left != NULL) {
                contagem = quantidadeNos(arvore -> left, contagem);
            }
            if (arvore -> right != NULL) {
                contagem = quantidadeNos(arvore -> right, contagem);
            }
        }
        return contagem;
}

Arvore* InsereArvore (Arvore* root, int id, char cliente, char vendedor, int matricula, int data, int mes, int ano, float valor) {
    system("cls");
    if (root == NULL) {
        Arvore * NovoNo = (Arvore*) malloc (sizeof(Arvore));
        NovoNo -> id = id;
        strcpy(NovoNo -> cliente,&cliente);
        strcpy(NovoNo -> vendedor,&vendedor);
        NovoNo -> data = data;
        NovoNo -> mes = mes;
        NovoNo -> ano = ano;

        NovoNo -> left = NovoNo -> right = NULL;
        printf("\ninserido c/ sucesso\n");
        return NovoNo;
    }
        if (id > root -> id) {
            root -> right = InsereArvore(root, id, cliente, vendedor, matricula, data, mes, ano, valor);
        }
        else if (id < root -> id) {
            root -> left = InsereArvore(root, id, cliente, vendedor, matricula, data, mes, ano, valor);
        }
    return root;
}

void imprimeNo(Arvore * arvore){
    printf("%d | %s | V%d | %s | %2d/%2d/%d | %.2f", arvore->id, arvore->vendedor, arvore->cliente, arvore->data, arvore->mes, arvore->ano, arvore->valor);
}

void imprimeVendas(Arvore * arvore){
    printf("%d | %s | %2d/%2d/%d | %.2f", arvore->id, arvore->vendedor, arvore->data, arvore->mes, arvore->ano, arvore->valor);
}

void imprimeAcimaouAbaixo(Arvore *arvore, float valor, int o){
    if(o%2 == 1){ //maior que o valor
            if(valor>arvore->valor){
                imprimeNo(arvore);
            }
    }
    else{ //menor que o valor
            if(valor<arvore->valor){
                imprimeNo(arvore);
            }
    }
    imprimeAcimaouAbaixo(arvore->left, valor, o);
    imprimeAcimaouAbaixo(arvore->right, valor, o);
}

void imprimearvoreOrder(Arvore *arvore, int o){
        if(o%2==1){
            imprimearvoreOrder(arvore->left,o);
            imprimeNo(arvore);
            imprimearvoreOrder(arvore->right,o);
        }
        else{
            imprimearvoreOrder(arvore->right,o);
            imprimeNo(arvore);
            imprimearvoreOrder(arvore->left,o);
        }
}
//tirar e coloca na main depois
void imprimeArvore(Arvore * arvore){
    int opt;
    do{
        printf("\nCrescente [1] ou Decrescente [2]?: ");
        scanf("%d",&opt);
        if(opt == 1) {
            imprimearvoreOrder(arvore, opt);
        }
        else if(opt == 2) {
             imprimearvoreOrder(arvore, opt);
        }
        else {
            printf("\nValor inserido invalido\n");
        }
    }while(opt < 0 || opt >2);
}


#endif // ARVORE_H_INCLUDED
