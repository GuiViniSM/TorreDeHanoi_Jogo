/**
 * @file pilha.c
 * 
 * @brief Implementeção das funções utilizadas pela lista ordenada. 
 */

#include <stdlib.h>
#include "pilha.h"

/**
 * @brief Inicializa a pilha.
 * 
 * @param stack Ponteiro para a pilha a ser criada.
 */
void createStack(Stack *stack) {
    stack->size = 0;
    stack->capacity = 1;

    stack->data = (int*)malloc(sizeof(int));

    stack->rear = stack->data;
}

/**
 * @brief Destroi a pilha, liiberando a memória alocada para a pilha.
 * 
 * @param stack Ponteiro para a pilha a ser destruida.
 */
void freeStack(Stack *stack) {
    free(stack->data);
    
    stack->data = stack->rear = NULL;
    stack->size = stack->capacity = 0;
}

/**
 * @brief Retorna o tamanho da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * 
 * @return Tamanho da pilha.
 */
int sizeStack(Stack *stack) {
    return stack->size;
}

/**
 * @brief Retorna o valor do elemento no topo da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * 
 * @return Valor do elemento no topo da pilha.
 */
int dataStack(Stack *stack) {
    return *stack->rear;
}

/**
 * @brief Insere um elemento na pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * @param data Valor do elemento a ser inserido.
 */
void insertStack(Stack *stack, int data) {
    if (stack->size == stack->capacity) reSizeStack(stack, stack->capacity * 2);

    if (stack->size > 0) stack->rear++;

    *stack->rear = data;

    stack->size++;
}

/**
 * @brief Remove um elemento da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 */
void removeStack(Stack *stack) {
    if (stack->size == 0) return;

    if (stack->size < stack->capacity / 4) reSizeStack(stack, (stack->capacity / 2) + 1);

    if (stack->size > 1) stack->rear--;

    stack->size--;
}

/**
 * @brief Redimensiona a capacidade da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * @param newSize Novo capacidade da pilha.
 */
void reSizeStack(Stack *stack, int newSize) {
    int *temp = (int*)malloc(newSize * sizeof(int)); /**< Novo endereço da pilha, após mudança de tamanho. */
    int *temp1 = stack->data; /**< Variável temporária que vai percorrer a antiga pilha para tranferir os valores armazenados. */
    int *temp2 = temp; /**< Variável temporária que vai percorrer a nova pilha, inserindo os valores da antiga pilha. */

    for (int i = 0; i < stack->size; i++) {
        *temp2 = *temp1;
        
        temp1++;
        temp2++;
    }

    free(stack->data);
    stack->data = temp;

    stack->rear = stack->data + stack->size - 1;

    stack->capacity = newSize;
}