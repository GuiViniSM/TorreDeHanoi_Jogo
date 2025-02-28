/**
 * @file listaOrdenada.c
 * 
 * @brief Implementeção das funções utilizadas pela lista ordenada. 
 */

#include <stdlib.h>
#include <string.h>
#include "listaOrdenada.h"

/**
 * @brief Inicializa a lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada a ser inicializada.
 */
void initialize(SortedList *lista) {
    lista->tamanho = 0;
    lista->sentinela = (Node*)malloc(sizeof(Node));
    lista->sentinela->proximo = lista->sentinela->anterior = lista->sentinela;
}

/**
 * @brief Destroi a lista ordenada, liberando a memória alocada.
 * 
 * @param lista Ponteiro para a lista ordenada a ser destruída.
 */
void destroy(SortedList *lista) {
    Iterador it = first(lista); /**< Iterador auxiliar. */

    while (!end(it)) it = remover(it);

    free(lista->sentinela);
}

/**
 * @brief Insere um elemento na lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada.
 * @param movimentos Número de movimentos da vitória.
 * @param numDiscos Número de discos da vitória.
 * @param nome Nome do vencedor.
 */
void insertSortedList(SortedList *lista, int movimentos, int numDiscos, char nome[]) {
    Iterador it = first(lista); /**< Iterador auxiliar. */

    while (!end(it) && ((it.elemento->numDiscos > numDiscos) || (it.elemento->numDiscos == numDiscos && it.elemento->movimentos <= movimentos)))
        next(&it);

    Node *novo = (Node*)malloc(sizeof(Node)); /**< Novo nó a ser inserido na lista ordenada. */

    novo->movimentos = movimentos;
    novo->numDiscos = numDiscos;  
    strcpy(novo->nome, nome);
    novo->proximo = it.elemento;
    novo->anterior = it.elemento->anterior;
    novo->proximo->anterior = novo->anterior->proximo = novo;

    lista->tamanho++;
}

/**
 * @brief Remove um elemento da lista ordenada.
 * 
 * @param it Iterador apontando para o elemento a ser removido.
 * 
 * @return Iterador apontando para o próximo elemento na lista ordenada.
 */
Iterador remover(Iterador it) {
    if (!end(it)) {
        Node *p = it.elemento; /**< Ponteiro para nó a ser removido. */

        next(&it);

        p->proximo->anterior = p->anterior;
        p->anterior->proximo = p->proximo;

        free(p);

        it.lista->tamanho--;
    }

    return it;
}

/**
 * @brief Direciona o iterador para o primeiro elemento da lista ordenada.
 * 
 * @param lista Ponteiro para a lista ordenada.
 * 
 * @return Iterador apontando para o primeiro elemento da lista ordenada.
 */
Iterador first(SortedList *lista) {
    Iterador it; /**< Iterador auxiliar. */

    it.elemento = lista->sentinela->proximo;
    it.lista = lista;

    return it;
}

/**
 * @brief Verifica se o iterador chegou ao fim da lista ordenada.
 * 
 * @param it Iterador a ser verificado.
 * 
 * @return 1 se o iterador está no fim da lista ordenada, caso contrário, retorna 0.
 */
int end(Iterador it) {
    return it.elemento == it.lista->sentinela;
}

/**
 * @brief Move o iterador para o próximo elemento da lista ordenada.
 * 
 * @param it Ponteiro para o iterador a ser movido.
 */
void next(Iterador *it) {
    if (!end(*it)) it->elemento = it->elemento->proximo;
}

/**
 * @brief Retorna o elemento apontado pelo iterador.
 * 
 * @param it Iterador apontando para o elemento desejado.
 * 
 * @return Nó apontado pelo iterador.
 */
Node elemento(Iterador it) {
    return *it.elemento;
}