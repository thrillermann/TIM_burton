#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "equipos.h"

#define pais_nomb_max 100
#define dt_nomb_max 50
#define cap_nomb_max 50

int main(){
    LISTA conj_selecciones; 
    init(&conj_selecciones);
    int fase=0; int resp; int salir=0;
    char pais_ing[pais_nomb_max];

    while (salir!=1){
        system("cls");
        printf("\n # # #  M E N U  # # #\n");
        printf("\n(1) Cargar paises");
        printf("\n(2) Modificar puntaje y cant partidos ganados/empatados pais");
        printf("\n(3) Borrar seleccion");
        printf("\n(4) Actualizar fase y actualizar la anterior pais");
        printf("\n(5) Buscar y mostrar datos de un pais");
        printf("\n(6) Mostrar todas las selecciones ordenadas por puntaje");
        printf("\n(7) Mostrar listado de actualizaciones de paises");
        printf("\n(8) Mostrar selecciones por fase");
        printf("\n(9) Mostrar goleadores por orden alfabetico");
        printf("\n(10) Mostrar goleadores por cantidad de goles");
        printf("\n(11) Exportar resultados de fase de una seleccion");
        printf("\n(12) Importar seleccion");
        printf("\n(13) Salir");
        printf("\n - Resp: ");
        scanf("%d", &resp);

        switch(resp){
            case (1):{
                cargar_datos(&conj_selecciones); 
                break;
            }
            case (2):{
                printf("\n en mantenimiento..."); break;
            }
            case (3):{
                printf("\n Ingrese el nombre de la seleccion: ");
                fflush(stdin);
                scanf("%[^\n]s", pais_ing);
                if (buscar_pais_en_lista(&conj_selecciones, pais_ing)!=1){
                    printf("\n no se encontro...");
                    printf("\n Pulse para volver al menu...");
                    fflush(stdin);
                    getchar();
                }
                else{
                    borrar_seleccion(&conj_selecciones); 
                }
                break;
            }
            case (4):{
                printf("\n Ingrese el nombre de la seleccion: ");
                fflush(stdin);
                scanf("%[^\n]s", pais_ing);
                if (buscar_pais_en_lista(&conj_selecciones, pais_ing)!=1){
                    printf("\n no se encontro...");
                    printf("\n Pulse para volver al menu...");
                    fflush(stdin);
                    getchar();
                }
                else{
                    mod_fase_y_estadisticas(&conj_selecciones);
                }
                break;
            }
            case (5):{
                printf("\n Ingrese el nombre de la seleccion: ");
                fflush(stdin);
                scanf("%[^\n]s", pais_ing);
                if (buscar_pais_en_lista(&conj_selecciones, pais_ing)!=1){
                    printf("\n no se encontro...");
                }
                else{
                    print_seleccion(conj_selecciones);
                }
                printf("\n Pulse para volver al menu...");
                fflush(stdin);
                getchar();
                
                break;
            }
            case (6):{
                fflush(stdin);
                printf("\n # # #   S E L E C C I O N E S   C O N   M A Y O R   P U N T A J E   # # #\n");
                print_selecciones_ord_x_ptos(conj_selecciones, 9); /*El mayor puntaje que se puede obtener es 9 ptos, ya que solo hay 3 partidos que tienen puntaje...*/
                printf("\n Pulse para volver al menu...");
                fflush(stdin);
                getchar();
                break;
            }
            case (7):{
                printf("\n en mantenimiento..."); break;
            }
            case (8):{
                printf("\n Ingrese la fase: ");
                scanf("%d", &fase);
                print_selecciones_x_fase(conj_selecciones, fase); 
                break;
            }
            case (9):{
                mostrar_goleadores_ord_x_pais(conj_selecciones); break;
            }
            case (10):{
                mostrar_goleadores_ord_x_goles(&conj_selecciones); break;
            }
            case (11):{
                printf("\n Ingrese el nombre de la seleccion: ");
                fflush(stdin);
                scanf("%[^\n]s", pais_ing);
                if (buscar_pais_en_lista(&conj_selecciones, pais_ing)!=1){
                    printf("\n no se encontro...");
                    printf("\n Pulse para volver al menu...");
                    fflush(stdin);
                    getchar();
                }
                else{
                    exportar_resultados_fase(conj_selecciones);
                }
                break;
            }
            case (12):{
                importar_seleccion(&conj_selecciones); break;
            }
            case (13):{
                exit(1);
            }
        }
    }
}

