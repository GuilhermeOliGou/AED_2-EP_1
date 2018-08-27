#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap_binario.h"
#include "grafo_listaadj.h"

#define DBL_MAX 2147483647

void relaxamentos (TipoGrafo* grafo, HeapBinario* heap, int indice, int* anterior){
    if (indice <= 0){
        printf("Vértice está abaixo dos limites do grafo!\n");
        return;
    }
    if (indice > obtemNrVertices(grafo)){
        printf("Vértice está acima dos limites do grafo!\n");
        return;
    }
    TipoApontador arestaAtual = primeiroListaAdj(indice, grafo);
    double novoPeso;
    int vDestino;
    while (arestaAtual){
        printHeap(heap);
        novoPeso = retornaDistancia(heap,indice)+obtemPesoInstantaneo(arestaAtual);
        vDestino = verticeDestino(arestaAtual,grafo);
        printf("%lf + %lf < %lf\n",retornaDistancia(heap,indice),obtemPesoInstantaneo(arestaAtual), retornaDistancia(heap,vDestino));
        if (novoPeso < retornaDistancia(heap,vDestino)){
            alteraElemento(heap,vDestino,novoPeso);
            anterior[verticeDestino(arestaAtual,grafo)] = indice;
        }
        arestaAtual = proxListaAdj(indice,grafo,arestaAtual);
    }
}

bool dijkstra (TipoGrafo* grafo, int tamanhoGrafo, int s, double* distancias, int* anterior){
    if (tamanhoGrafo <= 0){
        printf("Tamanho do grafo abaixo do limite permitido!\n");
        return false;
    }
    if (tamanhoGrafo > obtemNrVertices(grafo)){
        printf("Tamanho do grafo acima do limite permitido!\n");
        return false;
    }
    if (s <= 0){
        printf("Vértice origem está abaixo dos limites do grafo!\n");
        return false;
    }
    if (s > obtemNrVertices(grafo)){
        printf("Vértice origem está acima dos limites do grafo!\n");
        return false;
    }
    HeapBinario heap;
    if (!buildHeap(&heap,tamanhoGrafo,s)){
        printf("Falha na criação do heap!\n");
        return false;
    }
    int i;
    for (i = 1; i <= tamanhoGrafo; i++)
        anterior[i] = -1;
    int indice;
    while (possuiElementos(&heap)){
        indice = popElementoPrioritario(&heap);
        relaxamentos(grafo,&heap,indice,anterior);
        excluiElementoPrioritario(&heap);
    }
    for (i = 1; i <= tamanhoGrafo; i++)
        distancias[i] = retornaDistancia(&heap,i);
    return true;
}

bool recebeEntrada (TipoGrafo* grafo, int* inicial, FILE* entrada){
    int s;
    fscanf(entrada,"%d\n",&s);
    *inicial = s;

    int nv, na;
    fscanf(entrada,"%d %d\n",&nv,&na);

    if (!inicializaGrafo(grafo,nv)){
        printf("Grafo não foi criado!\n");
        return false;
    }

    int v1, v2;
    TipoPeso peso;

    int i;
    for (i = 0; i < na; i++){
        fscanf(entrada,"%d %d %lf\n",&v1,&v2,&peso);
        insereAresta(v1,v2,peso,grafo);
    }

    fclose(entrada);
    return true;
}

void escreveSaida (TipoGrafo* grafo, int s, FILE* saida){
    int i;
    int tamanhoGrafo = obtemNrVertices(grafo);
    double* distancias = (double*)calloc(tamanhoGrafo+1, sizeof(double));
    if (!distancias){
        printf("Não há espaço suficiente para criar vetor de distâncias!\n");
        return;
    }
    int* anterior = (int*)calloc(tamanhoGrafo+1, sizeof(int));
    if (!anterior){
        printf("Não há espaço suficiente para criar vetor de anteriores!\n");
        return;
    }
    if (!dijkstra(grafo,tamanhoGrafo,s,distancias,anterior)){
        printf("Falha na execução do dijkstra!\n");
        return;
    }
    for (i = 1; i <= tamanhoGrafo; i++){
        fprintf(saida,"%d ", i);
        if (distancias[i] == DBL_MAX){
            fprintf(saida,"%.2e ", DBL_MAX);
        }else{
            fprintf(saida,"%f ", distancias[i]);
        }
        fprintf(saida,"%d\n", anterior[i]);
    }
    fclose(saida);
}

int main(int argc, char** argv){
    FILE* entrada = fopen(argv[1],"rt");
    FILE* saida = fopen(argv[2],"rt");

    TipoGrafo grafo;
    int s;

    if (recebeEntrada(&grafo,&s,entrada)){

        escreveSaida(&grafo,s,saida);
    }else{
        printf("Arquivo não foi lido!\n");
    }
    return 1;
}
