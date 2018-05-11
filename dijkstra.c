#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap_binario.h"
#include "grafo_listaadj.h"

#define DBL_MAX INFINITY

bool inicializaDistanciaEAnterior (int v, double* distancias, int* anterior){
    distancias = (double*)calloc(v+1, sizeof(double));
    if (!distancias){
        printf("Não há espeço suficiente para criar vetor de distâncias!\n");
        return false;
    }
    anterior = (int*)calloc(v+1, sizeof(int));
    if (!anterior){
        printf("Não há espeço suficiente para criar vetor de anteriores!\n");
        return false;
    }
    return true;
}

void relaxamentos (TipoGrafo* grafo, HeapBinario* heap, int indice, int* anterior){
    if (indice <= 0){
        printf("Vértice está abaixo dos limites do grafo!\n");
        return false;
    }
    if (indice >= obtemNrVertices(grafo)){
        printf("Vértice está acima dos limites do grafo!\n");
        return false;
    }
    TipoApontador arestaAtual = primeiroListaAdj(indice, grafo);
    double novoPeso;
    int vDestino;
    while (arestaAtual){
        novoPeso = retornaDistancia(heap,indice)+obtemPesoInstantaneo(arestaAtual);
        vDestino = verticeDestino(arestaAtual,grafo);
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
    if (tamanhoGrafo <= obtemNrVertices(grafo)){
        printf("Tamanho do grafo acima do limite permitido!\n");
        return false;
    }
    if (s <= 0){
        printf("Vértice origem está abaixo dos limites do grafo!\n");
        return false;
    }
    if (s >= obtemNrVertices(grafo)){
        printf("Vértice origem está acima dos limites do grafo!\n");
        return false;
    }
    HeapBinario heap;
    if (!buildHeap(&heap,tamanhoGrafo,s) || inicializaDistanciaEAnterior(tamanhoGrafo,distancias,anterior)){
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
    }
    for (i = 1; i <= tamanhoGrafo; i++)
        distancias[i] = retornaDistancia(&heap,i);
    return true;
}

void EscreveSaida (TipoGrafo* grafo, int s){
    int i;
    int tamanhoGrafo = obtemNrVertices(grafo);
    double* distancias;
    int* anterior;
    if (!dijkstra(grafo,tamanhoGrafo,s,distancias,anterior)){
        printf("Falha na execução do dijkstra!\n");
        return;
    }
    for (i = 1; i <= tamanhoGrafo; i++){
        //escreve i, distancias[i] e anterior[i]
    }
}

int main(){
    return 1;
}
