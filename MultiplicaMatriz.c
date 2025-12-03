#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//teste para verificar se tem espaço alocado em nível de coluna
int testeMatrizColuna(int *p){
    if(!p){
       printf("Erro: espaço de memória não alocado (colunas)\n");
       return 1;
    }
    return 0;
}

//teste para verificar se tem espaço alocado em nível de linha
int testeMatrizLinha(int **p){
    if(!p){
        printf("Erro: espaço de memória não alocado (linhas)\n");
        return 1;
    }
    return 0;
}

// Imprime uma linha da matriz de maneira responsiva
void exibeMatrizLinha(int **p, int linha, int coluna, int inicio){
    //enquanto inicio não satifazer a condição faça
    if (inicio >= coluna){
        printf("\n");
        return;
    }
    //imprima o elemento de linha passado do parametro
    //agora com inicio de 0 ao tamanho da linha
    printf("%d ", p[linha][inicio]);
    exibeMatrizLinha(p, linha, coluna, inicio + 1);
}

// percorre cada coluna, que por sua vez percorre as linhas via outra função
void exibeMatrizColuna(int **p, int linha, int coluna, int inicio){
    if (inicio >= linha){
        return;
    }
    exibeMatrizLinha(p, inicio, coluna, 0); // <- usar 'inicio' como índice da linha
    exibeMatrizColuna(p, linha, coluna, inicio + 1);
}

//apenas para informar a qtd de linhas de uma matriz a ser criada por alocação
int informaLinha(void){
    int linha;
    printf("\nInforme a quantidade de linhas da matriz: ");
    scanf("%d",&linha);
    return linha;
}
//para informa a qtd de colunas de uma matriz a ser criada por alocação
int informaColuna(void){
    int coluna;
    printf("\nInforme a quantidade de colunas da matriz: ");
    scanf("%d",&coluna);
    return coluna;
}
//verifica a possibilidade de produto entre matrizes
int verificaMulti(int C1,int L2){
    if(C1!=L2){
        printf("A operação não é possível: número de colunas[%d] da 1ª matriz diferente do número de linhas[%d] da 2ª matriz.\n",C1,L2);
        return 1;
    }
    return 0;
}

void insereLinha(int **p, int linha, int coluna, int inicio) {
    if (inicio >= coluna) {
        printf("\n");
        return;
    }
    int input;
    printf("Informe um elemento para posição [%d][%d]: ", linha, inicio);
    scanf("%d", &input);
    p[linha][inicio] = input;

    insereLinha(p, linha, coluna, inicio + 1);
}

int **insereColuna(int **p, int linha, int coluna, int inicio) {
    if (inicio >= linha) {
        return p;
    }
    insereLinha(p, inicio, coluna, 0);
    printf("Linha %d preenchida\n", inicio);
    printf("\n%d\n",inicio);
    //exibeMatrizColuna(p,linha,coluna,0);
    return insereColuna(p, linha, coluna, inicio + 1);
}

int menu(void){
    int op;
    printf("\n----------------------------");
    printf("\n1 - Inserção de matriz (manual)");
    printf("\n2 - Inserção de dados automática");
    printf("\n0 - Sair do programa");
    printf("\n----------------------------\n");
    scanf("%d", &op);
    return op;
}

/*
void preencheAuto(int **p, int L, int C){
    int v = 1;
    for(int i=0;i<L;i++){
        for(int j=0;j<C;j++){
            p[i][j] = v++;
        }
    }
}
*/

// Libera a memória alocada para a matriz via ponteiro
void liberaMemoria(int **p, int L){
    if(!p) return;
    //abaixo inserir uma função recursiva
    for(int i=0;i<L;i++){
        free(p[i]);
    }
    free(p);
}

//a função abaixo serve apenas para alocar espaço para cada coluna,
//em função das linhas passadas via o contador"inicio"
void preencheColuna(int **p, int linha, int coluna, int inicio){
    if(inicio>=linha){
        return;
    }
    p[inicio] = (int*)calloc(coluna, sizeof(int));
    preencheColuna(p,linha,coluna,inicio+1);
}

void multiplicaMatriz(**p1,**p2,L1)

int main() {
    setlocale(LC_ALL, "Portuguese");

    int L1, C1,L2,C2;
    int **p1,**p2;
    int op = 1;

    while (op != 0) {
        op = menu();
        if (op == 0) break;

        printf("\nDados referente a Matriz 1...\n");
        L1 = informaLinha();
        C1 = informaColuna();

        p1 = (int**)calloc(L1, sizeof(int*));
        //if(testeMatrizLinha(p1)==1) return 0;
        //if(testeMatrizColuna(p1[L1-1])==1) return 0;
        //acima verifica se é possível alocar em linhas
        //exibeMatrizColuna(p1,L1,C1,0);
        preencheColuna(p1,L1,C1,0);
        exibeMatrizColuna(p1,L1,C1,0);


        printf("\nDados referente a Matriz 2...\n");
        L2 = informaLinha();
        C2 = informaColuna();

        p2 = (int**)calloc(L2, sizeof(int*));
        //if(testeMatrizLinha(p2)==1) return 0;
        //acima verifica se é possível alocar em linhas
        //exibeMatrizColuna(p1,L1,C1,0);
        preencheColuna(p2,L2,C2,0);
        exibeMatrizColuna(p2,L2,C2,0);
        //if(testeMatrizColuna(p2[L2-1])==1) return 0;

        if(verificaMulti(C1,L2)==1){
            liberaMemoria(p1, L1);
            liberaMemoria(p2,L2);
        return 0;}
        //opçoes
        if (op == 1) {
            printf("\nInserindo na Matriz 1....\n");
            p1 = insereColuna(p1, L1, C1, 0);
            exibeMatrizColuna(p1, L1, C1, 0);
            printf("\nInserindo na Matriz 2...\n");
            p2 = insereColuna(p2, L2, C2, 0);
            exibeMatrizColuna(p2, L2, C2, 0);
        } else if (op == 2) {
            printf("\nPreenchendo matriz automaticamente....\n");
            //preencheAuto(p1, L1, C1);
        }


        // Libera antes de recomeçar o loop
        liberaMemoria(p1, L1);
        liberaMemoria(p2,L2);
    }

    return 0;
}
