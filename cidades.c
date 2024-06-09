#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h" // Inclui cidades.h

/*

10              <-- Comprimento da estrada
2               <-- Número de cidades
8 Birnin Zana   <-- Cidade 1
5 Birnin S'Yan  <-- Cidade 2

*/

// Função para ler os dados da estrada e cidades a partir de um arquivo
Estrada *getEstrada(const char *nomeArquivo) {

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    printf("Abrindo arquivo: %s\n", nomeArquivo);

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));

    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d %d", &estrada->T, &estrada->N) != 2) {
        
        free(estrada);
        fclose(arquivo);

        return NULL;
    }

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
       
        free(estrada);
        fclose(arquivo);

        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));

    if (estrada->C == NULL) {

        free(estrada);
        fclose(arquivo);

        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {

        if (fscanf(arquivo, "%d", &estrada->C[i].Posicao) != 1) {

            printf("Erro ao ler a posicao da cidade %d.\n", i + 1);

            free(estrada->C);
            free(estrada);
            fclose(arquivo);

            return NULL;
        }

        if (fgets(estrada->C[i].Nome, sizeof(estrada->C[i].Nome), arquivo) == NULL) {

            printf("Erro ao ler o nome da cidade %d.\n", i + 1);

            free(estrada->C);
            free(estrada);
            fclose(arquivo);

            return NULL;
        }

        estrada->C[i].Nome[strcspn(estrada->C[i].Nome, "\n")] = 0;  // Remove a quebra de linha
        printf("Cidade %d: Posicao: %d, Nome: %s\n", i + 1, estrada->C[i].Posicao, estrada->C[i].Nome);

        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {

            printf("Erro: Posicao invalida para a cidade %d.\n", i + 1);

            free(estrada->C);
            free(estrada);
            fclose(arquivo);

            return NULL;
        }
    }

    fclose(arquivo);

    return estrada;
}

// Função para calcular a menor vizinhança entre as cidades
double calcularMenorVizinhancaEstrada(Estrada *estrada) {

    if (estrada == NULL) {
        printf("Erro: Estrada nao inicializada.\n");

        return -1;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N - 1; i++) {

        double vizinhanca = (double)abs(estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;

        printf("Calculo da vizinhanca entre as duas cidades: %.2lf\n", vizinhanca);

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    return menorVizinhanca;
}

// Função para determinar a cidade com a menor vizinhança
char *cidadeMenorVizinhancaEstrada(Estrada *estrada) {

    if (estrada == NULL) {
        printf("Erro: Estrada nao inicializada.\n");

        return NULL;
    }

    double menorVizinhanca = estrada->T;
    int indiceMenorVizinhanca = -1;

    for (int i = 0; i < estrada->N - 1; i++) {

        double vizinhanca = (double)abs(estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMenorVizinhanca = i;
        }
    }

    char *resultado = (char *)malloc(256 * sizeof(char));

    if (resultado == NULL) {
        return NULL;
    }

    if (indiceMenorVizinhanca != -1) {
        strcpy(resultado, estrada->C[indiceMenorVizinhanca].Nome);
    } else {
        free(resultado);

        resultado = NULL;
    }

    return resultado;
}

// Função para calcular a menor vizinhança usando o arquivo
double calcularMenorVizinhanca(const char *nomeArquivo) {

    Estrada *estrada = getEstrada(nomeArquivo);

    if (estrada == NULL) {
        return -1;
    }

    double resultado = calcularMenorVizinhancaEstrada(estrada);

    free(estrada->C);
    free(estrada);

    return resultado;
}

// Função para determinar a cidade com a menor vizinhança usando o arquivo
char *cidadeMenorVizinhanca(const char *nomeArquivo) {

    Estrada *estrada = getEstrada(nomeArquivo);

    if (estrada == NULL) {
        return NULL;
    }

    char *resultado = cidadeMenorVizinhancaEstrada(estrada);

    free(estrada->C);
    free(estrada);

    return resultado;
}

int main() {

    const char *nomeArquivo = "teste01.txt";
    Estrada *estrada = getEstrada(nomeArquivo);

    if (estrada == NULL) {
        printf("Erro ao ler os dados da estrada.\n");

        return 1;
    }

    double menorVizinhanca = calcularMenorVizinhancaEstrada(estrada);

    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhanca.\n");

        free(estrada->C);
        free(estrada);

        return 1;
    }

    printf("Menor vizinhanca: %.2lf\n", menorVizinhanca);

    char *cidadeMenorViz = cidadeMenorVizinhancaEstrada(estrada);

    if (cidadeMenorViz == NULL) {
        printf("Erro ao determinar a cidade com menor vizinhanca.\n");

        free(estrada->C);
        free(estrada);

        return 1;
    }

    printf("Cidade com menor vizinhanca: %s\n", cidadeMenorViz);

    free(cidadeMenorViz);
    free(estrada->C);
    free(estrada);

    return 0;
}