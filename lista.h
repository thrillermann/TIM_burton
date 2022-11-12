#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "equipos.h"

struct nodi {
    Equipo seleccion;
    struct nodi *ps;
};

typedef struct nodi NODO;

typedef struct {
    NODO *acc;
    NODO *cur;
    NODO *curaux;
} LISTA;


void init (LISTA *listona) {
    (*listona).acc=NULL;
    (*listona).cur=NULL;
    (*listona).curaux=NULL;
}

void insertar (LISTA *listona, Equipo equi) {
    NODO* nodito=(NODO*)malloc(sizeof(NODO));

    nodito->seleccion=equi;

    if ((*listona).acc==(*listona).cur) {
        (*nodito).ps=(*listona).cur;
        (*listona).acc=nodito;
        (*listona).cur=nodito;
        (*listona).curaux=(*listona).cur;
    } else {
        (*listona).curaux->ps=nodito;
        (*nodito).ps=(*listona).cur->ps;
        (*listona).cur=nodito;
    }
}

void suprimir (LISTA *listona) {
    if ((*listona).curaux==(*listona).cur) {
        if (!((*listona).acc==NULL)) {
            free((void*)(*listona).acc);
            (*listona).acc=NULL;
            (*listona).cur=NULL;
            (*listona).curaux=NULL;
        };
       } else {
            (*listona).curaux->ps=(*listona).cur;
            free((void*)(*listona).cur);
            (*listona).cur=(*listona).curaux->ps;
        }
    };

void reset (LISTA *listonaaa) {
    (*listonaaa).cur=(*listonaaa).acc;
    (*listonaaa).curaux=(*listonaaa).acc;
}

void avanzar (LISTA *listona) {
    (*listona).curaux=(*listona).cur;
    (*listona).cur=(*listona).cur->ps;
}

int fuera (LISTA listinha) {
    if (listinha.cur==NULL) {
        return 1;
    } else {
        return 0;
    }

}

Equipo muestro (LISTA nanai) {
    return nanai.cur->seleccion;
}


int is_full (void) {
    Equipo *aux;
    aux=(Equipo*)malloc(sizeof(Equipo));
    if (aux==NULL) return 1;
    else return 0;
}

int is_empty(LISTA lista_ing){
    if (lista_ing.cur == NULL) return 1;
    else return 0;
}

#endif // LISTA_EQUIPO_H_INCLUDED
