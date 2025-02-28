/**
 * @file pilha.h
 * 
 * @brief Definição das estruturas e escopo das funções utilizadas na manipulação de pilhas.
 */

#ifndef PILHA_H
#define PILHA_H

/**
 * @brief Estrutura para representar uma pilha.
 */
typedef struct Stack {
    int size; /**< Tamanho atual da pilha. */
    int capacity; /**< Capacidade máxima da pilha. */
    int *data; /**< Ponteiro para os dados da pilha. */
    int *rear; /**< Ponteiro para o topo da pilha. */
} Stack;

/**
 * @brief Inicializa a pilha.
 * 
 * @param stack Ponteiro para a pilha a ser criada.
 */
void createStack(Stack *stack);

/**
 * @brief Destroi a pilha, liiberando a memória alocada para a pilha.
 * 
 * @param stack Ponteiro para a pilha a ser destruida.
 */
void freeStack(Stack *stack);

/**
 * @brief Retorna o tamanho da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * 
 * @return Tamanho da pilha.
 */
int sizeStack(Stack *stack);

/**
 * @brief Retorna o valor do elemento no topo da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * 
 * @return Valor do elemento no topo da pilha.
 */
int dataStack(Stack *stack);

/**
 * @brief Insere um elemento na pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * @param data Valor do elemento a ser inserido.
 */
void insertStack(Stack *stack, int data);

/**
 * @brief Remove um elemento da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 */
void removeStack(Stack *stack);

/**
 * @brief Redimensiona a capacidade da pilha.
 * 
 * @param stack Ponteiro para a pilha.
 * @param newSize Novo capacidade da pilha.
 */
void reSizeStack(Stack *stack, int newSize);

#endif