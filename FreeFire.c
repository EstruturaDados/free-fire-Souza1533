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


// Função: InserirNaLista
// Descrição: Adiciona um novo item à mochila (lista sequencial) se houver espaço.
// Parâmetro:
//  - lista: ponteiro para a estrutura Bolsa que representa a mochila
void InserirNaLista(Bolsa *lista){
    // Verifica se a mochila já está cheia
    if (lista->qnt_items == MAX_ITEMS){
        printf("\n- Erro: Lista cheia, não é possível inserir -\n");
        return; // Sai da função sem inserir
    }

    // Variáveis temporárias para receber os dados do item
    char nome_item[MAX_STR_LEN];
    char tipo_item[MAX_STR_LEN];
    int quantidade_item;

    // Solicita informações do usuário
    printf("\n---(  Adicionar novo item  )---\n");
    printf("\nNome do item: \n\n-> ");
    scanf("%s", nome_item);

    printf("\nTipo do item: \n\n-> ");
    scanf("%s", tipo_item);
    
    printf("\nQuantidade do item: \n\n-> ");
    scanf("%d", &quantidade_item);

    // Copia os valores para o próximo índice da lista
    // Cada item é armazenado em uma struct Item dentro do vetor
    strcpy(lista->items[lista->qnt_items].nome, nome_item);
    strcpy(lista->items[lista->qnt_items].tipo, tipo_item);
    lista->items[lista->qnt_items].quantidade = quantidade_item;
  
    // Incrementa a quantidade de itens na mochila
    lista->qnt_items++;

    // Mensagem de confirmação
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
    printf("\nPrecione ENTER para continuar: "); 

    while(getchar() != '\n'); //limpa buffer
    getchar();// Espera o usuário apertar Enter
}

// Remove um item pelo nome
void RemoverItemDaLista(Bolsa *lista, const char *nome_item) {
    int pos = -1;

    // Busca o item pelo nome
    for (int i = 0; i < lista->qnt_items; i++) {
        if (strcmp(lista->items[i].nome, nome_item) == 0) {
            pos = i;

            // Desloca os itens seguintes para "tampar o buraco"
            for (int j = pos; j < lista->qnt_items - 1; j++) {
                lista->items[j] = lista->items[j + 1]; // copia struct inteira (nome + tipo)
            }

            lista->qnt_items--;
            printf("\n-Item '%s' removido com sucesso!\n", nome_item);
            return;
        }
    }
        printf("\nErro: Item '%s' nao encontrado na lista\n", nome_item);
}


int BuscarItemPorNome(Bolsa *lista, const char *nome_item){ 
    // Percorre todos os itens da mochila
    for (int i = 0; i < lista->qnt_items; i++) {
        // Compara o nome do item atual com o nome buscado
        if (strcmp(lista->items[i].nome, nome_item) == 0) {
            printf("\nItem: %s Encontrado!\n", nome_item);
            return 1; // Retorna 1 (verdadeiro) para a variável que chamou a função
        }
    }

    // Se o loop terminar sem encontrar o item
    printf("\nItem: %s Nao Encontrado!\n", nome_item);
    return 0; // Retorna 0 (falso) para a variável que chamou a função
}


// Função: ExibirMenu
// Descrição: Exibe o menu principal da mochila de sobrevivência e
// permite ao usuário escolher operações como inserir, listar,
// buscar ou remover itens. Repete até o usuário escolher sair.
void ExibirMenu(Bolsa *lista) {
    int escolha;

    do {
        // Cabeçalho do menu
        printf("\n===============================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  \n");
        printf("===============================================\n");

        // Mostra quantidade de itens na mochila
        if(MAX_ITEMS != lista->qnt_items){
            printf("\n---------(   Items na Mochila: %d/10  )---------\n\n", lista->qnt_items);
        } else {
            printf("\n------(  Items na Mochila: %d/10 CHEIA! )------\n\n", lista->qnt_items);
        }

        // Opções do menu
        printf("1. Novo Item (Loot)\n");
        printf("2. Listar Items\n");
        printf("3. Buscar Item por nome\n");
        printf("4. Remover Items\n");
        printf("5. Sair.\n");
        printf("-----------------------------------------------\n-> ");
        scanf("%d", &escolha);

        // Processa a escolha do usuário
        switch (escolha) {

            case 1: // Inserir novo item
                InserirNaLista(lista);
                break;

            case 2: // Listar todos os itens
                ListarItems(lista);
                break;

            case 3: { // Buscar item por nome
                // {} cria um escopo local para variáveis do case
                char nome[MAX_STR_LEN];
                printf("\n---(  Buscar item na mochila  )---\n");
                printf("\nDigite o nome do item que deseja buscar:\n-> ");
                scanf("%s", nome);
                while (getchar() != '\n'); // limpa ENTER do teclado
                
                // Chama a função de busca e recebe 1 se encontrado ou 0 se não
                int encontrado = BuscarItemPorNome(lista, nome);

                // Decide ação com base no retorno da função
                if(encontrado) {
                    printf("Você pode agora usar ou remover o item.\n");
                } else {
                    printf("Tente adicionar o item primeiro.\n");
                }
                break;
            }

            case 4: { // Remover item
                // {} cria escopo local para a variável nome
                char nome[MAX_STR_LEN];
                printf("\nDigite o nome do item para remover:\n-> ");
                scanf("%s", nome);
                while (getchar() != '\n'); // limpa ENTER do teclado
                RemoverItemDaLista(lista, nome);
                break;
            }

            case 5: // Sair do programa
                printf("\nSaindo...\n");
                break;

            default: // Opção inválida
                printf("\nOpcao invalida!\n");
        }

    } while (escolha != 5); // Repete o menu até o usuário escolher sair
}


int main(){
    Bolsa lista;
    IniciarLista(&lista);
    ExibirMenu(&lista);
}