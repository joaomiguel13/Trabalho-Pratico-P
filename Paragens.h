#ifndef METROMONDEGO_PARAGENS_H
#define METROMONDEGO_PARAGENS_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct{
    char nome[100];
    char codigo[5];
    char linhaqpertence[100];
} Paragens;

Paragens* registaParagem(Paragens *paragens, int *total);
Paragens* eliminaParagem(Paragens *paragens, int *total);
void visualizaParagem(Paragens* paragens, int total);
void geraCodigo(Paragens* paragens);

#endif //METROMONDEGO_PARAGENS_H
