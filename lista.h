#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "malloc.h"
#include "equipos.h"

typedef struct nod{
    Equipo seleccion;
    struct nod *siguiente;
} NODO;

typedef struct {
    NODO *acc;
    NODO *cur;
    NODO *curaux;
} LISTA;

void init(LISTA *lista_ing) {
    lista_ing->acc=NULL;
    lista_ing->cur=NULL;
    lista_ing->curaux=NULL;
}

int is_empty(LISTA lista_ing){
    if (lista_ing.cur == lista_ing.curaux) return 1;
    else return 0;
}

int is_full (LISTA lista_ing) {
	Equipo *aux;
	aux=(Equipo*)malloc(sizeof(Equipo));
	if (aux==NULL) {
	return 1;
	} else {
	return 0;
	}
}

int insertar(LISTA *lista_ing, Equipo equipo_ing) {
    if((NODO*)malloc(sizeof(NODO))==NULL){
        return 0;
    }
    else{
        NODO *aux1;
        NODO *nuevo_nodo=(NODO*)malloc(sizeof(NODO));

        nuevo_nodo->seleccion = equipo_ing;
        nuevo_nodo->siguiente = NULL;

        if (is_empty(*lista_ing)==1) {
            lista_ing->acc = nuevo_nodo;
            lista_ing->cur = nuevo_nodo;
            lista_ing->curaux = nuevo_nodo;
        }
        else {
            aux1 = lista_ing->cur;

            lista_ing->cur->siguiente = nuevo_nodo;
            lista_ing->curaux->siguiente = aux1;

            lista_ing->cur = nuevo_nodo;
            lista_ing->curaux = aux1;

        }
        return 1;
    }

}

int suprimir (LISTA *lista_ing) {
    if (is_empty(*lista_ing)==1) {
        return 0;
    }
    else {
        NODO *aux1;
        aux1 = lista_ing->cur->siguiente;
        
        lista_ing->curaux->siguiente = aux1;

        free((void*)(lista_ing->cur));

        lista_ing->cur = aux1;

        return 1;
    }
}

void reset (LISTA *lista_ing) {
    lista_ing->cur = lista_ing->acc;
    lista_ing->curaux = lista_ing->acc;
}

void avanzar (LISTA *lista_ing) {
    NODO *aux1, *aux2;
    aux1 = lista_ing->cur;
    aux2 = lista_ing->cur->siguiente;

    lista_ing->curaux = aux1;
    lista_ing->cur = aux2;
}

int fuera (LISTA lista_ing) {
    if (lista_ing.cur==NULL) return 1;
    else return 0;
}

Equipo muestro (LISTA lista_ing) {
    return lista_ing.cur->seleccion;
}

#endif // LISTA_EQUIPO_H_INCLUDED

