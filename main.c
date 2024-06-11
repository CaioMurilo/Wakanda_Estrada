#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhanca.\n");
        return 1;
    }

    printf("Menor vizinhanca: %.2lf\n", menorVizinhanca);

    char *cidadeMenorViz = cidadeMenorVizinhanca(nomeArquivo);
    if (cidadeMenorViz == NULL) {
        printf("Erro ao determinar a cidade com menor vizinhanca.\n");
        return 1;
    }

    printf("Cidade com menor vizinhanca: %s\n", cidadeMenorViz);

    free(cidadeMenorViz);
    return 0;
}
