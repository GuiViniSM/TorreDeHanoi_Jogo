/**
 * @file listaOrdenada.h
 * 
 * @brief Definição das estruturas e escopo de funções utilizadas na implementação da lista ordenada. 
 */

#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H

/**
 * @brief Estrutura do nó da lista ordenada.
 */
typedef struct node {
    int movimentos; /**< Número de movimentos do jogador no placar. */
    int numDiscos; /**< Número de discos utilizado pelo jogador. */
    char nome[50]; /**< Nome do jogador. */
    struct node *proximo; /**< Ponteiro para o próximo nó. */
    struct node *anterior; /**< Ponteiro para o nó anterior. */
} Node;

/**
 * @brief Estrutura da lista ordenada.
 */
typedef struct SortedList{
    Node *sentinela; /**< Ponteiro para o nó sentinela. */
    unsigned tamanho; /**< Número de elementos na lista ordenada. */
} SortedList;

/**
 * @brief Estrutura do iterador para lista ordenada.
 */
typedef struct Iterador{
    Node *elemento; /**< Ponteiro para elemento da lista ordenada. */
    SortedList *lista; /**< Ponteiro para a lista ordenada que o iterador percorre. */
} Iterador;

/**
 * @brief Inicializa a lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada a ser inicializada.
 */
void initialize(SortedList *lista);

/**
 * @brief Destroi a lista ordenada, liberando a memória alocada.
 * 
 * @param lista Ponteiro para a lista ordenada a ser destruída.
 */
void destroy(SortedList *lista);


/**
 * @brief Insere um elemento na lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada.
 * @param movimentos Número de movimentos da vitória.
 * @param numDiscos Número de discos da vitória.
 * @param nome Nome do vencedor.
 */
void insertSortedList(SortedList *lista, int movimentos, int numDiscos, char nome[]);

/**
 * @brief Remove um elemento da lista ordenada.
 * 
 * @param it Iterador apontando para o elemento a ser removido.
 * 
 * @return Iterador apontando para o próximo elemento na lista ordenada.
 */
Iterador remover(Iterador it);

/**
 * @brief Direciona o iterador para o primeiro elemento da lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada.
 * 
 * @return Iterador apontando para o primeiro elemento da lista ordenada.
 */
Iterador first(SortedList *lista);

/**
 * @brief Verifica se o iterador chegou ao fim da lista ordenada.
 * 
 * @param it Iterador a ser verificado.
 * 
 * @return 1 se o iterador está no fim da lista ordenada, caso contrário, retorna 0.
 */
int end(Iterador it);

/**
 * @brief Move o iterador para o próximo elemento da lista ordenada.
 * 
 * @param it Ponteiro para o iterador a ser movido.
 */
void next(Iterador *it);

/**
 * @brief Retorna o elemento apontado pelo iterador.
 * 
 * @param it Iterador apontando para o elemento desejado.
 * 
 * @return Elemento apontado pelo iterador.
 */
Node elemento(Iterador it);

#endif