int buscar_pais_en_lista(LISTA *conj_selecciones, char seleccion_buscada[]){ //* funcion b modificada*//
    reset(conj_selecciones);
    while(fuera(*conj_selecciones)!=1){
        if (strcmp((mostrar_pais(conj_selecciones->cur->seleccion)), seleccion_buscada)==0){
            return 1;
        }
        else{
            avanzar(conj_selecciones);
        }
    }
    return 0;
}

void cargar_datos(LISTA *conj_selecciones){ //* funcion a modificada*//
    Equipo equipo;
    init_equipo(&equipo);
    char pais_ing[pais_nomb_max], dt_ing[dt_nomb_max], capitan_ing[cap_nomb_max], grupo_ing;
    int puntaje_actual_ing, fase_ing, continuar=1, resp_check=0, success;
    while(continuar!=0){
        system("cls");
        printf("\n # # #   C A R G A R   S E L E C C I O N E S   # # #\n");

        printf("\n + Ingrese la seleccion que desea insertar: ");
        fflush(stdin);
        scanf("%[^\n]s", pais_ing);
        cargar_pais(&equipo, pais_ing);

        printf("\n + Apellido y nombre del dt: ");
        fflush(stdin);
        scanf("%[^\n]s", dt_ing);
        cargar_dt(&equipo, dt_ing);

        printf("\n + Apellido del capitan de equipo: ");
        fflush(stdin);
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

        printf("\n + Ingrese el puntaje actual del equipo: ");
        resp_check = scanf("%d", &puntaje_actual_ing);
        while(puntaje_actual_ing<0 || puntaje_actual_ing>9 || 1 != resp_check){ //* 1 != resp_check es para denegar los caracteres*//
            fflush(stdin);
            printf("\n\a # Respuesta invalida...");
            printf("\n + Ingrese el puntaje actual del equipo: ");
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

void print_seleccion(LISTA lista_equipos){ //* funcion c*//
    int i; int partidos_perdidos=0;
    partidos_perdidos = (lista_equipos.cur->seleccion.partidos_jugados)-((lista_equipos.cur->seleccion.partidos_ganados)+(lista_equipos.cur->seleccion.partidos_empatados)); 

    system("cls");
    printf("\n # # #   R E S U L T A D O   # # #\n");
    printf("\n + Seleccion: %s", lista_equipos.cur->seleccion.pais);
    printf("\n + DT: %s", lista_equipos.cur->seleccion.dt);
    printf("\n + Capitan: %s", lista_equipos.cur->seleccion.capitan);
    printf("\n + Grupo: %c", lista_equipos.cur->seleccion.grupo);
    printf("\n + Puntaje Actual: %d", lista_equipos.cur->seleccion.puntaje_actual);
    printf("\n + Goleador: %s, %d gol/es", lista_equipos.cur->seleccion.goleador.apellido, lista_equipos.cur->seleccion.goleador.goles);
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
            printf("\n\t\t - Puntaje parcial: %d pto/s", lista_equipos.cur->seleccion.resultados_fase[i].puntaje_parcial);
            break;}
            case (1):{printf("\n\t + Octavos de final"); break;}
            case (2):{printf("\n\t + Cuartos de final"); break;}
            case (3):{printf("\n\t + Semifinal"); break;}
            case (4):{printf("\n\t + Final");}
        }
        printf("\n\t\t - Gol/es a favor: %d", lista_equipos.cur->seleccion.resultados_fase[i].goles_favor);
        printf("\n\t\t - Gol/es en contra: %d\n", lista_equipos.cur->seleccion.resultados_fase[i].goles_contra);
    }
    printf("\n + Fecha Actualizacion: %d-%d-%d", lista_equipos.cur->seleccion.fecha_actualizada.dia, lista_equipos.cur->seleccion.fecha_actualizada.mes, lista_equipos.cur->seleccion.fecha_actualizada.anio);
    printf("\n + Partidos Jugados: %d", lista_equipos.cur->seleccion.partidos_jugados);
    printf("\n + Partidos Ganados: %d", lista_equipos.cur->seleccion.partidos_ganados);
    printf("\n + Partidos Empatados: %d", lista_equipos.cur->seleccion.partidos_empatados);
    printf("\n + Partidos Perdidos: %d", partidos_perdidos);

    reset(&lista_equipos);
}

