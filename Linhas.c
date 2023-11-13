//
// Created by joaom on 04/05/2023.
//

#include "Linhas.h"

plinha adicionaLinha(plinha p, int numP, Paragens* paragens){
    plinha novo;  //Ponteiro para a nova linha
    char nomeLinha[TAM];
    char codigoParagem[TAM];
    int existe,registada;

    fflush(stdin);
    printf("Introduza o nome da linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strlen(nomeLinha) - 1] = '\0';

    plinha aux = p;
    while(aux != NULL){  //percorrer as linhas para verificar se já existe uma linha com o mesmo nome
        if(strcmp(aux->nome,nomeLinha) == 0){
            printf("[ERRO]Ja existe uma linha com este nome\n");
            return p;
        }
        aux = aux->proxLinha;
    }

    printf("Linha %s adicionada com sucesso\n", nomeLinha);

    if((novo = malloc(sizeof(linha))) == NULL) {
        printf("Erro na alocacao de memoria\n");
    }else{
        strcpy(novo->nome, nomeLinha); //copiar o nome da linha do utilizador para a variavel nome da nova linha
        novo->PLparagem = NULL; // nao existe nenhuma paragem ainda
        novo->proxLinha = p; //ligar a nova linha à linha existente
        p = novo; //apontar para a nova linha
    }

    do {
        printf("Introduza o codigo da paragem a adicionar:\n");
        printf("Para terminar a operacao digite 0\n");
        printf(">>");
        scanf("%s", codigoParagem);

        if(strcmp(codigoParagem,"0") == 0)
            break;

        existe = 0;
        paragensLinhas* temp = novo->PLparagem;
        while (temp != NULL){ // Verifica se a paragem já foi adicionada à linha
            if(strcmp(temp->codigo, codigoParagem) == 0){
                printf("[ERRO]A paragem com o codigo %s ja foi adicionada a esta linha.\n",codigoParagem);
                existe = 1;
                break;
            }
            temp = temp->proxparagem;
        }

        if(existe)
            continue; // ignora o restante código e regressa ao while

        registada = 0;
        plinha paragem = novo; //apontar para o mesmo que o novo
        for(int i = 0; i<numP; i++){
            if(strcmp(paragens[i].codigo,codigoParagem) == 0){ // se o codigo existir
                registada = 1;
                paragensLinhas* novaParagem = malloc(sizeof(paragensLinhas)); // alocar a nova estrutura do tipo ParagensLinhas
                strcpy(novaParagem->nome, paragens[i].nome); //copiar o nome
                strcpy(novaParagem->codigo, codigoParagem); // copiar o codigo
                strcpy(novaParagem->paragemqpertence, paragem->nome);
                strcpy(paragens[i].linhaqpertence, paragem->nome);
                if (paragem->PLparagem == NULL) {
                    paragem->PLparagem = novaParagem; // nao existe paragens na linha, torna-se a primeira
                } else {
                    paragensLinhas* auxiliar = paragem->PLparagem;
                    while (auxiliar->proxparagem != NULL) { // percorrer lista
                        auxiliar = auxiliar->proxparagem;   //atualizar lista
                    }
                    auxiliar->proxparagem = novaParagem; // Adiciona a paragem no fim da lista
                }
                novaParagem->proxparagem = NULL;
                novo = paragem;
                printf("Paragem %s com o codigo %s adicionada com sucesso a linha %s\n",novaParagem->nome,novaParagem->codigo,novo->nome);
                break;
            }
        }

        if(!registada)
            printf("[ERRO] A paragem com o codigo %s nao existe\n", codigoParagem);

    } while (1);
    return p;
}

void visualizaLinha(plinha p){
    plinha aux = p;

    while(aux != NULL) // percorrer as linhas
    {
        printf("Linha: %s\n", aux->nome);
        printf("Paragens:\n");

        paragensLinhas* aux1 = aux->PLparagem;
        while (aux1 != NULL){ //percorrer as paragens da linha atual
            printf("%s %s\n", aux1->nome, aux1->codigo);
            aux1 = aux1->proxparagem;
        }
        aux = aux->proxLinha;
    }
}

plinha listaEliminaParagemLista(plinha p, Paragens* paragens) {
    char nomeLinha[TAM];
    char cdg[TAM];

    fflush(stdin);
    printf("Introduza o nome da linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strlen(nomeLinha) - 1] = '\0';

    plinha aux = p;

    while (aux != NULL) { //percorrer as linhas
        if (strcmp(aux->nome, nomeLinha) == 0) {
            printf("Qual o codigo da paragem que quer apagar?\n");
            scanf(" %s", &cdg);
            paragensLinhas* aux1 = aux->PLparagem; // primeira paragem
            if (aux1 != NULL && strcmp(aux1->codigo, cdg) == 0) {
                //o codigo é da primeira paragem
                aux->PLparagem = aux1->proxparagem; //atualizar o inicio da lista de paragens
                free(aux1); //libertar a memoria ocupada pela primeira paragem
                printf("Paragem removida com sucesso.\n");
            } else {
                bool paragemEncontrada = true;
                while (aux1 != NULL && aux1->proxparagem != NULL) { //percorrer todas as paragens
                    if (strcmp(aux1->proxparagem->codigo, cdg) == 0) {
                        paragensLinhas* paragemRemover = aux1->proxparagem; //paragem para remover
                        aux1->proxparagem = aux1->proxparagem->proxparagem; //atualizar o ponteiro, ignorar a paragem que foi removida
                        free(paragemRemover); //libertar a memoria ocupada pela paragem
                        printf("Paragem removida com sucesso.\n");
                        paragemEncontrada = false;
                        break;
                    }
                    aux1 = aux1->proxparagem; // avançar nas paragens
                }
                if (paragemEncontrada) { //paragem nao encontrada
                    printf("Paragem nao encontrada.\n");
                }
            }
            break;
        }
        aux = aux->proxLinha;
    }
    return p;
}

plinha adicionaInicio(plinha p, int numP, Paragens* paragens) {
    char nomeLinha[TAM];
    char codigo[TAM];


    fflush(stdin);
    printf("Introduza o nome da linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strlen(nomeLinha) - 1] = '\0';

        plinha atual = p;
        // procurar a linha na lista de linhas
        while (atual != NULL) {
            if (strcmp(atual->nome, nomeLinha) == 0) {
                break;
            }
            atual = atual->proxLinha;
        }

        if (atual == NULL) {
            printf("A linha com o nome %s nao foi encontrada\n", nomeLinha);
            return p;
        }

        printf("Introduza o codigo da paragem a adicionar\n");
        printf("Para terminar a operacao, digite 0.\n");
        printf(">>");
        scanf("%s", codigo);

        while (strcmp(codigo, "0") != 0) {
            bool paragemExistente = false;
            bool paragemEncontrada = false;

            //Verificar se a paragem já existe na linha
            paragensLinhas *temp = atual->PLparagem;
            while (temp != NULL) {
                if (strcmp(temp->codigo, codigo) == 0) {
                    paragemExistente = true;
                    break;
                }
                temp = temp->proxparagem;
            }

            if (paragemExistente) {
                printf("A paragem com o codigo %s ja foi adicionada a esta linha.\n", codigo);
                break;
            } else {
                //procurar a paragem
                for (int i = 0; i < numP; i++) {
                    if (strcmp(paragens[i].codigo, codigo) == 0) {
                        paragemEncontrada = true;
                        paragensLinhas* nova = malloc(sizeof(paragensLinhas));//alocar memoria para a nova paragem
                        strcpy(nova->nome, paragens[i].nome);
                        strcpy(nova->codigo, codigo);
                        nova->proxparagem = atual->PLparagem; // apontar para o inicio da lista
                        atual->PLparagem = nova; //apontar para a nova paragem, ficando a primeira
                        printf("Paragem %s adicionada com sucesso a linha %s\n", nova->nome, atual->nome);
                        break;
                    }
                }
                if (!paragemEncontrada) {
                    printf("A paragem com o codigo %s nao existe\n", codigo);
                    break;
                }
            }

            printf("Adicione outra paragem ou 0 para sair\n");
            printf(">> ");
            scanf("%s", codigo);
        }
    return p;
}

plinha adicionaOrdenado(plinha p, int numP, Paragens* paragens){
    char nomeLinha[TAM];
    char codigo[TAM];
    char codigoAnterior[TAM];

    fflush(stdin);
    printf("Introduza o nome da linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strlen(nomeLinha) - 1] = '\0';

    plinha atual = p;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeLinha) == 0) {
            break;
        }
        atual = atual->proxLinha;
    }

    if (atual == NULL) {
        printf("A linha com o nome %s nao existe\n", nomeLinha);
        return p;
    }

    printf("Introduza o codigo da paragem anterior:\n");
    scanf("%s", &codigoAnterior);

    paragensLinhas *paragemAnterior = NULL;

    //procurar a paragem anterior na lista
    paragensLinhas *temp = atual->PLparagem;
    while (temp != NULL) {
        if (strcmp(temp->codigo, codigoAnterior) == 0) {
            paragemAnterior = temp;
            break;
        }
        temp = temp->proxparagem;
    }

    if (paragemAnterior == NULL) {
        printf("A paragem com o codigo %s nao foi encontrada nesta linha\n", codigoAnterior);
        return p;
    }

    printf("Introduza o codigo da paragem a adicionar:\n");
    printf("Para terminar a operacao, digite 0.\n");
    printf(">>");
    scanf("%s", &codigo);

    while (strcmp(codigo, "0") != 0) {
        bool paragemExistente = false;
        bool paragemEncontrada = false;

        // verificar se a paragem já existe na lista de paragens da linha
        temp = atual->PLparagem;
        while (temp != NULL) {
            if (strcmp(temp->codigo, codigo) == 0) {
                paragemExistente = true;
                break;
            }
            temp = temp->proxparagem;
        }

        if (paragemExistente) {
            printf("A paragem com o codigo %s ja foi adicionada a esta linha.\n", codigo);
            printf("Introduza o codigo da paragem anterior novamente:\n");
            scanf("%s", &codigoAnterior);

            //procurar novamente a paragem anterior
            paragemAnterior = NULL;
            temp = atual->PLparagem;
            while (temp != NULL) {
                if (strcmp(temp->codigo, codigoAnterior) == 0) {
                    paragemAnterior = temp;
                    break;
                }
                temp = temp->proxparagem;
            }

            if (paragemAnterior == NULL) {
                printf("A paragem com o codigo %s nao foi encontrada nesta linha\n", codigoAnterior);
                return p;
            }
        } else {
            for (int i = 0; i < numP; i++) {
                if (strcmp(paragens[i].codigo, codigo) == 0) {
                    paragemEncontrada = true;
                    //Adicionar a nova paragem
                    paragensLinhas *nova = malloc(sizeof(paragensLinhas));
                    strcpy(nova->nome, paragens[i].nome);
                    strcpy(nova->codigo, codigo);
                    nova->proxparagem = paragemAnterior->proxparagem; // inserir a nova paragem após a paragem anterior
                    paragemAnterior->proxparagem = nova; // paragem anterior ter a nova paragem com próxima

                    printf("Paragem %s adicionada com sucesso a linha %s\n", nova->nome, atual->nome);
                    break;
                }
            }
            if (!paragemEncontrada) {
                printf("A paragem com o codigo %s nao existe\n", codigo);
                printf("Introduza o codigo da paragem anterior novamente:\n");
                scanf("%s", codigoAnterior);

                //Procurar novamente a paragem anterior
                paragemAnterior = NULL;
                temp = atual->PLparagem;
                while (temp != NULL) {
                    if (strcmp(temp->codigo, codigoAnterior) == 0) {
                        paragemAnterior = temp;
                        break;
                    }
                    temp = temp->proxparagem;
                }

                if (paragemAnterior == NULL) {
                    printf("A paragem com o codigo %s nao foi encontrada nesta linha\n", codigoAnterior);
                    return p;
                }
            }
        }

        printf("Introduza outra paragem ou 0 para sair\n");
        printf(">>");
        scanf("%s", codigo);
    }

    return p;
}


plinha adicionaFim(plinha p, int numP, Paragens* paragens){
    char nomeLinha[TAM];
    char codigo[TAM];

    fflush(stdin);
    printf("Introduza o nome da linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strlen(nomeLinha) - 1] = '\0';

    //procurar a linha na lista
    plinha atual = p;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeLinha) == 0) {
            break;
        }
        atual = atual->proxLinha;
    }

    if (atual == NULL) {
        printf("A linha com o nome %s nao existe\n", nomeLinha);
        return p;
    }

    printf("Introduza o codigo da paragem a adicionar\n");
    printf("Para terminar a operacao, digite 0.\n");
    printf(">>");
    scanf("%s", codigo);

    while (strcmp(codigo, "0") != 0) {
        bool paragemAdicionada = false;
        bool paragemEncontrada = false;

        //Verificar se a paragem já foi adicionada
        paragensLinhas *temp = atual->PLparagem;
        while (temp != NULL) {
            if (strcmp(temp->codigo, codigo) == 0) {
                paragemAdicionada = true;
                break;
            }
            temp = temp->proxparagem;
        }

        if (paragemAdicionada) {
            printf("A paragem com o codigo %s ja foi adicionada a esta linha.\n", codigo);
            break;
        } else {
            //Procurar a paragem
            for (int i = 0; i < numP; i++) {
                if (strcmp(paragens[i].codigo, codigo) == 0) {
                    paragemEncontrada = true;
                    //Adicionar a paragem
                    paragensLinhas *novo = malloc(sizeof(paragensLinhas));
                    strcpy(novo->nome, paragens[i].nome);
                    strcpy(novo->codigo, codigo);
                    novo->proxparagem = NULL;

                    //Se a lista estiver vazia
                    if (atual->PLparagem == NULL) {
                        atual->PLparagem = novo; //A nova paragem é a primeira
                    } else {
                        //Encontrar o fim
                        paragensLinhas *ultimo = atual->PLparagem;
                        while (ultimo->proxparagem != NULL) {
                            ultimo = ultimo->proxparagem;
                        }
                        //Adicionar a paragem no fim
                        ultimo->proxparagem = novo;
                    }

                    printf("Paragem %s adicionada com sucesso a linha %s\n", novo->nome, atual->nome);
                    break;
                }
            }
            if (!paragemEncontrada) {
                printf("A paragem com o codigo %s nao existe\n", codigo);
                break;
            }
        }

        printf("Introduza outra paragem ou 0 para sair\n");
        printf(">>");
        scanf("%s", codigo);
    }

    return p;
}

