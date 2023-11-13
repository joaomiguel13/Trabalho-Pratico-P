#include <stdio.h>
#include "Paragens.h"
#include "Linhas.h"
#include "data.h"

Paragens *paragens = NULL;
plinha listaLinhas = NULL;
int numParagens = 0;

void menuEscolheOrdem(){
    char opcao;
    do{
        printf("Escolha uma opcao:\n");
        printf("1 - Inserir paragem no inicio\n");
        printf("2 - Inserir paragem ordenada\n");
        printf("3 - Inserir paragem no fim\n");
        printf("4 - Voltar\n");
        printf(">> ");
        scanf(" %c",&opcao);

        switch(opcao){
            case '1':
                adicionaInicio(listaLinhas, numParagens, paragens);
                break;
            case '2':
                adicionaOrdenado(listaLinhas,numParagens,paragens);
                break;
            case '3':
                adicionaFim(listaLinhas, numParagens, paragens);
                break;
        }
    } while (opcao != '4');
}

void menuAtualizaLinha(){
    char opcao;
    do{
        printf("Escolha uma opcao:\n");
        printf("1 - Eliminar paragem\n");
        printf("2 - Adicionar paragem\n");
        printf("3 - Voltar\n");
        printf(">> ");
        scanf(" %c",&opcao);

        switch (opcao) {
            case '1':
                listaEliminaParagemLista(listaLinhas, paragens);
                break;
            case '2':
                menuEscolheOrdem();
                break;
        }
    } while (opcao != '3');
}

void menuLinhas(){
    char opcao;

    do{
        printf("Escolha uma opcao:\n");
        printf("1 - Adicionar Linha\n");
        printf("2 - Atualizar Linha\n");
        printf("3 - Visualizar Linhas\n");
        printf("4 - Voltar ao menu principal\n");
        printf(">> ");
        scanf(" %c", &opcao);

        switch(opcao){
            case '1':
                listaLinhas = adicionaLinha(listaLinhas, numParagens, paragens);
                break;
            case '2':
                menuAtualizaLinha();
                break;
            case '3':
                visualizaLinha(listaLinhas);
                break;
        }
    }while(opcao != '4');
};

void menuParagens(){
    char opcao;

    do{
        printf("Escolha uma opcao:\n");
        printf("1 - Registar Paragem\n");
        printf("2 - Eliminar Paragem\n");
        printf("3 - Visualizar Paragens\n");
        printf("4 - Voltar ao menu principal\n");
        printf(">> ");
        scanf(" %c", &opcao);

        switch(opcao){
            case '1':
                paragens = registaParagem(paragens, &numParagens);
                break;
            case '2':
                eliminaParagem(paragens, &numParagens);
                break;
            case '3':
                visualizaParagem(paragens,numParagens);
                break;
        }
    }while(opcao != '4');
}


void mostraMenuInicial(){
    char op;

    do{
        printf("Bem-vindo ao Metro Mondego\n");
        printf("1 - Paragens\n");
        printf("2 - Linhas\n");
        printf("3 - Calcular percurso\n");
        printf("4 - Sair\n");
        printf(">> ");
        scanf(" %c", &op);

        switch(op){
            case '1':
                menuParagens();
                break;
            case '2':
                menuLinhas();
                break;
            case '3':
                calculaPercurso(listaLinhas);
                break;
            case '4':
                printf("A sair...");
        }

    }while(op != '4');
}


int main(){
    paragens = leDadosParagens(&numParagens);
    listaLinhas = carregarDadosLinhas();
    mostraMenuInicial();
    guardaDadosParagens(paragens,numParagens);
    guardarDadosLinhas(listaLinhas);
    liberta_lista(listaLinhas);
    return 0;
}