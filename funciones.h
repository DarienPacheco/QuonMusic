#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "map.h"
#include "list.h"

typedef struct{

    char *nombre;
    char *contrasena;
    //list *canciones_favoritas; //esto deberia ser una lista
    //list *artistas_favoritos;
    //list *generos_favoritos;

}tipoUsuario;

typedef struct{

    int id;
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
    //list canciones;

}tipoArtista;

typedef struct{

    char *nombre;
    //list *canciones;

}tipoGenero;

const char *get_csv_field (char * tmp, int k);

void llenarBD(Map *, Map *, Map *, Map *);

void mostrarMapaUsuario(Map*);

void mostrarMapaCanciones(Map*);

void mostrarMapaArtista(Map*);

void mostrarMapaGenero(Map*);
#endif
