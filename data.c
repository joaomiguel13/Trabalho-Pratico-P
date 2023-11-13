//
// Created by joaom on 30/05/2023.
//

#include "data.h"

int getTotalParagens(char *nomeF){
    FILE *f;
    Paragens aux;
    int total = 0;
    f = fopen(nomeF, "rb");
    if(f==NULL)
        return 0;
    while(fread(&aux, sizeof(Paragens), 1, f) == 1)
        total++;
    fclose(f);
    return total;
}

Paragens* leDadosParagens(int *total){
    FILE *f;
    Paragens *b = NULL;
    *total = getTotalParagens("paragens.dat"); //Total de paragens no ficheiro
    if (*total == 0)
        return NULL;
    f = fopen("paragens.dat", "rb");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return NULL;
    }
    b = malloc(sizeof(Paragens) * (*total)); // Alocar memória para as paragens
    if(b == NULL){
        fclose(f); *total = 0;
        return NULL;
    }
    fread(b, sizeof(Paragens), *total, f); // Ler os dados e guardar em b
    fclose(f);
    return b;
}

void guardaDadosParagens(Paragens* paragens, int total){
    FILE *f;
    f = fopen("paragens.dat", "wb");
    if(f==NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
    fwrite(paragens, sizeof(Paragens), total, f); // Escrever as paragens no ficheiro
    fclose(f);
}

void guardarDadosLinhas(plinha p) {
    FILE *f;
    f = fopen("linhas.dat", "wb");

    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }


    plinha aux = p;

    while (aux != NULL) {  // Percorrer as linhas
        fwrite(aux, sizeof(linha), 1, f);  // Escrever a estrutura linha no ficheiro

        paragensLinhas* aux1 = aux->PLparagem;
        while (aux1 != NULL) {  // Percorrer as paragens da linha atual
            fwrite(aux1, sizeof(paragensLinhas), 1, f);  // Escrever a estrutura paragensLinhas no ficheiro
            aux1 = aux1->proxparagem;
        }

        aux = aux->proxLinha;
    }

    fclose(f);
}


plinha carregarDadosLinhas() {
    FILE *f;
    f = fopen("linhas.dat", "rb");

    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }

    plinha p = NULL; //ponteiro para a lista de linhas
    plinha aux = NULL; // ponteiro para percorer as linhas
    plinha novaLinha = NULL; // ponteiro para uma nova linha

    while (1) {
        novaLinha = malloc(sizeof(linha));
        if (fread(novaLinha, sizeof(linha), 1, f) != 1) { // ler a linha do ficheiro
            free(novaLinha);
            break;  // Sair do loop se a houver erro de leitura ou chegar ao fim do ficheiro
        }
        novaLinha->proxLinha = NULL;
        novaLinha->PLparagem = NULL;

        if (p == NULL) {
            p = novaLinha; // se a lista estiver vazia, a nova linha é a primeira
        } else {
            aux->proxLinha = novaLinha; // adicionar a nova linha à lista
        }

        aux = novaLinha;

        paragensLinhas* auxParagem = NULL; //Percorrer a lista de paragens das linhas
        paragensLinhas* novaParagem = NULL; //Nova paragem

        while (1) {
            novaParagem = malloc(sizeof(paragensLinhas));
            if (fread(novaParagem, sizeof(paragensLinhas), 1, f) != 1) { // ler as paragens do ficheiro
                free(novaParagem);
                break;  // Sair do loop se a houver erro de leitura ou chegar ao fim do ficheiro
            }
            novaParagem->proxparagem = NULL;

            if (aux->PLparagem == NULL) {
                aux->PLparagem = novaParagem; // se nao existirem paragens a nova paragem é a primeira
            } else {
                auxParagem->proxparagem = novaParagem;//adicionar paragem
            }
            auxParagem = novaParagem;
        }
    }

    fclose(f);
    return p;
}