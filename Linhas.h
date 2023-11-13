#ifndef METROMONDEGO_LINHAS_H
#define METROMONDEGO_LINHAS_H
#include "Paragens.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define TAM 100

typedef struct ParagensLinhas paragensLinhas;
struct ParagensLinhas{
    char nome[100];
    char codigo[5];
    paragensLinhas* proxparagem;
    char paragemqpertence[100];
};

typedef struct Linha linha, *plinha;
struct Linha{
    char nome[100];
    plinha proxLinha;
    paragensLinhas* PLparagem;
};



void liberta_lista(plinha p);
plinha adicionaLinha(plinha p, int numP,Paragens* paragens);
plinha listaEliminaParagemLista(plinha p, Paragens* paragens);
plinha adicionaInicio(plinha p, int numP, Paragens* paragens);
plinha adicionaFim(plinha p, int numP, Paragens* paragens);
plinha adicionaOrdenado(plinha p, int numP, Paragens* paragens);
void visualizaLinha(plinha p);
void calculaPercurso(plinha p);

#endif //METROMONDEGO_LINHAS_H
