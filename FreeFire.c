#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

void inserirItem(Item itens[], int *qtd);
void removerItem(Item itens[], int *qtd);
void listarItens(const Item itens[], int qtd);

int main(void) {
    Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;

    printf("===============================================\n");
    printf("     MOCHILA DE SOBREVIVENCIA - INVENTARIO \n");
    printf("===============================================\n");
    printf("Capacidade: ate %d itens\n\n", MAX_ITENS);

    do {
        printf("\n--- MENU ---\n");
        printf("1) Inserir item\n");
        printf("2) Remover item\n");
        printf("3) Listar itens\n");
        printf("0) Sair\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa buffer
            continue;
        }
        while (getchar() != '\n'); // Limpa buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &quantidadeItens);
                listarItens(mochila, quantidadeItens);
                break;
            case 2:
                removerItem(mochila, &quantidadeItens);
                listarItens(mochila, quantidadeItens);
                break;
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
            case 0:
                printf("Encerrando... Bom jogo!\n");
                break;
            default:
                printf("Opcao inexistente. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

void inserirItem(Item itens[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia! Remova algo antes de inserir novo item.\n");
        return;
    }

    printf("Nome do item: ");
    scanf("%29s", itens[*qtd].nome);

    printf("Tipo (ex.: arma, municao, cura): ");
    scanf("%19s", itens[*qtd].tipo);

    printf("Quantidade: ");
    if (scanf("%d", &itens[*qtd].quantidade) != 1 || itens[*qtd].quantidade < 0) {
        printf("Quantidade invalida. Operacao cancelada.\n");
        while (getchar() != '\n'); // Limpa buffer
        return;
    }
    while (getchar() != '\n'); // Limpa buffer

    (*qtd)++;
    printf("Item \"%s\" inserido com sucesso.\n", itens[*qtd - 1].nome);
}

void removerItem(Item itens[], int *qtd) {
    if (*qtd == 0) {
        printf("A mochila esta vazia. Nada para remover.\n");
        return;
    }

    char nomeAlvo[TAM_NOME];
    printf("Digite o nome do item a remover: ");
    scanf("%29s", nomeAlvo);
    while (getchar() != '\n'); // Limpa buffer

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(itens[i].nome, nomeAlvo) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                itens[j] = itens[j + 1];
            }
            (*qtd)--;
            encontrado = 1;
            printf("Item \"%s\" removido com sucesso.\n", nomeAlvo);
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" nao encontrado.\n", nomeAlvo);
    }
}

void listarItens(const Item itens[], int qtd) {
    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", qtd, MAX_ITENS);
    if (qtd == 0) {
        printf("(vazio)\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%2d) Nome: %-28s | Tipo: %-12s | Qtde: %d\n",
               i + 1, itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
}
