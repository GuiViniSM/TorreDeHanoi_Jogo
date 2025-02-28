/**
 * @file main.c
 * 
 * @brief Implementação do jogo Torre de Hanoi.
 * 
 *  O programa Torre de Hanoi simula o famoso jogo quebra-cabeça 
 *  Torre de Hanoi, o objetivo é mover todos os discos que estão 
 *  inicialmente na torre 1 para a torre 3, movendo apenas um disco
 *  por vez e sem colocar um disco maior sobre um disco menor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "listaOrdenada.h"

/**
 * @brief Estrutura para armazenar as torres de Hanoi.
 */
typedef struct hanoi {
    Stack torre[3]; /**< Array de pilhas que representam as torres. */
} Hanoi;

/**
 * @brief Representação visual dos discos.
 */
const char * const discos[] = {
    "0        |       \0",
    "1        -       \0",
    "2       ---      \0",
    "3      -----     \0",
    "4     -------    \0",
    "5    ---------   \0",
    "6   -----------  \0",
    "7  ------------- \0",
    "8 ---------------\0"
};

/**
 * @brief Limpa a tela do terminal.
 */
void clear();

/**
 * @brief Espera o usuário apertar enter.
 */
void wait();

/**
 * @brief Imprime o menu principal do jogo.
 */
void printMenu();

/**
 * @brief Lê a opção do menu escolhida pelo usuário.
 * 
 * @return char A opção escolhida.
 */
char lerOpcao();

/**
 * @brief Verifica se a opção escolhida é válida.
 * 
 * @param opcao A opção escolhida pelo usuário.
 * 
 * @return int 1 se a opção for inválida, 0 caso contrário.
 */
int opcaoInvalida(char opcao);

/**
 * @brief Inicia o jogo da Torre de Hanoi.
 * 
 * @param placar Lista ordenada para armazenar o placar.
 */
void jogo(SortedList *placar);


/**
 * @brief Inicializa a estrutura da Torre de Hanoi.
 * 
 * @param torre Ponteiro para a estrutura Hanoi.
 * @param qtd Quantidade de discos.
 */
void iniciarHanoi(Hanoi *torre, int qtd);

/**
 * @brief Destrói a estrutura da Torre de Hanoi.
 * 
 * @param torre Ponteiro para a estrutura Hanoi.
 */
void destruirHanoi(Hanoi *torre);

/**
 * @brief Verifica se as torres de origem e destino são válidas.
 * 
 * @param torre Estrutura Hanoi.
 * @param origem Índice da torre de origem.
 * @param dest Índice da torre de destino.
 * 
 * @return int 1 se as torres são válidas, 0 caso contrário.
 */
int torreValida(Hanoi torre, int origem, int dest);

/**
 * @brief Verifica se a torre está vazia.
 * 
 * @param torre Estrutura Hanoi.
 * @param num Índice da torre.
 * 
 * @return int 1 se a torre está vazia, 0 caso contrário.
 */
int torreVazia(Hanoi torre, int num);

/**
 * @brief Verifica se o movimento é válido.
 * 
 * @param torre Estrutura Hanoi.
 * @param origem Índice da torre de origem.
 * @param destino Índice da torre de destino.
 * 
 * @return int 1 se o movimento é válido, 0 caso contrário.
 */
int movimentoValido(Hanoi torre, int origem, int destino);

/**
 * @brief Move um disco de uma torre para outra.
 * 
 * @param torre Ponteiro para a estrutura Hanoi.
 * @param origem Índice da torre de origem.
 * @param dest Índice da torre de destino.
 */
void moverDisco(Hanoi *torre, int origem, int dest);

/**
 * @brief Verifica se o jogador ganhou o jogo.
 * 
 * @param torre Estrutura Hanoi.
 * @param qtd Quantidade de discos.
 * 
 * @return int 1 se o jogador ganhou, 0 caso contrário.
 */
int ganhouJogo(Hanoi torre, int qtd);

/**
 * @brief Imprime as torres de Hanoi.
 * 
 * @param torre Ponteiro para a estrutura Hanoi.
 * @param qtd Quantidade de discos.
 */
void printHanoi(Hanoi *torre, int qtd);

/**
 * @brief Obtém os valores das torres de Hanoi.
 * 
 * @param torre Ponteiro para a estrutura Hanoi.
 * @param idx Índice da torre.
 * @param aux Array auxiliar para armazenar os valores.
 */
void valorTorre(Hanoi *torre, int idx, int aux[3][9]);

/**
 * @brief Função principal do programa.
 * 
 * @return Int retorno padrão
 */
