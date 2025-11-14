#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define COUNT 5 // remover dps иж teste
/*
int VaziaArvore (Raiz * arvore) - retorna 1 se for nulo e 0 se nao for o caso
Raiz* RemoveArvore (Raiz* arvore) - remove a arvore inteira
Arvore * encontraMenor (Arvore* arvore) - encontra o menor valor da raiz e retorna o seu endereco
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
        return (rand()%(1000 - 9999));
    }
    else{
        return (rand()%(0 - 9));
    }

}

int BuscarArvore (Arvore* root, int info) {
    if (root == NULL) {
        return 0;
    }
    if (root -> data == info) {
        return 1;
    }
    if (info > root -> data) {
        return BuscarArvore(root->right, info);
    }
    else if (info < root -> data) {
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

int alturaArvore(Arvore *arvore){
        if (arvore == NULL) {
            return  -1;
        }
        else {
            int direita = alturaArvore(arvore->right);
            int esquerda = alturaArvore(arvore->left);
            direita = (direita > esquerda) ? direita : esquerda;
            return 1+ direita;
        }
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
// teste remover depois
void print2DUtil(Arvore* root, int space) {
    if (root == NULL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
    print2DUtil(root->left, space);
}
void print2D(Arvore* root) {
    print2DUtil(root, 0);
}

#endif // ARVORE_H_INCLUDED
