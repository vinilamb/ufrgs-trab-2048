#include <stdio.h>
#include <stdlib.h>

struct square {
    int cor;
    int valor;
};

struct posicao {
    int linha;
    int coluna;
};

#define LADOS 4
#define CASAS (LADOS*LADOS)

// Definição do tabuleiro
typedef struct square Board[LADOS][LADOS];

// Atribui o valor a todas as casas do tabuleiro
void fill_board(Board b, int value);

// Imprime o tabuleiro no console
void imprimir_board(Board b);

// Encontra índices da casa na matriz bidimensional
// Retorno 0 = Peça não está no tabuleiro
int Posicao_Casa(Board b, struct square* casa, struct posicao *pos) {
    for (int i = 0; i < LADOS; i++) {
        for (int j = 0; j < LADOS; j++) {
            if (&b[i][j] == casa) {
                pos->linha = i;
                pos->coluna = j;
                return 1;
            }
        }
    }
    return 0;
}

int posicao_valida(struct posicao pos) {
    return pos.linha < LADOS && pos.coluna < LADOS;
}

// funções Casa_%DIREÇÃO% retornam null se casa não for válida ou não estiver na Board
// Em vez de Casa, quem sabe Vizinho no nome?
struct square* Casa_Cima(Board b, struct square *casa_ptr);

struct square* Casa_Baixo(Board b, struct square *casa_ptr);

struct square* Casa_Esquerda(Board b, struct square *casa_ptr);

struct square* Casa_Direita(Board b, struct square *casa_ptr);

// spawn de números novos
// usar rand() para ver as chances de spawnar 2 ou 4
// usa a função abaixo para encontrar todas as casas vazias
// usar o rand() para escolher o índice no vetor
// atribuir valor a casa vazia pelo pointer
void Spawnar_Numero(Board b);
// preenche o buffer com casas vazias e retorna o total de vazias
void encontra_casas_vazias(Board b, struct square* buffer_vazias[CASAS], int *qtd_vazias);

// funções para as jogadas
// algoritmo para uma jogada:
// 1. começa em um dos cantos
// 2. usa as funções para mover as peças
void Jogada_Cima(Board b);
void Jogada_Baixo(Board b);
void Jogada_Esquerda(Board b);
void Jogada_Direita(Board b);

// funções para mover peças
void Mover_Esquerda(Board b, struct square *casa_ptr);
void Mover_Baixo(Board b, struct square *casa_ptr);
void Mover_Cima(Board b, struct square *casa_ptr);
void Mover_Direita(Board b, struct square *casa_ptr);

int main(void) {
    Board b;
    fill_board(b, 0);
    Spawnar_Numero(b);
    Spawnar_Numero(b);

    // Imprime tabuleiro
    printf("\n");
    imprimir_board(b);

    // Loop
    while (1) {
        char cmd;
        // Lê comando
        printf("\nFaça uma jogada. Use WASD. E para sair: ");
        cmd = getche();

        // Processa comando
        switch (cmd) {
            case 'w': Jogada_Cima(b);       break;
            case 'a': Jogada_Esquerda(b);   break;
            case 's': Jogada_Baixo(b);      break;
            case 'd': Jogada_Direita(b);    break;
            case 'e': goto SAIR;
            default: break;
        }

        // checar se o jogo acabou
        // se não acabou, spawna um número
        Spawnar_Numero(b);
        // se acabou, sair do loop

        // Imprime tabuleiro
        printf("\n");
        imprimir_board(b);
    }

    SAIR:;
}

void fill_board(Board b, int value) {
    int i, j;
    for (i = 0; i < LADOS; i++) {
        for (j = 0; j  < LADOS; j++) {
            b[i][j].valor = value;
        }
    }
}

void imprimir_board(Board b) {
    for (int i = 0; i < LADOS; i++) {
        for (int j = 0; j < LADOS; j++) {
            printf("%4d", b[i][j].valor);
        }
        printf("\n");
    }
}

void Spawnar_Numero(Board b) {
    int qtd_vazias, valor_spawn;
    struct square* buffer_vazias[CASAS];
    encontra_casas_vazias(b, buffer_vazias, &qtd_vazias);

    // calcula o valor para spawnar
    if (rand() % 9) {
        valor_spawn = 2;
    } else {
        valor_spawn = 4;
    }

    if (qtd_vazias > 0) {
        buffer_vazias[rand() % qtd_vazias]->valor = valor_spawn;
    }
}

