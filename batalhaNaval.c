#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AGUA '~'
#define NAVIO 'N'
#define ACERTO 'X'
#define ERRO 'O'

// Funções
void inicializarTabuleiro(char tabuleiro[][10], int tamanho);
void posicionarNavios(char tabuleiro[][10], int tamanho, int quantidade);
void mostrarTabuleiro(char tabuleiro[][10], int tamanho, int mostrarNavios);
int jogar(char tabuleiro[][10], int tamanho);

int main() {
    int nivel, tamanho, quantidadeNavios;
    char tabuleiro[10][10];

    srand(time(NULL));

    printf("=== BATALHA NAVAL ===\n");
    printf("Escolha o nivel de dificuldade:\n");
    printf("1. Facil (5x5, 3 navios)\n");
    printf("2. Medio (7x7, 5 navios)\n");
    printf("3. Dificil (10x10, 8 navios)\n");
    printf("Nivel: ");
    scanf("%d", &nivel);

    switch (nivel) {
        case 1:
            tamanho = 5;
            quantidadeNavios = 3;
            break;
        case 2:
            tamanho = 7;
            quantidadeNavios = 5;
            break;
        case 3:
            tamanho = 10;
            quantidadeNavios = 8;
            break;
        default:
            printf("Nivel invalido! Saindo...\n");
            return 1;
    }

    inicializarTabuleiro(tabuleiro, tamanho);
    posicionarNavios(tabuleiro, tamanho, quantidadeNavios);

    printf("\nIniciando o jogo...\n");
    int tentativasRestantes = tamanho * 2; // Limite de tentativas
    int naviosRestantes = quantidadeNavios;

    while (tentativasRestantes > 0 && naviosRestantes > 0) {
        mostrarTabuleiro(tabuleiro, tamanho, 0);
        printf("Tentativas restantes: %d\n", tentativasRestantes);
        printf("Navios restantes: %d\n", naviosRestantes);

        int resultado = jogar(tabuleiro, tamanho);

        if (resultado == 1) {
            printf("Voce acertou um navio!\n");
            naviosRestantes--;
        } else if (resultado == 0) {
            printf("Agua!\n");
        } else {
            printf("Ja tentou essa posicao.\n");
        }
        tentativasRestantes--;
    }

    if (naviosRestantes == 0) {
        printf("Parabens! Voce venceu!\n");
    } else {
        printf("Fim das tentativas. Voce perdeu!\n");
    }

    printf("\nTabuleiro final:\n");
    mostrarTabuleiro(tabuleiro, tamanho, 1);

    return 0;
}

// Inicializa o tabuleiro com agua
void inicializarTabuleiro(char tabuleiro[][10], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona navios aleatoriamente
void posicionarNavios(char tabuleiro[][10], int tamanho, int quantidade) {
    int naviosColocados = 0;
    while (naviosColocados < quantidade) {
        int linha = rand() % tamanho;
        int coluna = rand() % tamanho;
        if (tabuleiro[linha][coluna] == AGUA) {
            tabuleiro[linha][coluna] = NAVIO;
            naviosColocados++;
        }
    }
}

// Mostra o tabuleiro
void mostrarTabuleiro(char tabuleiro[][10], int tamanho, int mostrarNavios) {
    printf("  ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%d ", i);
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == NAVIO && !mostrarNavios) {
                printf("%c ", AGUA);
            } else {
                printf("%c ", tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
}

// Jogada do usuario
int jogar(char tabuleiro[][10], int tamanho) {
    int linha, coluna;
    printf("Digite a linha: ");
    scanf("%d", &linha);
    printf("Digite a coluna: ");
    scanf("%d", &coluna);

    if (linha < 0 || linha >= tamanho || coluna < 0 || coluna >= tamanho) {
        printf("Posicao invalida!\n");
        return -1;
    }

    if (tabuleiro[linha][coluna] == NAVIO) {
        tabuleiro[linha][coluna] = ACERTO;
        return 1; // Acertou
    } else if (tabuleiro[linha][coluna] == AGUA) {
        tabuleiro[linha][coluna] = ERRO;
        return 0; // Errou
    } else {
        return -1; // Ja tentou
    }
}