int main() {
    SortedList *placar = (SortedList*)malloc(sizeof(SortedList)); /**< Lista ordenada que armazena o placar. */
    initialize(placar);

    while (1) {
        printMenu();
        
        char opcao = lerOpcao(); /**< Entrada do usuário sobre o menu. */

        clear();
        
        if (opcao == '1') jogo(placar);
        else if (opcao == '2') {
            Iterador it = first(placar); /**< Iterador para impressão do placar. */

            printf("\nPlacar:\n");

            if (end(it)) printf("-- nenhum jogo salvo --\n\n");

            while (!end(it)) {
                Node p = elemento(it); /**< Node auxiliar para acessar valores do placar. */

                printf("%s - %d movimentos - %d discos\n", p.nome, p.movimentos, p.numDiscos);

                next(&it);
            }

            printf("\n");

            wait();
        }   
        else if (opcao == '3') {
            printf("\tSaindo do programa.\n");

            break;
        }
    }

    destroy(placar);
    free(placar);
    
    return 0;
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void wait() {
    printf("Aperte [enter] para voltar...\n");
    while (getchar() != '\n');
}

void printMenu() {
    clear();
    printf("Torre de Hanoi\n");
    printf("\nOpcoes:\n");
    printf("\t1 - Iniciar Jogo\n");
    printf("\t2 - Acessar placar\n");
    printf("\t3 - Sair \n");
    printf("\nEscolha uma opcao: ");
}

char lerOpcao() {
    char opcao; /**< Opção do menu a ser escolhida pelo usuário */

    do {
        opcao = getchar();
        while (getchar() != '\n');
    } while (opcaoInvalida(opcao));

    return opcao;
}

int opcaoInvalida(char opcao) {
    if (opcao == '1' || opcao == '2' || opcao == '3') return 0;

    printf("Entrada invalida. Por favor, insira uma das opcoes.\n");
    return 1;
}

void jogo(SortedList *placar) {
    Hanoi torre; /**< Torres do jogo. */

    char nome[51]; /**< Nome do jogador. */

    int qtdDiscos; /**< Número de discos do jogo. */
    int origem; /**< Torre do qual o disco sai. */
    int destino; /**< Torre a qual o disco chega. */
    int movimentos = 0; /**< Número de movimentos efetuados pelo jogador */

    printf("Digite seu nick (sem espaços): ");
    scanf("%50s", nome);
    while (getchar() != '\n');

    clear();

    printf("Digite a quantidade de discos (1 a 8): ");
    do {
        scanf("%d", &qtdDiscos);
        while (getchar() != '\n');

        if (qtdDiscos < 1 || qtdDiscos > 8) {
            clear();
            printf("Quantidade invalida! Lembre-se que deve estar entre 1 e 8.\n");
            printf("Digite a quantidade de discos (1 a 8): ");
        }
    } while (qtdDiscos < 1 || qtdDiscos > 8);

    clear();

    iniciarHanoi(&torre, qtdDiscos);

    printf("Para realizar um movimento, digite o numero\nda torre de origem e a de destino, exemplo: 1 3\n");
    printf("Quando desejar sair digite: -1 -1\n\n");

    do {
        printHanoi(&torre, qtdDiscos);
        printf("Movimento: ");

        scanf("%d %d", &origem, &destino);
        while (getchar() != '\n');

        clear();

        if (origem == -1 && destino == -1) {
            destruirHanoi(&torre);

            printf("\tSaindo do jogo...\n\n");

            return;
        }

        if (!torreValida(torre, origem, destino)) {
            printf("Torre de origem e/ou destino invalida(s)! Por favor escolha novamente.\n\n");

            continue;
        }

        if (torreVazia(torre, origem)) {
            printf("Torre de origem vazia! Por favor escolha novamente.\n\n");

            continue;
        }

        if (origem == destino) {
            printf("Torre de origem e destino iguais! Por favor escolha novamente.\n\n");

            continue;
        }

        if (movimentoValido(torre, origem, destino)) {
            moverDisco(&torre, origem, destino);

            movimentos++;
        }
        else {
            printf("Movimento invalido, disco da origem maior que disco do destino!\nPor favor escolha novamente.\n\n");
        }

        if (ganhouJogo(torre, qtdDiscos)) {
            printf("Parabens! Voce ganhou o jogo com %d movimentos!\n\n\n", movimentos);

            insertSortedList(placar, movimentos, qtdDiscos, nome);

            destruirHanoi(&torre);

            wait();

            break;
        }
    } while (1);
}

void iniciarHanoi(Hanoi *torre, int qtd) {
    for (int i = 0; i < 3; i++) createStack(&torre->torre[i]);

    for (int i = qtd; i > 0; i--) insertStack(&torre->torre[0], i);
}

void destruirHanoi(Hanoi *torre) {
    for (int i = 0; i < 3; i++) freeStack(&torre->torre[i]);
}

int torreValida(Hanoi torre, int origem, int dest) {
    if ((origem < 1 || origem > 3) || (dest < 1 || dest > 3)) return 0;

    return 1;
}

int torreVazia(Hanoi torre, int num) {
    return !sizeStack(&torre.torre[num - 1]);
}

int movimentoValido(Hanoi torre, int origem, int destino) {
    if (!sizeStack(&torre.torre[destino - 1])) return 1;

    return dataStack(&torre.torre[origem - 1]) < dataStack(&torre.torre[destino - 1]);
}

void moverDisco(Hanoi *torre, int origem, int dest) {
    int aux = dataStack(&torre->torre[origem - 1]); /**< Variavel para auxiliar a transferência de disco. */

    removeStack(&torre->torre[origem - 1]);

    insertStack(&torre->torre[dest - 1], aux);
}

int ganhouJogo(Hanoi torre, int qtd) {
    if (sizeStack(&torre.torre[2]) == qtd) return 1;

    return 0;
}

void printHanoi(Hanoi *torre, int qtd) {
    int aux[3][9] = {0}; /**< Matrix auxiliar que armazena o valor das stacks para a impressão. */

    for (int i = 0; i < 3; i++) valorTorre(torre, i, aux);

    for (int i = qtd - 1; i >= 0; i--) {
        printf("%s %s %s\n", discos[aux[0][i]], discos[aux[1][i]], discos[aux[2][i]]);
    }
    printf("        (1)               (2)               (3)      ");
    printf("\n\n");
}

void valorTorre(Hanoi *torre, int idx, int aux[3][9]) {
    if (!sizeStack(&torre->torre[idx])) return;

    aux[idx][sizeStack(&torre->torre[idx]) - 1] = dataStack(&torre->torre[idx]);

    removeStack(&torre->torre[idx]);

    valorTorre(torre, idx, aux);

    insertStack(&torre->torre[idx], aux[idx][sizeStack(&torre->torre[idx])]);
}