void encontra_casas_vazias(Board b, struct square* buffer_vazias[CASAS], int *qtd_vazias) {
    *qtd_vazias = 0;
    struct square *p;
    for (p = b[0]; p < b[0] + CASAS; p++) {
        if (p->valor == 0) {
            buffer_vazias[*qtd_vazias] = p;
            *qtd_vazias += 1;
        }
    }
}

void Jogada_Cima(Board b) {
    for (int linha = 1; linha < LADOS; linha++) {
        for (int col = 0; col < LADOS; col++) {
            Mover_Cima(b, &b[linha][col]);
        }
    }
}

void Mover_Cima(Board b, struct square *casa_ptr) {
    struct square* vizinho = Casa_Cima(b, casa_ptr);
    
    if (vizinho == NULL) {
        return;
    } else if (vizinho->valor == 0) {
        vizinho->valor = casa_ptr->valor;
        casa_ptr->valor = 0;
        Mover_Cima(b, vizinho);
    } else if (vizinho->valor == casa_ptr->valor) {
        vizinho->valor += casa_ptr->valor;
        casa_ptr->valor = 0;
    } else {
        return;
    }
}

struct square* Casa_Cima(Board b, struct square *casa_ptr) {
    struct posicao pos;
    Posicao_Casa(b, casa_ptr, &pos);
    pos.linha = pos.linha - 1;
    if (pos.linha < 0) return NULL;
    return &b[pos.linha][pos.coluna];
}

void Jogada_Baixo(Board b) {
    for (int linha = 2; linha >= 0; linha--) {
        for (int col = 0; col < LADOS; col++) {
            Mover_Baixo(b, &b[linha][col]);
        }
    }
}

void Mover_Baixo(Board b, struct square *casa_ptr) {
        struct square* vizinho = Casa_Baixo(b, casa_ptr);
    
    if (vizinho == NULL) {
        return;
    } else if (vizinho->valor == 0) {
        vizinho->valor = casa_ptr->valor;
        casa_ptr->valor = 0;
        Mover_Baixo(b, vizinho);
    } else if (vizinho->valor == casa_ptr->valor) {
        vizinho->valor += casa_ptr->valor;
        casa_ptr->valor = 0;
    } else {
        return;
    }
}

struct square* Casa_Baixo(Board b, struct square *casa_ptr) {
    struct posicao pos;
    Posicao_Casa(b, casa_ptr, &pos);
    pos.linha = pos.linha + 1;
    if (!(pos.linha < LADOS)) return NULL;
    return &b[pos.linha][pos.coluna];
}

struct square* Casa_Direita(Board b, struct square *casa_ptr) {
    struct posicao pos;
    Posicao_Casa(b, casa_ptr, &pos);
    pos.coluna = pos.coluna + 1;
    if (!(pos.coluna < LADOS)) return NULL;
    return &b[pos.linha][pos.coluna];
}

void Mover_Direita(Board b, struct square *casa_ptr) {
    struct square* vizinho = Casa_Direita(b, casa_ptr);
    
    if (vizinho == NULL) {
        return;
    } else if (vizinho->valor == 0) {
        vizinho->valor = casa_ptr->valor;
        casa_ptr->valor = 0;
        Mover_Direita(b, vizinho);
    } else if (vizinho->valor == casa_ptr->valor) {
        vizinho->valor += casa_ptr->valor;
        casa_ptr->valor = 0;
    } else {
        return;
    }
}

void Jogada_Direita(Board b) {
    for (int col = 3; col >= 0; col--) {
        for (int linha = 0; linha < LADOS; linha++) {
            Mover_Direita(b, &b[linha][col]);
        }
    }
}

void Jogada_Esquerda(Board b) {
    for (int col = 1; col < LADOS; col++) {
        for (int linha = 0; linha < LADOS; linha++) {
            Mover_Esquerda(b, &b[linha][col]);
        }
    }
}

struct square* Casa_Esquerda(Board b, struct square *casa_ptr) {
    struct posicao pos;
    Posicao_Casa(b, casa_ptr, &pos);
    pos.coluna = pos.coluna - 1;
    if (pos.coluna < 0) return NULL;
    return &b[pos.linha][pos.coluna];
}

void Mover_Esquerda(Board b, struct square *casa_ptr) {
    struct square* casa_esq = Casa_Esquerda(b, casa_ptr);
    
    if (casa_esq == NULL) {
        return;
    } else if (casa_esq->valor == 0) {
        casa_esq->valor = casa_ptr->valor;
        casa_ptr->valor = 0;
        Mover_Esquerda(b, casa_esq);
    } else if (casa_esq->valor == casa_ptr->valor) {
        casa_esq->valor += casa_ptr->valor;
        casa_ptr->valor = 0;
    } else {
        return;
    }
}
