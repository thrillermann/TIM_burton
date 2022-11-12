//funciones originales...

int buscar_pais (LISTA *posicion, char buscado[], int total){ // funcion b original
    int i=0, verdadero=0;
    reset(posicion);
    while (i<total||verdadero!=0) {
        verdadero=strcmp((*posicion).cur->seleccion.pais, buscado);
        if (verdadero!=0) {
         avanzar(posicion);
        };
        i++;
    };
    if (verdadero==0) {
        return 1;
    } else {
        return 0;
    };
}

void cargar_datos_orig(){ //* funcion a original*//
    Equipo equipo;
    char pais[],dt[],capitan[],grupo;
    int puntaje_actual,salir=1;
    
    do {
            
        printf("Ingrese la seleccion que desea insertar:");
        fgets(pais,100,stdin);
        
        //aca ingresar funcion buscar con pais
        if (/* equipo esta */){
            cargar_pais(equipo,pais);
            printf("Ingrese el apellido y nombre del dt:");
            fgets(dt,50,stdin);
            cargar_dt(equipo,dt);
            printf("Ingrese el apellido del capitan del equipo:");
            scanf("%s",capitan);
            cargar_capitan(equipo,capitan);
            printf("Ingrese el grupo en el juega el equipo:");
            scanf("%c",grupo);
            cargar_grupo(equipo,grupo);
            printf("Ingrese el puntaje actual del equipo");
            scanf("%d",puntaje_actual);
            cargar_puntaje_actual(equipo,puntaje_actual);
            printf("Ingrese la fase actual");
            scanf("%d",fase);
            cargar_fase(equipo,fase);
    
  

