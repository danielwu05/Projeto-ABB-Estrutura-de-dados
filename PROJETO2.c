#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>



int main() {
    srand(time(NULL));
    int opcao;
    Arvore *arvore = IniciaArvore();
    do {
        system("cls");
        printf("\n=== SISTEMA DE VENDAS ===\n");
        printf("1. Inserir nova venda\n");
        printf("2. Listar todas as vendas\n");
        printf("3. Buscar vendas por vendedor\n");
        printf("4. Listar vendas acima/abaixo de valor\n");
        printf("5. Exibir estatisticas\n");
        printf("6. Remover venda\n");
        printf("7. Finalizar sistema\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        empty_stdin();
        switch (opcao){
            case 1:
                 inserirNovaVenda(arvore);
                break;
            case 2:
                imprimeArvore(arvore);
                break;
            case 3:
                menuBuscarVendedor(arvore);
                break;
            case 4:
                Venda_maior_menor(arvore);
                break;
            case 5:
                estatisticas(arvore);
                break;
            case 6:
                arvore = removerVenda(arvore);
                break;
            case 7:
                RemoveArvore(arvore);
                return 0;
                break;
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
                break;
        }
    if (opcao != 7){
        printf("\nPressione Enter para continuar...");
    }
    }while(opcao<8);
    return 0;
}
