//
// Created by joaom on 30/05/2023.
//

#ifndef METROMONDEGO_DATA_H
#define METROMONDEGO_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linhas.h"
#include "Paragens.h"

Paragens* leDadosParagens(int *total);
void guardaDadosParagens(Paragens* paragens, int total);
int getTotalParagens(char *nomeF);

void guardarDadosLinhas(plinha p);
plinha carregarDadosLinhas();
#endif //METROMONDEGO_DATA_H
