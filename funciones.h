#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "list.h"
#include "treemap.h"

typedef struct{

    char *nombre;
    char *contrasena;
    list *canciones_favoritas; //esto deberia ser una lista
    list *artistas_favoritos;
    list *generos_favoritos;

}tipoUsuario;

typedef struct{

    char* id;
    char *nombre;
    char *artista;
    char *genero;
    char *subgenero;
    int puntaje;

}tipoCancion;

typedef struct{

    char *nombre;
    char *genero;
    char *subgenero;
    list *listaCanciones;

}tipoArtista;

typedef struct{

    char *nombre;
    list *listaCanciones;

}tipoGenero;

const char *get_csv_field (char * tmp, int k);

/*void *crearUsuarioCSV(FILE *archivo, char *linea);*/

void *crearCancionCSV(char *linea);

void *crearArtistaCSV(char *linea);

void *crearGeneroCSV(char *linea);

tipoUsuario *crearUsuario(char* user, char* contra, char* artista1, char* artista2, char* genero1, char* genero2);

void llenarBD(Map *, Map *, Map *, Map *, TreeMap*, TreeMap*);

void mostrarMapaUsuario(Map*);

void mostrarMapaCanciones(Map*);

void mostrarMapaArtista(Map*);

void mostrarMapaArtistaRegistro(Map*);

void mostrarMapaGenero(Map*);

void mostrarMapaGeneroRegistro(Map*);

void recomendacion_de_artistas(Map* , tipoUsuario* );

void recomendacion_de_generos_fav(Map* , tipoUsuario*);

void cancion_por_genero(char* , Map*);

void cancionPorArtista(Map* , char*);

void canciones_del_usuario(Map*, Map*, tipoUsuario*);

void artistas_del_usuario(Map*, Map*, tipoUsuario*);

void generosdelUsuario( Map*, Map*, tipoUsuario* );

char* leerCharEspacio( char* );

void escribir_canciones_txt(Map*);

void escribir_usuarios_txt(Map*);

void mostrarArbol( TreeMap* );

void explorar_canciones( TreeMap*, tipoUsuario* );

#endif
