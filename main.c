#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "equipos.h"

#define pais_nomb_max 100
#define dt_nomb_max 50
#define cap_nomb_max 50

int main(){
    LISTA conj_selecciones;
    char nombre_seleccion[pais_nomb_max];
    init(&conj_selecciones);

    cargar_datos(&conj_selecciones);
    /*
    
    
    */
    fflush(stdin);
    printf("\n Buscar selesion: ");
    fgets(nombre_seleccion, pais_nomb_max, stdin);

    buscar_pais_en_lista(conj_selecciones, nombre_seleccion);
    modificar_pts_y_partJGE(&conj_selecciones);
    print_seleccion(conj_selecciones, nombre_seleccion);
    print_partidos_perdidos(conj_selecciones);
    printf("\n sape");
    return 1;

}



void cargar_datos(LISTA *conj_selecciones){ //* funcion a modificada*//
    Equipo equipo;
    init_equipo(&equipo);
    char pais_ing[pais_nomb_max], dt_ing[dt_nomb_max], capitan_ing[cap_nomb_max], grupo_ing;
    int puntaje_actual_ing, fase_ing, continuar=1, resp_check=0;
    while(continuar!=0){
        system("cls");
        fflush(stdin);
        printf("\n # # #   C A R G A R   S E L E C C I O N E S   # # #\n");

        printf("\n + Ingrese la seleccion que desea insertar: ");
        fgets(pais_ing, pais_nomb_max, stdin);

        if (1 != buscar_pais_en_lista(*conj_selecciones, pais_ing)){
            cargar_pais(&equipo, pais_ing);

            printf("\n + Apellido y nombre del dt: ");
            fgets(&dt_ing, dt_nomb_max, stdin);
            cargar_dt(&equipo, dt_ing);

            printf("\n + Apellido del capitan de equipo: ");
            scanf("%s", capitan_ing);
            cargar_capitan(&equipo, capitan_ing);

            printf("\n + Grupo correspondiente (A,B,C,D,E,F,G,H): ");
            getc(stdin);
            scanf("%c", &grupo_ing);
            while(grupo_ing<65 || grupo_ing>72){
                printf("\n\a # Respuesta invalida...");
                printf("\n + Grupo correspondiente (A,B,C,D,E,F,G,H): ");
                getc(stdin);
                scanf("%c", &grupo_ing);
            }
            cargar_grupo(&equipo, grupo_ing);

            printf("\n + Ingrese el puntaje actual del equipo en fase de grupos: ");
            resp_check = scanf("%d", &puntaje_actual_ing);
            while(puntaje_actual_ing<0 || puntaje_actual_ing>9 || 1 != resp_check){ //* 1 != resp_check es para denegar los caracteres*//
                fflush(stdin);
                printf("\n\a # Respuesta invalida...");
                printf("\n + Ingrese el puntaje actual del equipo en fase de grupos: ");
                resp_check = scanf("%d", &puntaje_actual_ing);
            }
            cargar_puntaje_actual(&equipo, puntaje_actual_ing);

            printf("\n + Fase actual de la seleccion: ");
            printf("\n\n\t (0) = Fase de grupos, (1) = 8avos de final, (2) = 4tos de final, (3) Semifinal, (4) = Final\n");
            printf("\n + Resp: ");
            resp_check = scanf("%d", &fase_ing);
            while (fase_ing<0 || fase_ing>4 || 1 != resp_check){
                fflush(stdin);
                printf("\n\a # Respuesta invalida...");
                printf("\n + Fase actual de la seleccion: ");
                printf("\n\n\t (0) = Fase de grupos, (1) = 8avos de final, (2) = 4tos de final, (3) Semifinal, (4) = Final\n");
                printf("\n + Resp: ");
                resp_check = scanf("%d", &fase_ing);
            }
            cargar_fase(&equipo, fase_ing);
    
            insertar(conj_selecciones, equipo);
        }
        else{
            printf("\n\a # Esta seleccion ya se encuentra dentro de la lista...");
        }
        system("cls");
        printf("\a # Desea ingresar otro equipo?\n\n\t(1) = si\t(0) = no");
        printf("\n\n + Resp: ");
        resp_check = scanf("%d", &continuar);
        while (continuar<0 || continuar>1 || 1 != resp_check){
                fflush(stdin);
                printf("\n\a # Respuesta invalida...");
                printf("\n\a # Desea ingresar otro equipo?\n\n\t(1) = si\t(0) = no");
                printf("\n\n + Resp: ");
                resp_check = scanf("%d", &continuar);
            }
    }
}

