#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "malloc.h"
#include "equipos.h"

typedef struct nod{
    Equipo seleccion;
    struct nod *ps;
    struct nod *ant;
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
    if (lista_ing.acc == NULL) return 1;
    else return 0;
}

int insertar(LISTA *lista_ing, Equipo equipo_ing) {
    if((NODO*)malloc(sizeof(NODO))==NULL){
        return 0;
    }
    else{
        NODO *aux1, *aux2;
        NODO *nuevo_nodo=(NODO*)malloc(sizeof(NODO));

        nuevo_nodo->seleccion = equipo_ing;
        nuevo_nodo->ps = NULL;
        nuevo_nodo->ant = NULL;

        if (is_empty(*lista_ing)==1) {
            lista_ing->acc = nuevo_nodo;
            lista_ing->cur = nuevo_nodo;
            lista_ing->curaux = NULL;
        } 
        else {
            lista_ing->cur->ps=nuevo_nodo;
            nuevo_nodo->ant = lista_ing->cur;

            aux1 = lista_ing->cur->ps;
            aux2 = lista_ing->cur;

            lista_ing->cur = aux1;
            lista_ing->curaux = aux2;
        }
        return 1;
    }
    
}

int suprimir (LISTA *lista_ing) {
    if (is_empty(*lista_ing)==1) {
        return 0;
    }  
    else {
        NODO *aux1, *aux2;

        aux1 = lista_ing->curaux;
        aux2 = lista_ing->curaux->ant;

        free((void*)(lista_ing->cur));

        lista_ing->cur = aux1;
        lista_ing->curaux = aux2;
        return 1;
    }
}

void reset (LISTA *lista_ing) {
    lista_ing->cur = lista_ing->acc;
    lista_ing->curaux = lista_ing->acc;
}

void avanzar (LISTA *lista_ing) {
    lista_ing->cur = lista_ing->cur->ps;
    lista_ing->curaux = lista_ing->curaux->ps;

}

int fuera (LISTA lista_ing) {
    if (lista_ing.cur==NULL) return 1;
    else return 0;
}







Equipo muestro (LISTA nanai) {
    return nanai.cur->seleccion;
}


int is_full (LISTA equinihno) {
	Equipo *aux;
	aux=(Equipo*)malloc(sizeof(Equipo));
	if (aux==NULL) {
	return 1;
	} else {
	return 0;
	}
}
#endif // LISTA_EQUIPO_H_INCLUDED

