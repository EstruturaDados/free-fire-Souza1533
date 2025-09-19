//   Projeto: Mochila de Sobrevivência - Código da Ilha
//   ----------------------------------------------------
//   Este projeto é uma aplicação em C que simula uma mochila de sobrevivência em um jogo.  
//   O usuário pode *adicionar, listar, remover e buscar itens* da mochila, cada um com
//   *nome, tipo, quantidade e prioridade*.
//   Também é possível organizar a mochila por Nome, Tipo ou Prioridade.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS  10    // Capacidade máxima da mochila (limite de itens)
#define MAX_STR_LEN 16   // Máximo de caracteres por string (15 + '\0')

// Status de organização da mochila
// 0 = não ordenada
// 1 = ordenada por nome
// 2 = ordenada por tipo/prioridade
int organizado = 0;

// Estrutura que representa um Item
typedef struct {
    char nome[MAX_STR_LEN];   // Nome do item
    char tipo[MAX_STR_LEN];   // Tipo do item (ex: cura, munição, arma)
    int quantidade;           // Quantidade do item
    int prioridade;           // Prioridade do item (1 = baixa, 2 = média, 3 = alta)
} Item;

// Estrutura que representa a Bolsa (lista estática de itens)
typedef struct {
    Item items[MAX_ITEMS];    // Vetor de itens
    int qnt_items;            // Quantidade atual de itens
} Bolsa;


// Inicializa a lista, começando vazia
void IniciarLista(Bolsa *lista){
    lista->qnt_items = 0;
}

// Pausa o programa aguardando ENTER e limpa o buffer
void Press_Enter(){
    int c;
    printf("\nPrecione ENTER para continuar: "); 
    while ((c = getchar()) != '\n' && c != EOF); // Consome caracteres até limpar buffer
}


// --------------------- FUNÇÕES DE ORDENAÇÃO ---------------------

// Ordenação por Nome (Insertion Sort)
void Ordenar_Nome(Bolsa *lista) {
    int i, j;
    Item chave;

    for (i = 1; i < lista->qnt_items; i++) {
        chave = lista->items[i];
        j = i - 1;

        // Comparação alfabética de nomes
        while (j >= 0 && strcmp(lista->items[j].nome, chave.nome) > 0) {
            lista->items[j + 1] = lista->items[j];
            j--;
        }
        lista->items[j + 1] = chave;
    }
    printf("\nMochila Organizada por Ordem Alfabetica\n");
    organizado = 1;
    Press_Enter(); 
}

// Ordenação por Tipo (Insertion Sort)
void Ordenar_Tipo(Bolsa *lista){
    int i, j;
    Item chave;

    for (i = 1; i < lista->qnt_items; i++) {
        chave = lista->items[i];
        j = i - 1;

        // Comparação alfabética de tipos
        while (j >= 0 && strcmp(lista->items[j].tipo, chave.tipo) > 0) {
            lista->items[j + 1] = lista->items[j];
            j--;
        }
        lista->items[j + 1] = chave;
    }
    printf("\nMochila Organizada por Tipo\n");
    organizado = 2;
    Press_Enter();
}

// Ordenação por Prioridade (maior para menor)
void Ordenar_Prioridade(Bolsa *lista){
    int i, j;
    Item chave;

    for (i = 1; i < lista->qnt_items; i++) {
        chave = lista->items[i];
        j = i - 1;

        // Ordena de acordo com prioridade (3 > 2 > 1)
        while (j >= 0 && lista->items[j].prioridade < chave.prioridade){
            lista->items[j + 1] = lista->items[j];
            j--;
        }
        lista->items[j + 1] = chave;
    }
    printf("\nMochila Organizada por Prioridade\n");
    organizado = 2;
    Press_Enter();
}

// --------------------- FUNÇÕES PRINCIPAIS ---------------------

// Adiciona um novo item na mochila
void InserirNaLista(Bolsa *lista){
    if (lista->qnt_items == MAX_ITEMS){
        printf("\n- Erro: Lista cheia, não é possível inserir -\n");
        return;
    }

    char nome_item[MAX_STR_LEN];
    char tipo_item[MAX_STR_LEN];
    int prioridade_item;
    int quantidade_item;

    printf("\n---(  Adicionar novo Componente  )---\n");

    printf("\nNome do Componente: \n\n-> ");
    fgets(nome_item, sizeof(nome_item), stdin);
    nome_item[strcspn(nome_item, "\n")] = '\0';  // Remove ENTER

    printf("\nTipo do Componente: \n\n-> ");
    fgets(tipo_item, sizeof(tipo_item), stdin);
    tipo_item[strcspn(tipo_item, "\n")] = '\0';

    printf("\nQuantidade de Componente: \n\n-> ");
    scanf("%d", &quantidade_item);
    while(getchar() != '\n'); // Limpa buffer

    printf("\nPrioridade do Componente: (1.baixa 2.media 3.alta) \n\n-> ");
    scanf("%d", &prioridade_item);
    while(getchar() != '\n');

    // Validação da prioridade
    if (prioridade_item < 1 || prioridade_item > 3){
        printf("\nDigite um valor valido da proxima vez! Recomece.\n");
        Press_Enter();
        return;
    }
    
    // Copia os valores para a struct
    strcpy(lista->items[lista->qnt_items].nome, nome_item);
    strcpy(lista->items[lista->qnt_items].tipo, tipo_item);
    lista->items[lista->qnt_items].quantidade = quantidade_item;
    lista->items[lista->qnt_items].prioridade = prioridade_item;

    lista->qnt_items++;

    printf("Componente: %s (%s) x%d inserido com sucesso!\n", nome_item, tipo_item, quantidade_item);
    Press_Enter();
}

