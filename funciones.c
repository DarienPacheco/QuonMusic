#include "list.h"
#include "funciones.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//Funcion dada por el profesor para leer archivos .csv
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

void *crearUsuarioCSV(char *linea){

    tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

    usuario->nombre = (char*) get_csv_field(linea, 0);
	usuario->contrasena = (char*) get_csv_field(linea, 1);

	return usuario;

}

void *crearUsuario(char* user, char* contra){

    tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

    usuario->nombre = user;
	usuario->contrasena = contra;

	return usuario;

}

void *crearCancionCSV(char *linea){

    tipoCancion *cancion = (tipoCancion*) malloc (sizeof(tipoCancion));

    cancion->id = (int) get_csv_field(linea, 0);
	cancion->nombre = (char*) get_csv_field(linea, 1);
	cancion->artista = (char*) get_csv_field(linea, 2);
	cancion->genero = (char*) get_csv_field(linea, 3);
	cancion->subgenero = (char*) get_csv_field(linea, 4);
	cancion->puntaje = (int) get_csv_field(linea, 5);

	return cancion;

}

void *crearArtistaCSV(char *linea){

    tipoArtista *artista = (tipoArtista*) malloc (sizeof(tipoArtista));

    artista->nombre = (char*) get_csv_field(linea, 0);
    artista->genero = (char*) get_csv_field(linea, 1);
    artista->subgenero = (char*) get_csv_field(linea, 2);

    char* cancion = "hola";
    
    artista->listaCanciones = list_create((void *) artista->listaCanciones);

    for (int i=3 ; cancion ; i++){

      cancion = (char*) get_csv_field(linea, i);

      if (cancion != NULL){
        list_push_back(artista->listaCanciones, cancion);
      }

    }

    return artista;

}

void *crearGeneroCSV(char *linea){

    tipoGenero *genero = (tipoGenero*) malloc (sizeof(tipoGenero));

    char* cancion = "hola";

    genero->nombre = (char*) get_csv_field(linea, 0);
    
    genero->listaCanciones = list_create((void *) genero->listaCanciones);

    for (int i=1 ; cancion ; i++){

      cancion = (char*) get_csv_field(linea, i);

      if (cancion != NULL){
        list_push_back(genero->listaCanciones, cancion);
      }

    }
    return genero;

}

void llenarBD(Map *mapaCanciones, Map* mapaUsuario, Map* mapaArtista, Map* mapaGenero){

    FILE *archivo;
    char linea[1001];

    //LEER DATOS PARA MAPA DE USUARIOS.

    tipoUsuario *datoUsuario;

    archivo = fopen("usuarios.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        //ExitProcess(0);
    }

    while(fgets(linea, 1000, archivo)!= NULL)
    {
        datoUsuario = crearUsuarioCSV(linea);
        insertMap(mapaUsuario, datoUsuario->nombre, datoUsuario);
    }

    fclose(archivo);

    //LEER DATOS PARA MAPA DE CANCIONES.

    tipoCancion *datoCancion;

    archivo = fopen("canciones.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        return;
    }

    while(fgets(linea, 1000, archivo)!= NULL)
    {
        datoCancion = crearCancionCSV(linea);
        insertMap(mapaCanciones, datoCancion->id, datoCancion);
    }

    fclose(archivo);

    //LEER LOS DATOS PARA EL MAPA ARTISTAS

    tipoArtista *datoArtista;

    archivo = fopen("artista.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        return;
    }

    while(fgets(linea, 1000, archivo)!= NULL)
    {
        datoArtista = crearArtistaCSV(linea);
        insertMap(mapaArtista, datoArtista->nombre, datoArtista);
    }

    fclose(archivo);

    //LEER LOS DATOS PARA EL MAPA GENEROS

    tipoGenero *datoGenero;

    archivo = fopen("genero.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        return;
    }

    while(fgets(linea, 1000, archivo)!= NULL)
    {
        datoGenero = crearGeneroCSV(linea);
        insertMap(mapaGenero, datoGenero->nombre, datoGenero);
    }

    fclose(archivo);
}

