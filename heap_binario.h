#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Implementa��o usando vetores

typedef struct {
    double distancia;/* Representa a dist�ncia de um v�rtice em rela��o ao S*/
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
void inverterNaArvore (HeapBinario* heap, int v1, int v2);

/* Essa fun��o inverte dois v�rtices na estrutura do mapa de indexa��o
Ela pega como par�metro o heap de onde os Vertices tem origem
E os dois Vertices que ela deve alterar*/
void inverter (HeapBinario* heap, int v1, int v2);

/* Essa fun��o modifica o valor de algum elemento na �rvore do heap
E no mapa de indexa��o
E o realoca adequadamente nas estruturas
Ela pega como par�metro o heap de onde o V�rtice tem origem
O v�rtice que dever� ser alterado e o valor que ele assumir�*/
void alteraElemento (HeapBinario* heap, int elementoAlterado, int valor);

/* Essa fun��o inicializa o heap e define o v�rtice origem como tendo dist�ncia 0
Ela pega como par�metros o heap onde os dados ser�o colocados,
Al�m do n�mero de v�rtice alocados e o v�rtice origem do percurso*/
bool buildHeap (HeapBinario* heap, int nn, int verticeS);

/* Essa fun��o reorganiza o heap depois que a raiz recebe um pop
Ela pega como par�metros somente o heap cuja raiz recebeu o pop*/
void heapify (HeapBinario* heap);

/* Essa fun��o retorna verdadeiro caso o heap ainda possua elementos*/
bool possuiElementos (HeapBinario* heap);

/* Essa fun��o retorna o valor e exclui o elemento de maior prioridade no heap (pop)
Ela pega como par�metro o heap cuja raiz receber� o pop*/
int popElementoPrioritario (HeapBinario* heap);

/* Essa fun��o retorna a dist�ncia de um v�rtice espec�fico da raiz
Ela pega como par�metros o heap de onde o v�rtice tem origem e o v�rtice*/
double retornaDistancia(HeapBinario* heap, int vertice);