int buscar_pais_en_lista(LISTA conj_selecciones, char seleccion_buscada[]){ //* funcion b modificada*//
    reset(&conj_selecciones);

    while(fuera(conj_selecciones)!=1){
        if (0==strcmp(conj_selecciones.cur->seleccion.pais, seleccion_buscada))
            return 1;
        else{
            avanzar(&conj_selecciones);
        }
    }
    return 0;
}

int print_seleccion(LISTA lista_equipos, char selecc_buscada[]){ //* funcion c*//
    int i;
    reset(&lista_equipos);
    while(fuera(lista_equipos)!=1){
        if(0==strcmp(lista_equipos.cur->seleccion.pais, selecc_buscada)){
            system("cls");
            printf("\n # # #   R E S U L T A D O   # # #\n");
            printf("\n + Seleccion: %s", mostrar_pais(lista_equipos.cur->seleccion));
            printf("\n + DT: %s", mostrar_dt(lista_equipos.cur->seleccion));
            printf("\n + Capitan: %s", mostrar_capitan(lista_equipos.cur->seleccion));
            printf("\n + Grupo: %c", mostrar_grupo(lista_equipos.cur->seleccion));
            printf("\n + Puntaje Actual: %d", mostrar_puntaje_actual(lista_equipos.cur->seleccion));
            printf("\n + Goleador: %s, %d gol/es", mostrar_goleador_apellido(lista_equipos.cur->seleccion), mostrar_goleador_goles(lista_equipos.cur->seleccion));
            switch(lista_equipos.cur->seleccion.fase){
                case (0):{printf("\n + Fase Actual: Grupo"); break;}
                case (1):{printf("\n + Fase Actual: Octavos de final"); break;}
                case (2):{printf("\n + Fase Actual: Cuartos de final"); break;}
                case (3):{printf("\n + Fase Actual: Semifinal"); break;}
                case (4):{printf("\n + Fase Actual: Final");}
            }
            printf("\n + Resultados:");
            for (i=0; i<=lista_equipos.cur->seleccion.fase; ++i){
                switch (i){
                    case (0):{printf("\n\t + Fase de Grupos:");
                    printf("\n\t\t - Puntaje parcial: %d", mostrar_resultados_fase_punt_parcial(lista_equipos.cur->seleccion, i));
                    break;}
                    case (1):{printf("\n\t + Octavos de final"); break;}
                    case (2):{printf("\n\t + Cuartos de final"); break;}
                    case (3):{printf("\n\t + Semifinal"); break;}
                    case (4):{printf("\n\t + Final");}
                }
                printf("\n\t\t - Gol/es a favor: %d", mostrar_resultados_fase_gfav(lista_equipos.cur->seleccion, i));
                printf("\n\t\t - Gol/es en contra: %d\n", mostrar_resultados_fase_gcon(lista_equipos.cur->seleccion, i));
            }
            //FALTA USAR FUNCIONES EN FECHA DE ACTUALIZACION
            printf("\n + Fecha Actualizacion: %d-%d-%d", lista_equipos.cur->seleccion.fecha_actualizada.dia, lista_equipos.cur->seleccion.fecha_actualizada.mes, lista_equipos.cur->seleccion.fecha_actualizada.anio);
            printf("\n + Partidos Jugados: %d", mostrar_partidos_jugados(lista_equipos.cur->seleccion));
            printf("\n + Partidos Ganados: %d", mostrar_partidos_ganados(lista_equipos.cur->seleccion));
            printf("\n + Partidos Empatados: %d", mostrar_partidos_empatados(lista_equipos.cur->seleccion));
            reset(&lista_equipos);
            return 1;
        }
        else{
            avanzar(&lista_equipos);
        }
    }
    printf("\n - Pulse una tecla para volver al menu...");
    getchar();
    reset(&lista_equipos);
    return 0;
}

