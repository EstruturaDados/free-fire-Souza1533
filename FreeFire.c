//   Projeto: Mochila de Sobrevivência - Código da Ilha

//   Este projeto é uma aplicação em C que simula uma mochila de sobrevivência em um jogo.  
//   O usuário pode *adicionar, listar e remover itens* da mochila, cada um com *nome, tipo e quantidade*.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS  10    // Quantidade máxima de itens na bolsa
#define MAX_STR_LEN 16   //Cada Item pode ter apenas 15 letras

// Estrutura que representa um Item
typedef struct {
    char nome[MAX_STR_LEN];   // Nome do item
    char tipo[MAX_STR_LEN];   // Tipo do item (ex: cura, munição, arma)
    int quantidade;           // Quantidade do item
} Item;

// Estrutura que representa a Bolsa (lista estática de itens)
typedef struct {
    Item items[MAX_ITEMS];  // Vetor de itens
    int qnt_items;          // Quantidade atual de itens
} Bolsa;


// Inicializa a lista, começando vazia
void IniciarLista(Bolsa *lista){
    lista->qnt_items = 0;
}


// Insere um novo item na lista
void InserirNaLista (Bolsa *lista){
    if (lista->qnt_items == MAX_ITEMS){
        printf("\n- Erro: Lista cheia nao e possivel inserir -\n");
        return;
    }

    char nome_item[MAX_STR_LEN];
    char tipo_item[MAX_STR_LEN];
    int quantidade_item;

    printf("\n---(  Adicionar novo item  )---\n");
    printf("\nNome do item: \n\n-> ");
    scanf("%s", nome_item);

    printf("\nTipo do item: \n\n-> ");
    scanf("%s", tipo_item);
    
    printf("\nQuantidade do item: \n\n-> ");
    scanf("%d", &quantidade_item);

    // Copia os valores para a struct
    strcpy(lista->items[lista->qnt_items].nome, nome_item);
    strcpy(lista->items[lista->qnt_items].tipo, tipo_item);
    lista->items[lista->qnt_items].quantidade = quantidade_item;
  

    lista->qnt_items++;
    printf("Item '%s' (%s) x%d inserido com sucesso!\n", nome_item, tipo_item, quantidade_item);
}


// Lista todos os itens da bolsa
void ListarItems(Bolsa *lista){
    //printf("\nItem 1- %s\n\n", lista->items[0]);
    printf("\n--------(   Itens Disponiveis  %d/10  )--------\n\n", lista->qnt_items);
    printf("----------------------------------------------\n");
     printf("NOME            | TIPO           | QUANTIDADE\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < lista->qnt_items; i++) {
        printf("%-15s | %-14s | %d\n",
               lista->items[i].nome,
               lista->items[i].tipo,
               lista->items[i].quantidade);
    }

    printf("----------------------------------------------\n");
}

// Remove um item pelo nome
void RemoverItemDaLista(Bolsa *lista, const char *nome_item) {
    int pos = -1;

    // Busca o item pelo nome
    for (int i = 0; i < lista->qnt_items; i++) {
        if (strcmp(lista->items[i].nome, nome_item) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: Item '%s' nao encontrado na lista\n", nome_item);
        return;
    }

    // Desloca os itens seguintes para "tampar o buraco"
    for (int j = pos; j < lista->qnt_items - 1; j++) {
        lista->items[j] = lista->items[j + 1]; // copia struct inteira (nome + tipo)
    }

    lista->qnt_items--;
    printf("\n-Item '%s' removido com sucesso!\n", nome_item);
}




//Exibi Menu Principal
void ExibirMenu(Bolsa *lista) {
    int escolha;
    printf("\n===============================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  \n");
    printf("===============================================\n");

    do {
        if(MAX_ITEMS != lista->qnt_items){
            printf("\n----(  Items na Mochila: %d/10 )----\n\n", lista->qnt_items);
        } else {
            printf("\n----(  Items na Mochila: %d/10 CHEIA!)----\n\n", lista->qnt_items);
        }
        printf("1. Novo Item (Loot)\n");
        printf("2. Listar Items\n");
        printf("3. Remover Items\n");
        printf("4. Sair.\n");
        printf("---------------------------\n-> ");
        scanf("%d", &escolha);
        

        switch (escolha) {
            case 1:
                InserirNaLista(lista);
                break;
            case 2:
                ListarItems(lista);
                break;
            case 3: {
                char nome[MAX_STR_LEN];
                printf("\nDigite o nome do item para remover:\n-> ");
                scanf("%s", nome);
                RemoverItemDaLista(lista, nome);
                break;
            }
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while (escolha != 4);
}


int main(){
    Bolsa lista;
    IniciarLista(&lista);
    ExibirMenu(&lista);
}
    