void mostrarMapaUsuario(Map* mapa){

    tipoUsuario* datoUsuario = (tipoUsuario*) malloc(sizeof(tipoUsuario));

    datoUsuario = firstMap(mapa);
    printf("-----Mapa de Usuarios y contrasenas-----\n");

    while( datoUsuario != NULL ){

        printf("%s \n", datoUsuario->nombre);
        printf("%s \n", datoUsuario->contrasena);
        printf("\n");


        datoUsuario = nextMap(mapa);

    }
    printf("\n");

    free(datoUsuario);
}

void mostrarMapaCanciones(Map* mapa){

    tipoCancion* datoCancion = (tipoCancion*) malloc(sizeof(tipoCancion));

    datoCancion = firstMap(mapa);
    printf("-----Mapa de canciones-----\n");

    while( datoCancion != NULL ){

        printf("%d \n", datoCancion->id);
        printf("%s \n", datoCancion->nombre);
        printf("%s \n", datoCancion->artista);
        printf("%s \n", datoCancion->genero);
        printf("%s \n", datoCancion->subgenero);
        printf("%d \n", datoCancion->puntaje);
        printf("\n");


        datoCancion = nextMap(mapa);

    }
    printf("\n");
    free(datoCancion);
}

void mostrarMapaArtista(Map* mapa){

    tipoArtista* datoArtista = (tipoArtista*) malloc(sizeof(tipoArtista));
    char* cancion;

    datoArtista = firstMap(mapa);
    printf("-----Mapa de Artistas-----\n");

    while( datoArtista != NULL ){

        printf("%s \n", datoArtista->nombre);
        printf("%s \n", datoArtista->genero);
        printf("%s \n", datoArtista->subgenero);

        cancion = list_first(datoArtista->listaCanciones);
  
        while(cancion != NULL ){

          printf("%s \n", cancion);

          cancion = list_next(datoArtista->listaCanciones);

        }
        printf("\n");

        datoArtista = nextMap(mapa);

    }

    printf("\n");
    free(datoArtista);
}

void mostrarMapaArtistaRegistro(Map* mapa){

  tipoArtista* oArtista = (tipoArtista*) malloc(sizeof(tipoArtista));

  list *listaArtista = list_create((void*) listaArtista);

  oArtista = firstMap(mapa);

  while( oArtista != NULL ){

    //printf("%s \n", oArtista->nombre);
    list_push_front(listaArtista, oArtista->nombre);
    
    oArtista = nextMap(mapa);

  }

  char* artista;

  artista = list_first(listaArtista);
  
  while(artista != NULL ){

    printf("%s \n", artista);

    artista = list_next(listaArtista);

  }

  printf("\n");
  free(oArtista);

}

void mostrarMapaGenero(Map* mapa){

    tipoGenero* datoGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
    char* cancion;
    
    //int num = list_size(datoGenero->listaCanciones);

    datoGenero = firstMap(mapa);
    printf("-----Mapa de Generos-----\n");

    while( datoGenero != NULL ){

        printf("%s \n", datoGenero->nombre);
        
        cancion = list_first(datoGenero->listaCanciones);
  
        while(cancion != NULL ){

          printf("%s \n", cancion);

          cancion = list_next(datoGenero->listaCanciones);

        }
        printf("\n");

        datoGenero = nextMap(mapa);

    }

    printf("\n");
    free(datoGenero);
}

void mostrarMapaGeneroRegistro(Map* mapa){

  tipoGenero* oGenero = (tipoGenero*) malloc(sizeof(tipoGenero));

  list *listaGenero = list_create((void*) listaGenero);

  oGenero = firstMap(mapa);

  while( oGenero != NULL ){

    //printf("%s \n", oGenero->nombre);
    list_push_front(listaGenero, oGenero->nombre);

    oGenero = nextMap(mapa);

  }

  char* genero;

  genero = list_first(listaGenero);

  while( genero != NULL ){

    printf("%s \n", genero);

    genero = list_next(listaGenero);

  }

  free(oGenero);
  
}