void print_selecciones_ord_x_ptos(LISTA conj_selecciones, int pts_max){
    if(fuera(conj_selecciones)!=1){
        if(mostrar_puntaje_actual(conj_selecciones.cur->seleccion)==pts_max){
            printf("\n + Pais: %s, %d pto/s", mostrar_pais(conj_selecciones.cur->seleccion), mostrar_puntaje_actual(conj_selecciones.cur->seleccion));
        }
        avanzar(&conj_selecciones);
        print_selecciones_ord_x_ptos(conj_selecciones, pts_max);
    }
    else{
        reset(&conj_selecciones);
        print_selecciones_ord_x_ptos(conj_selecciones, pts_max-1);
    }
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
    fflush(stdin);
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

void mostrar_goleadores_ord_x_goles(LISTA *conj_selecciones){
    int max_goles=0;
    reset(conj_selecciones);
    printf("\n 1er control");

    while(conj_selecciones->cur->ps != NULL){
        if ((conj_selecciones->cur->seleccion.goleador.goles) >= (max_goles)){
            max_goles = conj_selecciones->cur->seleccion.goleador.goles;
        }
    }

    printf("\n sapee");
}

void mod_pts_y_partJGE(LISTA *conj_selecciones){ /*funcion g... en la invocacion se le pasa la lista con el cursor con la seleccion que se busco*/
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
    modificar_puntaje_actual(&conj_selecciones->cur->seleccion, pts_fase_grupos);

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
    modificar_partidos_jugados(&conj_selecciones->cur->seleccion, p_jugados);

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
    modificar_partidos_ganados(&conj_selecciones->cur->seleccion, p_ganados);

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
    modificar_partidos_empatados(&conj_selecciones->cur->seleccion, p_empatados);

    system("cls");
    printf("\n # # #   M O D I F I C A R   P U N T O S   Y   P A R T I D O S   # # #\n");
    printf("\n\a # Datos modificados con exito, pulse para volver al menu...");
    fflush(stdin);
    getchar(); 
}

void mod_fase_y_estadisticas(LISTA *conj_selecciones){ /*funcion i, en la invocacion se le pasa la lista con el cursor con la seleccion que se busco*/
    int datos_ing, cant_fases_avanzadas, p_jugados, p_ganados, p_empatados, resp_check;
    system("cls");
    printf("\n # # #   M O D I F I C A C I O N  D E  F A S E   # # #\n");
    printf("\n # Pais: %s", mostrar_pais(conj_selecciones->cur->seleccion));
    printf("\n\t * Fase actual: ");
    switch(conj_selecciones->cur->seleccion.fase){
        case (0):{printf("Fase de grupos\n"); break;}
        case (1):{printf("8vos de final\n"); break;}
        case (2):{printf("4tos de final\n"); break;}
        case (3):{printf("Semifinal\n"); break;}
        case (4):{printf("Final\n");}
    }
    printf("\n\t - Estadisticas guardadas de la Fase en cuestion: ");
    if (conj_selecciones->cur->seleccion.fase==0) {printf("\n\t\t * Puntaje parcial: %d", mostrar_resultados_fase_punt_parcial(conj_selecciones->cur->seleccion, 0));}
    printf("\n\t\t * Gol/es a favor: %d", mostrar_resultados_fase_gfav(conj_selecciones->cur->seleccion, conj_selecciones->cur->seleccion.fase));
    printf("\n\t\t * Gol/es en contra: %d\n", mostrar_resultados_fase_gcon(conj_selecciones->cur->seleccion, conj_selecciones->cur->seleccion.fase));
    printf("\n\t\t * Partidos jugados: %d\n", mostrar_partidos_jugados(conj_selecciones->cur->seleccion));
    
    printf("\n - A continuacion actualice los datos de la fase... ");
    if (conj_selecciones->cur->seleccion.fase==0){
        
        printf("\n + Ingrese puntaje parcial: ");
        resp_check = scanf("%d", &datos_ing);
        while (datos_ing<0 || datos_ing>9 || resp_check!=1){
            fflush(stdin);
            printf("\n\a # Respuesta invalida...");
            printf("\n + Ingrese puntaje parcial: ");
            resp_check = scanf("%d", &datos_ing);
        }
        modificar_puntaje_actual(&conj_selecciones->cur->seleccion, datos_ing);  
    }

    
    printf("\n + Partidos Jugados (desde el comienzo de la copa): ");
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
    
    printf("\n + Partidos Jugados: ");
    resp_check = scanf("%d", &p_jugados);
    }
    modificar_partidos_jugados(&conj_selecciones->cur->seleccion, p_jugados);

    printf("\n + Partidos Ganados: ");
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
        
        printf("\n + Partidos Ganados: ");
        resp_check = scanf("%d", &p_ganados);
    }
    modificar_partidos_ganados(&conj_selecciones->cur->seleccion, p_ganados);

    printf("\n + Partidos Empatados: ");
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
        printf("\n + Partidos Empatados: ");
        resp_check = scanf("%d", &p_empatados);
    }
    modificar_partidos_empatados(&conj_selecciones->cur->seleccion, p_empatados);

    printf("\n + Ingrese los goles a favor (de la fase en cuestion): ");
    resp_check = scanf("%d", &datos_ing);
    while (datos_ing<0 || resp_check!=1){
        fflush(stdin);
        printf("\n\a # Respuesta invalida...");
        printf("\n + Ingrese los goles en favor: ");
        resp_check = scanf("%d", &datos_ing);
    }
    modificar_resultados_fase_GF(&conj_selecciones->cur->seleccion, conj_selecciones->cur->seleccion.fase, datos_ing);

    printf("\n + Ingrese los goles en contra (de la fase en cuestion): ");
    resp_check = scanf("%d", &datos_ing);
    while (datos_ing<0 || resp_check!=1){
        fflush(stdin);
        printf("\n\a # Respuesta invalida...");
        printf("\n + Ingrese los goles en contra: ");
        resp_check = scanf("%d", &datos_ing);
    }
    modificar_resultados_fase_GC(&conj_selecciones->cur->seleccion, conj_selecciones->cur->seleccion.fase, datos_ing);

    printf("\n - Seleccione la fase a la que el equipo accedio: ");
    printf("\n\n\t (0) = Fase de grupos, (1) = 8avos de final, (2) = 4tos de final, (3) Semifinal, (4) = Final\n");
    printf("\n   + Resp: ");
    resp_check = scanf("%d", &datos_ing);
    while (datos_ing<0 || datos_ing>4 || 1 != resp_check){
        fflush(stdin);
        printf("\n\a # Respuesta invalida...");
        printf("\n - Seleccione la fase a la que el equipo accedio: ");
        printf("\n\n\t (0) = Fase de grupos, (1) = 8avos de final, (2) = 4tos de final, (3) Semifinal, (4) = Final\n");
        printf("\n   + Resp: ");
        resp_check = scanf("%d", &datos_ing);
    }

    if (conj_selecciones->cur->seleccion.fase>0){
        modificar_resultados_fase_ptj(&conj_selecciones->cur->seleccion, conj_selecciones->cur->seleccion.fase, 1); /* Si el equipo no esta en fase de grupos, y actualizamos su fase, quiere decir que que gano y avanzo*/
    }

    cant_fases_avanzadas = datos_ing - conj_selecciones->cur->seleccion.fase;

    if (cant_fases_avanzadas>1){
        printf("\n\a # Advertencia: se ha saltado mas 1 fase, por lo tanto quedaron vacias...");
    }

    modificar_fase(&conj_selecciones->cur->seleccion, datos_ing);

    printf("\n\a # Datos modificados con exito, pulse para volver al menu...");
    fflush(stdin);
    getchar(); 
}

