#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Implementa��o usando vetores

typedef struct {
    int distancia;/* Representa a dist�ncia de um v�rtice em rela��o ao S*/
    int mapaDeRetorno;/* Indica a qual v�rtice do grafo representa essa determinada dist�ncia*/
}NO;

typedef struct {
    NO* arvore; /* Cada �ndice representa um n� da �rvore heap
                Organizado na ordem correta
                O �ndice 1 representa a raiz, ou aquele que tem amior prioridade*/

    int* mapa; /* Os �ndices representam os v�rtices do grafo
                Os valores representam a posi��o deles na �rvore Heap
                �ndice 1 representa o primeiro v�rtice do grafo*/
    int numElementos;
    int maxElementos;
}HeapBinario;

/* Essa fun��o inverte dois v�rtices na estrutura interna da �rvore
Ela pega como par�metro o heap de onde os NOs tem origem
E os dois n�s que ela deve alterar*/
void inverterNaArvore (HeapBinario* heap, int v1, int v2){
    int aux1 = heap->arvore[v1].distancia;
    int aux2 = heap->arvore[v1].mapaDeRetorno;
    heap->arvore[v1].distancia = heap->arvore[v2].distancia;
    heap->arvore[v1].mapaDeRetorno = heap->arvore[v2].mapaDeRetorno;
    heap->arvore[v2].distancia = aux1;
    heap->arvore[v2].mapaDeRetorno = aux2;
}

/* Essa fun��o inverte dois v�rtices na estrutura do mapa de indexa��o
Ela pega como par�metro o heap de onde os Vertices tem origem
E os dois Vertices que ela deve alterar*/
void inverter (HeapBinario* heap, int v1, int v2){
    if (v1 <= 0){
        printf("Valor de v1 , %d,muito baixo!\n", v1);
        return;
    }
    if (v1 > heap->maxElementos){
        printf("Valor de v1 , %d,muito alto!\n", v1);
        return;
    }
    if (v2 <= 0){
        printf("Valor de v2 , %d,muito baixo!\n", v2);
        return;
    }
    if (v2 > heap->maxElementos){
        printf("Valor de v2 , %d,muito alto!\n", v2);
        return;
    }
    int aux2 = heap->mapa[v1];
    heap->mapa[v1] = heap->mapa[v2];
    heap->mapa[v2] = aux2;
    inverterNaArvore(heap, heap->mapa[v1], heap->mapa[v2]);
}

/* Essa fun��o modifica o valor de algum elemento na �rvore do heap
E no mapa de indexa��o
E o realoca adequadamente nas estruturas
Ela pega como par�metro o heap de onde o V�rtice tem origem
O v�rtice que dever� ser alterado e o valor que ele assumir�*/
void alteraElemento (HeapBinario* heap, int elementoAlterado, int valor){
    if (valor < 0){
        printf("Novo valor muito baixo!\n");
        return;
    }
    if (elementoAlterado <= 0){
        printf("Elemento alterado muito baixo!\n");
        return;
    }
    if (elementoAlterado > heap->maxElementos){
        printf("Elemento alterado muito alto!\n");
        return;
    }
    if (heap->mapa[elementoAlterado] > heap->numElementos){
        printf("Elemento j� foi alterado!\n");
        return;
    }
    int indice = heap->mapa[elementoAlterado];
    heap->arvore[indice].distancia = valor;
    int indicePai;
    while(true){
        indicePai = (indice - (indice%2))/2; /*Essa equa��o faz com que, a partir do �ndice atual
                                             Eu possa encontrar o �ndice do n� pai*/
        if (indice <= 1 ||
            heap->arvore[indice].distancia >= heap->arvore[indicePai].distancia){/*Verifica��o se ou o n� � raiz
                                                                            ou se � menor/igual ao pai*/
            break;
        }
        inverter(heap, heap->arvore[indice].mapaDeRetorno, heap->arvore[indicePai].mapaDeRetorno);
        indice = indicePai;
    }
}

