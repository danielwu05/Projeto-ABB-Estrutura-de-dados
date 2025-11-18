#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


NoArvore* inserirNovaVenda(Arvore* arvore)
{
    NoArvore *nova = (NoArvore*)malloc(sizeof(NoArvore));
    Data data;
    char cliente[51];
    char vendedor[51];
    char matricula[5];
    float valor;
    int id;

    printf("\n=== Cadastro de Nova Venda ===\n");

    int min = 1000;
    int max = 9999;

    id = (rand() % (max - min + 1)) + min;

    printf("ID gerado: %d\n", id);

    while (getchar() != '\n');

    printf("Digite o nome do Cliente: ");
    fgets(cliente,51,stdin);

    printf("Digite o nome do Vendedor: ");
    fgets(vendedor,51,stdin);

    gerarMatricula(matricula);
    printf("Matricula gerada : %s\n", matricula);


    printf("Digite a data (dia mes ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    printf("Digite o valor da venda: ");
    scanf("%f", &valor);

    printf("\nVenda confirmada!\n");

    arvore->raiz = InsereArvore(arvore->raiz, id, cliente, vendedor, matricula, data, valor);

    return arvore->raiz;
}



void estatisticas(Arvore *arvore)
{
    if (!VaziaArvore(arvore))
{
    int totalVendas = quantidadeNos(arvore->raiz, 0);
    float faturamentoTotal = somaValores(arvore->raiz);

    printf("\n=== Estatisticas ===\n");
    printf("Total de vendas: %d\n", totalVendas);
    printf("Faturamento total: R$ %.2f\n", faturamentoTotal); //Apenas fiz isso para garantir que o numero seja no formato pedido de 2 casas decimais
}

}


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

        switch (opcao)
        {
            case 1:
                 inserirNovaVenda(arvore);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                break;
            case 5:
                estatisticas(arvore);
                break;
            case 6:

                break;
            case 7:
                RemoveArvore(arvore);
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    if (opcao != 7)
    {
    printf("\nPressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
    }
    }

    while(opcao!=7);

    return 0;

}