void importar_seleccion(LISTA *conj_selecciones){ /*funcion m*/
    FILE *seleccion_importada;
    char nomb_del_archivo[pais_nomb_max];

    system("cls");
    printf("\n # # #   I M P O R T A R   S E L E C C I O N   # # #\n");
    
    printf("\n - Introduzca el nombre completo del archivo (ej: ARCHIVO_DE_EJEMPLO.txt)");
    printf("\n    * Puede introducir \"ayuda\" para ver mas informacion... ");
    
    printf("\n\n - Resp: ");
    scanf("%s", nomb_del_archivo);    
    if (strcmp(nomb_del_archivo, "ayuda")==0){
        system("cls");
        printf("\n\a # # #   A Y U D A   # # #\n");
        printf("\n * Coloque el archivo en dentro de la carpeta del programa...\n");
        printf("\n * El nombre del archivo no debe contener ningun espacio...\n");
        printf("\n * El archivo de tener el siguiente formato:");
        printf("\n    NOMBRE_DE_LA_SELECCION");
        printf("\n    NOMBRE_DEL_DT APELLIDO_DEL_DT");
        printf("\n    APELLIDO_DEL_CAPITAN");
        printf("\n    PUNTAJE_FASE_GRUPOS");
        printf("\n\n - Introduzca el nombre completo del archivo (ej: ARCHIVO_DE_EJEMPLO.txt)");
        printf("\n\n - Resp: ");
        scanf("%s", nomb_del_archivo);
    }

    if (fopen(nomb_del_archivo, "r")==NULL){
        printf("\n\a # No se encontro el archivo...");
    }
    else{
        Equipo nueva_seleccion;
        init_equipo(&nueva_seleccion);
        seleccion_importada = fopen(nomb_del_archivo, "r");

        char pais_ing[pais_nomb_max], dt_nomb_ing[dt_nomb_max], dt_ape_ing[dt_nomb_max], capitan_ing[cap_nomb_max];
        int puntaje_ing;
        
        fscanf(seleccion_importada, "%s %s %s %s %d", pais_ing, dt_nomb_ing, dt_ape_ing, capitan_ing, &puntaje_ing);

        strcat(dt_nomb_ing, " ");
        strcat(dt_nomb_ing, dt_ape_ing);

        cargar_pais(&nueva_seleccion, pais_ing);
        cargar_dt(&nueva_seleccion, dt_nomb_ing);
        cargar_capitan(&nueva_seleccion, capitan_ing);
        cargar_puntaje_actual(&nueva_seleccion, puntaje_ing);

        insertar(conj_selecciones, nueva_seleccion);
        system("cls");
        printf("\n # # #   I M P O R T A R   S E L E C C I O N   # # #\n");
        printf("\n - Desde: %s", nomb_del_archivo);
        printf("\n\a # Datos Importados: ");
        printf("\n\t * Pais: %s", mostrar_pais(conj_selecciones->cur->seleccion));
        printf("\n\t * DT: %s", mostrar_dt(conj_selecciones->cur->seleccion));
        printf("\n\t * Capitan: %s", mostrar_capitan(conj_selecciones->cur->seleccion));
        printf("\n\t * Puntaje fase de grupos: %d pto/s", mostrar_puntaje_actual(conj_selecciones->cur->seleccion));
        fclose(seleccion_importada);
    }
    printf("\n\n - Pulse una tecla para volver al menu...");
    fflush(stdin);
    getchar();
}

