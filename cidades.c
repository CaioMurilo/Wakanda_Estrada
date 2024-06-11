#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

/*

10              <-- Comprimento da estrada
2               <-- Número de cidades
8 Birnin Zana   <-- Cidade 1
5 Birnin S'Yan  <-- Cidade 2

*/

// Para inicializar as cidades a partir do arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fprintf(stderr, "Erro ao alocar memoria para Estrada.\n");
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d", &(estrada->T)); // Para ler o comprimento da estrada
    fscanf(file, "%d", &(estrada->N));  // Para ler o numero de cidades.

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        fprintf(stderr, "Erro ao alocar memoria para cidades.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(file, "%d ", &(estrada->C[i].Posicao));
        fgets(estrada->C[i].Nome, sizeof(estrada->C[i].Nome), file);
        estrada->C[i].Nome[strcspn(estrada->C[i].Nome, "\n")] = 0;      // remove a quebra de linha
    }

    fclose(file);
    return estrada;
}

// Calcular a menor vizinhança
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1;

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double inicioVizinhanca = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        double fimVizinhanca = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        double vizinhanca = fimVizinhanca - inicioVizinhanca;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Retornar o nome da cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;
        char *cidade = (char *)malloc(strlen(estrada->C[0].Nome) + 1);
        strcpy(cidade, estrada->C[0].Nome);

    free(estrada->C);
    free(estrada);

    return cidade;
}