void calculaPercurso(plinha p){
    char partida[100];
    char chegada[100];
    bool partidaEncontrada = false;
    bool chegadaEncontrada = false;

    fflush(stdin);
    printf("Introduza o nome da paragem de partida:");
    fgets(partida, sizeof(partida), stdin);
    partida[strlen(partida) - 1] = '\0';

    fflush(stdin);
    printf("Introduza o nome da paragem de chegada:");
    fgets(chegada, sizeof(chegada), stdin);
    chegada[strlen(chegada) - 1] = '\0';

    plinha linhaAtual = p;

    //Percorrer as linhas
    while(linhaAtual != NULL){
        paragensLinhas* paragemAtual = linhaAtual->PLparagem;
        //Percorrer as paragens da linha
        while (paragemAtual != NULL){
            if(strcmp(paragemAtual->nome, partida) == 0){
                partidaEncontrada = true;
            }
            //Verificar a paragem de chegada
            if(partidaEncontrada){
                if(strcmp(paragemAtual->nome,chegada) == 0){
                    printf("Linha %s\n", linhaAtual->nome);
                    chegadaEncontrada = true;
                    break;
                }
            }
            paragemAtual = paragemAtual->proxparagem;
        }
        //Se a chegada foi encontrada, parar o ciclo
        if(chegadaEncontrada)
            break;
        linhaAtual = linhaAtual->proxLinha;
    }

    //Mostrar percurso se a paragem de chegada foi encontrada
    if(chegadaEncontrada){
        partidaEncontrada = false;
        paragensLinhas* temp = linhaAtual->PLparagem;
        while (temp != NULL){
            //Se a partida foi encontrada
            if(strcmp(temp->nome, partida) == 0){
                partidaEncontrada = true;
            }
            //Mostrar percurso se a paragem de partida foi encontrada
            if(partidaEncontrada) {
                printf("%s", temp->nome);
                //Se a paragem atual for a paragem de chegada termina
                if (strcmp(temp->nome, chegada) == 0) {
                    printf("\n");
                    break;
                }
                else{
                    printf("->");
                }
            }
            temp = temp->proxparagem;
        }
    }
}


void liberta_lista(plinha p){
    plinha aux;

    while(p != NULL){
        aux = p;
        p = p ->proxLinha;
        free(aux);
    }
}