// Lista todos os itens da mochila
void ListarItems(Bolsa *lista){
    printf("\n---------------(   Itens Disponiveis  %d/10   )---------------\n\n", lista->qnt_items);
    printf("-------------------------------------------------------------\n");
    printf("NOME           | TIPO          | QUANTIDADE      | PRIORIDADE\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < lista->qnt_items; i++) {
        printf("%-14s | %-13s | %-15d | %d\n",
               lista->items[i].nome,
               lista->items[i].tipo,
               lista->items[i].quantidade,
               lista->items[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
    Press_Enter();
}

// Remove item pelo nome
void RemoverItemDaLista(Bolsa *lista, const char *nome_item) {
    int pos = -1;

    for (int i = 0; i < lista->qnt_items; i++) {
        if (strcmp(lista->items[i].nome, nome_item) == 0) {
            pos = i;

            // Desloca os itens seguintes para fechar o espaço
            for (int j = pos; j < lista->qnt_items - 1; j++) {
                lista->items[j] = lista->items[j + 1];
            }

            lista->qnt_items--;
            printf("\n-Componente '%s' removido com sucesso!\n", nome_item);
            return;
        }
    }
    printf("\nErro: Componente '%s' nao encontrado na lista\n", nome_item);
    Press_Enter();
}

// Busca binária (somente se ordenado por nome)
int BuscaBinaria(Bolsa *lista, const char *nome_item) {
    int inicio = 0;
    int fim = lista->qnt_items - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(lista->items[meio].nome, nome_item);

        if (cmp == 0) {
            return meio; // Item encontrado
        } else if (cmp > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1; // Item não encontrado
}

// Permite escolher como organizar a mochila
void OrganizarMochila(Bolsa *lista){
    int escolha;
    printf("--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem (maior pro menor)\n");
    printf("0. Cancelar\n-> ");
    scanf("%d", &escolha);

    if(escolha > 3 || escolha < 0){
        printf("Opcao Invalida!\n");
        Press_Enter();
        return;
    }

    switch(escolha){
        case 1: Ordenar_Nome(lista); break;
        case 2: Ordenar_Tipo(lista); break;
        case 3: Ordenar_Prioridade(lista); break;
    }
}

// --------------------- MENU PRINCIPAL ---------------------

void ExibirMenu(Bolsa *lista) {
    int escolha;

    do {
        printf("\n======================================================\n");
        printf("      MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  \n");
        printf("======================================================\n");

        if(MAX_ITEMS != lista->qnt_items){
            printf("\n-------------(  Items na Mochila: %d/10  )-------------\n", lista->qnt_items);
        } else {
            printf("\n----------(  Items na Mochila: %d/10 CHEIA! )---------\n", lista->qnt_items);
        }

        // Status de ordenação
        if(organizado == 0) printf("-----------(Status Ordenacao: NAO Ordenado)-----------\n\n");
        else if(organizado == 1) printf("---------(Status Ordenacao: Ordenado por Nome)--------\n\n");
        else if(organizado == 2) printf("---(Status Ordenacao: Ordenado por Tipo/Prioridade)---\n\n");

        // Menu de opções
        printf("1. Adicionar Componente\n");
        printf("2. Listar Componentes (Inventario)\n");
        printf("3. Busca Binaria por Componente-Chave (por nome)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Descartar Componentes\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("------------------------------------------------------\n-> ");
        scanf("%d", &escolha);
        while (getchar() != '\n');

        switch (escolha) {
            case 1: InserirNaLista(lista); break; // Adicionar
            case 2: ListarItems(lista); break;    // Listar
            case 3: { // Busca Binária
                if(organizado == 1){
                    char nome[MAX_STR_LEN];
                    printf("\n-- Busca Binaria por Componente-Chave --\n");
                    printf("Nome do componente a buscar: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    int pos = BuscaBinaria(lista, nome);
                    if (pos != -1) {
                        printf("\n-- Componente-Chave Encontrado! --\n");
                        printf("Nome: %s, Tipo(%s), Qtd: %d, Prio: %d\n",
                            lista->items[pos].nome,
                            lista->items[pos].tipo,
                            lista->items[pos].quantidade,
                            lista->items[pos].prioridade);
                    } else {
                        printf("Componente '%s' nao encontrado.\n", nome);
                    }
                } else {
                    printf("ALERTA: A busca binaria requer que a mochila esteja ordenada por nome.\nUse a opcao 4 para organizar a mochila primeiro.\n");
                }
                Press_Enter();
                break;
            }
            case 4: OrganizarMochila(lista); break; // Organizar
            case 5: { // Remover
                char nome[MAX_STR_LEN];
                printf("\nDigite o nome do componente para remover:\n-> ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                RemoverItemDaLista(lista, nome);
                break;
            }
            case 0: printf("\nSaindo...\n\n"); break; // Sair
            default: printf("\nOpcao invalida!\n"); break;
        }
    } while (escolha != 0);
}

// --------------------- PROGRAMA PRINCIPAL ---------------------

int main(){
    Bolsa lista;              // Instância da mochila
    IniciarLista(&lista);     // Inicializa mochila vazia
    ExibirMenu(&lista);       // Inicia o loop principal
}