void exportar_resultados_fase(LISTA conj_selecciones){
    FILE *seleccion_resultados_export;
    char nombre_del_archivo[pais_nomb_max];
    int i;

    strcpy(nombre_del_archivo, mostrar_pais(conj_selecciones.cur->seleccion));
    strcat(nombre_del_archivo,"_RESULTADOS_EXPORT.txt");

    system("cls");
    printf("\n # # #   E X P O R T A R   R E S U L T A D O S   D E   F A S E   # # #\n");

    seleccion_resultados_export = fopen(nombre_del_archivo, "w");
    for (i=0; i<=mostrar_fase(conj_selecciones.cur->seleccion); ++i){
        switch(i){
            case (0):{
                fprintf(seleccion_resultados_export, " * Fase: Grupos, ");
                fprintf(seleccion_resultados_export, "Pto/s: %d ", mostrar_puntaje_actual(conj_selecciones.cur->seleccion));
                fprintf(seleccion_resultados_export, "GF: %d, ", mostrar_resultados_fase_gfav(conj_selecciones.cur->seleccion, i));
                fprintf(seleccion_resultados_export, "GC: %d\n", mostrar_resultados_fase_gcon(conj_selecciones.cur->seleccion, i));
                break;
            }
            case (1):{
                fprintf(seleccion_resultados_export, " * Fase: 8avos, ");
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==1){
                    fprintf(seleccion_resultados_export, "Resultado: Gano, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==0){ 
                    fprintf(seleccion_resultados_export, "Resultado: Perdio, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==2){ 
                    fprintf(seleccion_resultados_export, "Resultado: Pendiente, ");
                }
                
                fprintf(seleccion_resultados_export, "GF: %d, ", mostrar_resultados_fase_gfav(conj_selecciones.cur->seleccion, i));
                fprintf(seleccion_resultados_export, "GC: %d\n", mostrar_resultados_fase_gcon(conj_selecciones.cur->seleccion, i));
                break;
            }
            case (2):{
                fprintf(seleccion_resultados_export, " * Fase: 4tos, ");
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==1){
                    fprintf(seleccion_resultados_export, "Resultado: Gano, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==0){ 
                    fprintf(seleccion_resultados_export, "Resultado: Perdio, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==2){ 
                    fprintf(seleccion_resultados_export, "Resultado: Pendiente, ");
                }

                fprintf(seleccion_resultados_export, "GF: %d, ", mostrar_resultados_fase_gfav(conj_selecciones.cur->seleccion, i));
                fprintf(seleccion_resultados_export, "GC: %d\n", mostrar_resultados_fase_gcon(conj_selecciones.cur->seleccion, i));
                break;
            }
            case (3):{
                fprintf(seleccion_resultados_export, " * Fase: Semifinal, ");
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==1){
                    fprintf(seleccion_resultados_export, "Resultado: Gano, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==0){ 
                    fprintf(seleccion_resultados_export, "Resultado: Perdio, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==2){ 
                    fprintf(seleccion_resultados_export, "Resultado: Pendiente, ");
                }

                fprintf(seleccion_resultados_export, "GF: %d, ", mostrar_resultados_fase_gfav(conj_selecciones.cur->seleccion, i));
                fprintf(seleccion_resultados_export, "GC: %d\n", mostrar_resultados_fase_gcon(conj_selecciones.cur->seleccion, i));
                break;
            }
            case (4):{
                fprintf(seleccion_resultados_export, " * Fase: Final, ");
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==1){
                    fprintf(seleccion_resultados_export, "Resultado: Gano, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==0){ 
                    fprintf(seleccion_resultados_export, "Resultado: Perdio, ");
                }
                if (mostrar_resultados_fase_punt_parcial(conj_selecciones.cur->seleccion, i)==2){ 
                    fprintf(seleccion_resultados_export, "Resultado: Pendiente, ");
                }

                fprintf(seleccion_resultados_export, "GF: %d, ", mostrar_resultados_fase_gfav(conj_selecciones.cur->seleccion, i));
                fprintf(seleccion_resultados_export, "GC: %d\n", mostrar_resultados_fase_gcon(conj_selecciones.cur->seleccion, i));
            }
        }
    }
    fclose(seleccion_resultados_export);

    printf("\n - Los resultados se guardaron en el archivo \"%s\"", nombre_del_archivo);
    printf("\n\n Pulse para volver al menu...");
    fflush(stdin);
    getchar();

    
}

void borrar_seleccion(LISTA *conj_selecciones){
    int borrar, check_resp;
    system("cls");
    printf("\n # # #   B O R R A R   S E L E C C I O N   # # #\n");
    printf("\n - Seleccion: %s", mostrar_pais(conj_selecciones->cur->seleccion));
    printf("\n\a # Esta seguro que quiere borrar esta seleccion?");
    printf("\n\t (1) = si    (0) = no");
    printf("\n\n - Resp: ");
    check_resp = scanf("%d", &borrar);
    while(check_resp!=1 | borrar!=0 && borrar!=1 ){
        printf("\n\a # Respuesta invalida...");
        printf("\n # Esta seguro que quiere borrar esta seleccion?");
        printf("\n\t (1) = si    (2) = no");
        printf("\n\n - Resp: ");
        check_resp = scanf("%d", &borrar);
    }
    if (borrar==1){
        FILE *seleccion_borrada;
        char nombre_del_archivo[pais_nomb_max];
        strcpy(nombre_del_archivo, mostrar_pais(conj_selecciones->cur->seleccion));
        strcat(nombre_del_archivo, "_BORRADO.txt");

        seleccion_borrada = fopen(nombre_del_archivo, "w");
        fprintf(seleccion_borrada, "%s\n", mostrar_pais(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%s\n", mostrar_dt(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%s\n", mostrar_capitan(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%c\n", mostrar_grupo(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d\n", mostrar_puntaje_actual(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%s, %d\n", mostrar_goleador_apellido(conj_selecciones->cur->seleccion), mostrar_goleador_goles(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d-%d-%d\n", mostrar_fecha_actualizada_dia(conj_selecciones->cur->seleccion), mostrar_fecha_actualizada_mes(conj_selecciones->cur->seleccion), mostrar_fecha_actualizada_anio(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d\n", mostrar_puntaje_actual(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d\n", mostrar_partidos_jugados(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d\n", mostrar_partidos_ganados(conj_selecciones->cur->seleccion));
        fprintf(seleccion_borrada, "%d\n", mostrar_partidos_empatados(conj_selecciones->cur->seleccion));

        fclose(seleccion_borrada);
        suprimir(conj_selecciones);

        system("cls");
        printf("\n # # #   B O R R A R   S E L E C C I O N   # # #\n");
        printf("\n\a # Seleccion borrada y exportada en \"%s\" dentro de la carpeta del programa...", nombre_del_archivo);
    }
    printf("\n\n Pulse para volver al menu...");
    fflush(stdin);
    getchar();
    
}