void print_selecciones_x_fase(LISTA conj_selecciones, int fase_ing){ /*funcion d*/
    int cant_de_selecciones_mostradas=0;
    reset(&conj_selecciones);
    system("cls");
    switch(fase_ing){
                case (0):{printf("\n\a # # #  F A S E  D E  G R U P O S  # # #\n"); break;}
                case (1):{printf("\n\a # # #   8 V O S   D E   F I N A L   # # #\n"); break;}
                case (2):{printf("\n\a # # #   4 T O S   D E   F I N A L  # # #\n"); break;}
                case (3):{printf("\n\a # # #   S E M I F I N A L   # # #\n"); break;}
                case (4):{printf("\n\a # # #   F I N A L   # # #\n");}
            }

    while(fuera(conj_selecciones)!=1){
        if(conj_selecciones.cur->seleccion.fase == fase_ing){
            printf("\n + %s", mostrar_pais(conj_selecciones.cur->seleccion));
            cant_de_selecciones_mostradas += 1;
        }
        avanzar(&conj_selecciones);
    }
    if(cant_de_selecciones_mostradas==0){
        printf("\n - No hay selecciones jugando la fase seleccionada...");
        
    }
    printf("\n - Pulse una tecla para volver al menu...");
    getchar();
    reset(&conj_selecciones);
}

void mostrar_goleadores_ord_x_pais(LISTA conj_selecciones){ /* funcion e...   A=65 - Z=90 y a=97 - z=122,   a-A=32*... le falta amor, no anda todavia...*/  
    int cant_goleadores=0, i;
    reset(&conj_selecciones);

    system("cls");
    printf("\n\a # # #   L I S T A   D E   G O L E A D O R E S   # # #\n");
    for (i=65; i<=90; ++i){
        while(fuera(conj_selecciones)!=1){
            if(conj_selecciones.cur->seleccion.pais[0] == i || conj_selecciones.cur->seleccion.pais[0] == (i+32)){
                if(conj_selecciones.cur->seleccion.goleador.goles>0){
                    printf("\n + %s, Gol/es: %d, %s", mostrar_goleador_apellido(conj_selecciones.cur->seleccion), mostrar_goleador_goles(conj_selecciones.cur->seleccion), mostrar_pais(conj_selecciones.cur->seleccion));
                    cant_goleadores+=1;
                }
            }
            avanzar(&conj_selecciones);
        }
    }
    if (cant_goleadores==0){
        printf("\n - No hay goleadores...");
    }
    fflush(stdin);
    printf("\n - Pulse una tecla para volver al menu...");
    getchar();

    reset(&conj_selecciones);
}