/* Essa fun��o inicializa o heap e define o v�rtice origem como tendo dist�ncia 0
Ela pega como par�metros o heap onde os dados ser�o colocados,
Al�m do n�mero de v�rtice alocados e o v�rtice origem do percurso*/
bool buildHeap (HeapBinario* heap, int nn, int verticeS){
    if (nn <= 0){
        printf("Quantidade de n�s muito baixa!\n");
        return false;
    }
    if (verticeS <= 0){
        printf("Valor do vertice origem muito baixo!\n");
        return false;
    }
    if (verticeS > nn){
        printf("Valor do vertice origem muito alto!\n");
        return false;
    }
    NO* novaArvore = (NO*)calloc(nn+1, sizeof(NO));
    int* novoMapa = (int*)calloc(nn+1, sizeof(int));
    heap->arvore = novaArvore;
    heap->mapa = novoMapa;
    heap->numElementos = nn;
    heap->maxElementos = nn;
    int i;
    for (i = 1; i <= nn; i++){
        heap->arvore[i].distancia = INFINITY;
        heap->arvore[i].mapaDeRetorno = i;
        heap->mapa[i] = i;
    }
    alteraElemento(heap, verticeS, 0);
    return true;
}

/* Essa fun��o reorganiza o heap depois que a raiz recebe um pop
Ela pega como par�metros somente o heap cuja raiz recebeu o pop*/
void heapify (HeapBinario* heap){
    int indice = 1;
    int indiceFilho;
    while (true){
        if (indice >= heap->numElementos)
            break;
        indiceFilho = 2*indice;
        if (indiceFilho > heap->numElementos)
            break;
        if (indiceFilho+1 <= heap->numElementos
                && heap->arvore[indiceFilho].distancia > heap->arvore[indiceFilho+1].distancia)
            indiceFilho++;
        if (heap->arvore[indice].distancia <= heap->arvore[indiceFilho].distancia)
            break;
        inverter(heap, heap->arvore[indice].mapaDeRetorno, heap->arvore[indiceFilho].mapaDeRetorno);
        indice = indiceFilho;
    }
}

/* Essa fun��o retorna o valor e exclui o elemento de maior prioridade no heap (pop)
Ela pega como par�metro o heap cuja raiz receber� o pop*/
int popElementoPrioritario (HeapBinario* heap){
    if (heap->numElementos <= 0){
        printf("N�o h� mais elementos nesse Heap!\n");
        return false;
    }
    if (heap->numElementos == 1){
        heap->numElementos = heap->numElementos-1;
        return heap->arvore[1].mapaDeRetorno;
    }
    inverter(heap, heap->arvore[1].mapaDeRetorno, heap->arvore[heap->numElementos].mapaDeRetorno);
    heap->numElementos = heap->numElementos-1;
    heapify(heap);
    return heap->arvore[heap->numElementos+1].mapaDeRetorno;
}

/* Essa fun��o retorna a dist�ncia de um v�rtice espec�fico da raiz
Ela pega como par�metros o heap de onde o v�rtice tem origem e o v�rtice*/
int retornaDistancia(HeapBinario* heap, int vertice){
    if (vertice <= 0){
        printf("Valor do vertice , %d,muito baixo!\n", vertice);
        return -1;
    }
    if (vertice > heap->maxElementos){
        printf("Valor do vertice , %d,muito alto!\n", vertice);
        return -1;
    }
    return heap->arvore[heap->mapa[vertice]].distancia;
}

//TESTE
/*void printaHeap (HeapBinario* heap){
    int i;
    for (i = 1; i <= heap->numElementos; i++){
        printf("%d : %d\n", heap->arvore[i].mapaDeRetorno, heap->arvore[i].distancia);
    }
}

int main(){
    HeapBinario heap;
    buildHeap(&heap, 10, 5);
    printaHeap(&heap);
    alteraElemento(&heap, 6, 1);
    printaHeap(&heap);
    alteraElemento(&heap, 7, 7);
    printaHeap(&heap);
    alteraElemento(&heap, 10, 7);
    printaHeap(&heap);
    alteraElemento(&heap, 1, 3);
    printaHeap(&heap);
    alteraElemento(&heap, 3, 8);
    printaHeap(&heap);
    alteraElemento(&heap, 9, 5);
    printaHeap(&heap);
    alteraElemento(&heap, 2, 9);
    printaHeap(&heap);
    alteraElemento(&heap, 4, 17);
    printaHeap(&heap);
    alteraElemento(&heap, 8, 7);
    printaHeap(&heap);
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    printf("Numero: %d\n", popElementoPrioritario(&heap));
    return 1;
}*/
