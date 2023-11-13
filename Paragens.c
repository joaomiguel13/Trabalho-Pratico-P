//
// Created by joaom on 04/05/2023.
//

#include "Paragens.h"

void geraCodigo(Paragens* paragens) {
    int codigo,i;
    char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int quantidadeCaracteres = sizeof(caracteres) -1;

    srand(time(NULL));

    for(i = 0; i<4; i++){
        codigo = rand() % quantidadeCaracteres;
        paragens->codigo[i] = caracteres[codigo];
    }

    paragens->codigo[4] = '\0';
}

void visualizaParagem(Paragens* paragens, int total){
    int i;
    printf("Existem %d paragens:\n", total);
    for(i=0;i<total;i++){
        printf("Nome:%s\tCodigo:%s\n", paragens[i].nome, paragens[i].codigo);
    }
}

Paragens* registaParagem(Paragens* paragens, int* total) {
    Paragens* temp = realloc(paragens, sizeof(Paragens) * (*total + 1));
    Paragens novaParagem;
    int i, existe;

    if(temp != NULL){
        paragens = temp;

        do {
            fflush(stdin);
            printf("Introduza o nome da paragem:");
            fgets(novaParagem.nome, sizeof(Paragens), stdin);
            novaParagem.nome[strlen(novaParagem.nome) - 1] = '\0'; //Revomer o '\0'

            existe = 0;
            for (i = 0; i < *total; i++) {
                if (strcmp(novaParagem.nome, paragens[i].nome) == 0) {
                    printf("Ja existe uma paragem com esse nome.\n");
                    existe = 1;
                    break;
                }
            }
        } while (existe);

        bool isCodigoUnico;
        do {
            isCodigoUnico = true;
            geraCodigo(&novaParagem); // codigo random
            for (i = 0; i < *total; i++) {
                if (strcmp(novaParagem.codigo, paragens[i].codigo) == 0) {
                    isCodigoUnico = false;
                    break;
                }
            }
        } while (!isCodigoUnico);

        strcpy(novaParagem.linhaqpertence, ""); // para já, a paragem não pertence a nenhuma linha

        paragens[*total] = novaParagem; // Adicionar a nova paragem à estrutura
        (*total)++; // numero total de paragens incrementado
        printf("Paragem registada com sucesso.\n");
    }
    else {
        printf("Erro ao alocar memória!\n");
    }

    return paragens; //retornar o array de estruturas paragens atualizado
}

Paragens* eliminaParagem(Paragens* paragens, int *total){
    char codigo[5];
    int i;
    Paragens* aux, t;

    printf("Introduza o codigo da paragem a ser eliminada: ");
    scanf(" %s", &codigo);



    for(i = 0; i<*total && strcmp(codigo, paragens[i].codigo) != 0; i++) //procurar a paragem com o codigo
            ;
        if(i == *total){
            printf("O codigo nao existe\n");
            return paragens;
        } else if(*total == 1 && strcmp(paragens[i].linhaqpertence,"") == 0){ // so existe uma paragem e nao pertence a nenhuma linha
            free(paragens); // libertamos a memória do array de estruturas paragens
            *total = 0; //atualizamos o total de paragens
            printf("Paragem eliminada com sucesso\n");
            return NULL; //não existem mais paragens
        }
        else if(strcmp(paragens[i].linhaqpertence, "") == 0){ //existe mais do que uma paragem
                t = paragens[i]; //paragem que será movida
                paragens[i] = paragens[*total-1]; // substituir a paragem a ser eliminada pela útlima paragem
                aux = realloc(paragens, sizeof(Paragens) * (*total-1)); // realocar memória para o novo tamanho do array de estruturas
                if(aux != NULL){
                    paragens = aux;
                    (*total)--;
                }
                else
                    paragens[i] = t;
                printf("Paragem eliminada com sucesso!\n");
            }
        else{
            printf("Esta paragem esta associada a uma linha!\n");
        }
    return paragens; // return do ponteiro para o array de estruturas atualizado
}
