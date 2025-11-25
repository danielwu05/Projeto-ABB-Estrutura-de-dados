#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


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
    gets(cliente);

    printf("Digite o nome do Vendedor: ");
    gets(vendedor);


    int aconteceu = 0;
    percorreArvore(arvore->raiz,vendedor,matricula,&aconteceu);

    if(aconteceu==0)
        {
            gerarMatricula(matricula);
            printf("Matricula gerada e:%s\n",matricula);
        }
    else
    {
            printf("Vendedor ja registrado, matricula : %s\n", matricula);
    }



    printf("Digite a data (dia mes ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    printf("Digite o valor da venda: ");
    scanf("%f", &valor);

    printf("\nVenda confirmada!\n");

    arvore->raiz = InsereArvore(arvore->raiz, id, cliente, vendedor, matricula, data, valor);

    return arvore->raiz;
}



void buscarVendasVendedor(NoArvore *no, char *busca, int porMatricula)
{
    if(no!=NULL)
    {
            if ((porMatricula && strcmp(no->info.matricula, busca) == 0) || (!porMatricula && strcmp(no->info.vendedor, busca) == 0))
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


void buscarPorMatricula(NoArvore *no, char *matricula)
{
     if(no != NULL)
{
        if (strcmp(no->info.matricula, matricula) == 0)
    {
        imprimeNo(no);
    }

    buscarPorMatricula(no->right, matricula);
    buscarPorMatricula(no->left, matricula);
}
 }


void buscarPorNome(NoArvore *no, char *nome)
{
    if(no != NULL)
{
    if (strcmp(no->info.vendedor, nome) == 0)
    {
        imprimeNo(no);
    }
    buscarPorNome(no->right, nome);
    buscarPorNome(no->left, nome);
}
}

void menuBuscarVendedor(Arvore *a)
{
    int opcao;
    char busca[51];

    if ((VaziaArvore(a))==0)
    {
        printf("\nNenhuma venda cadastrada!\n");
    }

else{

    printf("\n=== Buscar Vendas por Vendedor ===\n");
    printf("1. Por Matricula\n");
    printf("2. Por Nome\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    while (opcao != '\n' || opcao != EOF){
        getchar();
    }

    if (opcao == 1)
    {
        printf("Digite a matricula (ex: V000): ");
        gets(busca);

        printf("\n--- Vendas Encontradas ---\n");
        printf("ID | Vendedor | Matricula | Cliente | Data de Transacao | Valor(R$)\n");
        printf("-------------------------------------------------------------------\n");
        buscarPorMatricula(a->raiz, busca);
    }
    else if (opcao == 2)
    {
        printf("Digite o nome do vendedor: ");
        gets(busca);

        printf("\n Vendas Encontradas \n");
        printf("ID | Vendedor | Matricula | Cliente | Data de Transacao | Valor(R$)\n");
        printf("-------------------------------------------------------------------\n");
        buscarPorNome(a->raiz, busca);
    }
    else {
        printf("\nOpcao de busca invalida.\n");
    }
}
}

void Venda_maior_menor(Arvore *arvore)
{
    if(arvore->raiz == NULL)
    {
        printf("Nao ha nenhuma venda registrada no momento");
    }
    else
    {
        float valor;
        int opcao;

        printf("Digite 1 para procurar vendas maiores ou 2 para vendas menores ");
        scanf("%d",&opcao);
        printf("Digite o valor de referencia:");
        scanf("%f",&valor);

        imprimeAcimaouAbaixo(arvore->raiz,valor,opcao);
    }
}

void estatisticas(Arvore *arvore)
{
    if (VaziaArvore(arvore)== 1)
{
    int totalVendas = quantidadeNos(arvore->raiz, 0);
    float faturamentoTotal = somaValores(arvore->raiz);

    printf("\n=== Estatisticas ===\n");
    printf("Total de vendas: %d\n", totalVendas);
    printf("Faturamento total: R$ %.2f", faturamentoTotal); //Apenas fiz isso para garantir que o numero seja no formato pedido de 2 casas decimais
}

    else
    {
        printf("Nao ha venda registrada no momento");
    }

}


Arvore* removerVenda(Arvore*arvore)
{
    int id;

    if ((VaziaArvore(arvore))==1)
    {
    printf("\n Remover Venda\n");
    printf("Digite o ID da venda a ser removida: ");
    scanf("%d", &id);


    if (BuscarArvore(arvore->raiz, id))
    {
        printf("\nVenda removida!\n");
        arvore->raiz = RemoveGalho(arvore->raiz, id);
        return arvore;

    }
    else
    {
        printf("Venda com ID %d nao encontrada!\n", id);
        return arvore;
    }
    }

else
{
        printf("\nNenhuma venda cadastrada para remover.\n");
        return arvore;
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
                break;
            default:
                printf("\nOpcao invalida!\n");
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