void mod_pts_y_partJGE(LISTA *conj_selecciones){ /*en la invocacion se le pasa la lista con el cursor con la seleccion que se busco*/
    int pts_fase_grupos, p_jugados, p_ganados, p_empatados, resp_check;
    system("cls");
    printf("\n # # #   M O D I F I C A R   P U N T O S   Y   P A R T I D O S   # # #\n");
    printf("\n # Pais: %s", mostrar_pais(conj_selecciones->cur->seleccion));
    printf("\n Datos actuales: ");
    printf("\n\t * Puntaje en fase de grupos: %d pto/s...", mostrar_puntaje_actual(conj_selecciones->cur->seleccion));
    printf("\n\t * Partidos Jugados: %d", mostrar_partidos_jugados(conj_selecciones->cur->seleccion));
    printf("\n\t * Partidos Ganados: %d", mostrar_partidos_ganados(conj_selecciones->cur->seleccion));
    printf("\n\t * Partidos Empatados: %d", mostrar_partidos_empatados(conj_selecciones->cur->seleccion));

    printf("\n\n - A continuacion ingrese los datos a reemplazar...");
    printf("\n\t + Puntaje en fase de grupos: ");
    resp_check = scanf("%d", &pts_fase_grupos);
    while(pts_fase_grupos<0 || pts_fase_grupos>9 || 1 != resp_check){ //* 1 != resp_check es para denegar los caracteres*//
        fflush(stdin);
        printf("\n\a # Respuesta invalida...");
        printf("\n\t + Puntaje en fase de grupos: ");
        resp_check = scanf("%d", &pts_fase_grupos);
    }
    cargar_puntaje_actual(&conj_selecciones->cur->seleccion, pts_fase_grupos);

    printf("\n\t + Partidos Jugados: ");
    resp_check = scanf("%d", &p_jugados);
    while(p_jugados<0 || p_jugados>7 || 1 != resp_check){
        fflush(stdin);
        printf("\n\a # Respuesta invalida");
        if(p_jugados>7 && 1 == resp_check){
            printf(", la cantidad de partidos jugados excede la cantidad de partidos en un mundial...");
        }
        if(1 != resp_check){
            printf("...");
        }
        
        printf("\n\t + Partidos Jugados: ");
        resp_check = scanf("%d", &p_jugados);
    }
    cargar_partidos_jugados(&conj_selecciones->cur->seleccion, p_jugados);

    printf("\n\t + Partidos Ganados: ");
    resp_check = scanf("%d", &p_ganados);
    while(p_ganados<0 || p_ganados>p_jugados || 1 != resp_check){
        fflush(stdin);
        printf("\n\a # Respuesta invalida");
        if(p_ganados>p_jugados && 1 == resp_check){
            printf(", la cantidad de partidos ganados es mayor a los partidos jugados...");
        }
        if(1 != resp_check){
            printf("...");
        }
        
        printf("\n\t + Partidos Ganados: ");
        resp_check = scanf("%d", &p_ganados);
    }
    cargar_partidos_ganados(&conj_selecciones->cur->seleccion, p_ganados);

    printf("\n\t + Partidos Empatados: ");
    resp_check = scanf("%d", &p_empatados);
    while( ((p_ganados==p_jugados)&&(p_empatados!=0)) || p_empatados<0 || p_empatados>p_jugados || 1 != resp_check){
        fflush(stdin);
        printf("\n\a # Respuesta invalida");
        if(p_empatados>p_jugados && 1 == resp_check){
            printf(", la cantidad de partidos empatados es mayor a los partidos jugados...");
        }
        if( ((p_ganados==p_jugados)&&(p_empatados!=0)) && 1 == resp_check){
            printf(", el equipo gano todos los partidos que jugo...");
        }
        if(1 != resp_check){
            printf("...");
        }
        printf("\n\t + Partidos Empatados: ");
        resp_check = scanf("%d", &p_empatados);
    }
    cargar_partidos_empatados(&conj_selecciones->cur->seleccion, p_empatados);

    system("cls");
    printf("\n # # #   M O D I F I C A R   P U N T O S   Y   P A R T I D O S   # # #\n");
    printf("\n\a # Datos modificados con exito, pulse para volver al menu...");
    fflush(stdin);
    getchar(); 
}

void mod_fase_y_estadisticas(LISTA conj_selecciones){ /*en la invocacion se le pasa la lista con el cursor con la seleccion que se busco*/

}

void print_partidos_perdidos(LISTA conj_selecciones){
    int partidos_perdidos=0;
    partidos_perdidos = (conj_selecciones.cur->seleccion.partidos_jugados)-((conj_selecciones.cur->seleccion.partidos_ganados)+(conj_selecciones.cur->seleccion.partidos_empatados));
    system("cls");
    printf("\n # # #   P A R T I D O S   P E R D I D O S   # # #\n");
    printf("\n # Pais: %s", mostrar_pais(conj_selecciones.cur->seleccion));
    printf("\n\t + Partidos perdidos: %d", partidos_perdidos);

    fflush(stdin);
    printf("\n\n - Pulse una tecla para volver al menu...");
    getchar();

}



