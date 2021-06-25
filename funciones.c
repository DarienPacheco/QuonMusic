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

void *crearUsuario(char *linea){

    tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

    usuario->nombre = get_csv_field(linea, 0);
	usuario->contrasena = get_csv_field(linea, 1);

	return usuario;

}

void llenarBD(/**Map *mapaCanciones, Map *mapaArtista, Map *mapaGenero,**/Map* mapaUsuario){

    FILE *archivo;
    char linea[1001];

    //LEER DATOS PARA MAPA DE USUARIOS.

    tipoUsuario *datoUsuario;

    archivo = fopen("usuarios.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        ExitProcess(1);
    }

    while(fgets(linea, 1000, archivo)!= NULL)
    {
        datoUsuario = crearUsuario(linea);
        insertMap(mapaUsuario, datoUsuario->nombre, datoUsuario);
    }

    fclose(archivo);

}

mostrarMapaUsuario(Map* mapa){

    tipoUsuario* datoUsuario = (tipoUsuario*) malloc(sizeof(tipoUsuario));

    datoUsuario = firstMap(mapa);

    while( datoUsuario != NULL ){


        printf("%s \n", datoUsuario->nombre);
        printf("%s \n", datoUsuario->contrasena);
        printf("\n");


        datoUsuario = nextMap(mapa);

    }

}
