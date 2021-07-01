#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "list.h"
#include "map.h"

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0)return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if((int*)key1 == (int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

int main(){

    int op;
    int opInicioSesion;
    int opMenu;
    char* regUsuario;
    char* regContra;
    char* regArtista_1;
    char* regArtista_2;
    char* regGenero_1;
    char* regGenero_2;

    tipoUsuario* usuarioRegistro = (tipoUsuario*) malloc(sizeof(tipoUsuario));

    regUsuario = (char*) malloc(sizeof(regUsuario));
    regContra = (char*) malloc(sizeof(regContra));

    Map *mapaCanciones = createMap(is_equal_int);
    Map *mapaArtista = createMap(is_equal_string);
    Map *mapaGenero = createMap(is_equal_string);
    Map *mapaUsuario = createMap(is_equal_string);

    llenarBD(mapaCanciones, mapaUsuario, mapaArtista, mapaGenero);
    //mostrarMapaUsuario(mapaUsuario);
    //mostrarMapaCanciones(mapaCanciones);
    //mostrarMapaArtista(mapaArtista);
    //mostrarMapaGenero(mapaGenero);

    while(1){//Muestra el menu

        printf("---------------------QUON MUSIC---------------------\n");
        printf("-----------------1. Registrarse---------------------\n");
        printf("----------------2. Iniciar sesion-------------------\n");
        printf("--------------------0. Salir------------------------\n");
        printf("Escriba el numero de la opcion: ");
        scanf("%i", &op);
        system("clear");


        switch (op){
        //case 0 es para salir del programa
        case 0:

            return 0;

        case 1:

            regUsuario = (char*) malloc(sizeof(regUsuario));
            regContra = (char*) malloc(sizeof(regContra));
            regArtista_1 = (char*) malloc(sizeof(regArtista_1));
            regArtista_2 = (char*) malloc(sizeof(regArtista_2));
            regGenero_1 = (char*) malloc(sizeof(regGenero_1));
            regGenero_2 = (char*) malloc(sizeof(regGenero_2));

            printf("--------------------Registrarse---------------------\n");
            printf("Ingrese nombre de usuario: \n");
            scanf("%s", regUsuario);
            printf("Ingrese contrasena:\n");
            scanf("%s", regContra);

            usuarioRegistro = searchMap(mapaUsuario, regUsuario);//si el usuario no existe en el mapa, esta variable sigue siendo NULL

            if(usuarioRegistro == NULL){

              /**mostrar genero musical y artistas**/

              printf("Seleccione 2 artistas:\n\n");

              mostrarMapaArtistaRegistro(mapaArtista);

              printf("Ingrese seleccion:\n");
              printf("Artista 1: ");
              scanf("%s", regArtista_1);
              printf("Artista 2: ");
              scanf("%s", regArtista_2);

              //printf("Ingrese n de artista:\n");

              printf("\nSeleccione 2 generos:\n\n");

              mostrarMapaGeneroRegistro(mapaGenero);

              printf("\nIngrese seleccion:\n");
              printf("Genero 1: ");
              scanf("%s", regGenero_1);
              printf("Genero 2: ");
              scanf("%s", regGenero_2);

              usuarioRegistro = crearUsuario(regUsuario, regContra);

              insertMap(mapaUsuario, usuarioRegistro->nombre, usuarioRegistro);

              //mostrarMapaUsuario(mapaUsuario);

              printf("SE HA REGISTRADO CORRECTAMENTE\n");

            }else{

                printf("ESTE USUARIO YA SE ENCUENTRA REGISTRADO\n");

            }

            break;

        case 2:


            while(1){

                printf("-------------------Iniciar Sesion-------------------\n");
                printf("Ingrese nombre de usuario:\n");
                //scanf() del nombre de usuario
                printf("Ingrese contrasena:\n");
                scanf("%i", &opInicioSesion);//estoy escaneando un int aca, hay qye cambiarlo, solo lo hice para avanzar y probar un poco el menu
                system("clear");

                if( opInicioSesion == 2 ){/**inicio de sesion valido, entra al menu principal de la aplicacion**/

                    printf("Inicio sesion correctamente\n");

                    while(1){

                        printf("Menu\n");
                        printf("1.Explorar Canciones\n");
                        printf("2.Recomendaciones\n");//submenu
                        printf("3.Ver mis Canciones\n");//submenu
                        printf("4.Ver mis Artistas\n");//submenu
                        printf("5.Ver mis Generos\n");//submenu
                        printf("6.Cerrar Sesion\n");
                        printf("0.Salir\n");
                        printf("Escriba el numero de la opcion: ");
                        scanf("%i", &opMenu);
                        system("clear");

                        switch(opMenu){

                        case 0:

                            return 0;

                        case 1:

                            printf("EXPLORAR CANCIONES\n");
                            break;

                        case 2:

                            printf("RECOMENDACIONES\n");
                            break;

                        case 3:

                            printf("CANCIONES\n");
                            break;

                        case 4:

                            printf("ARTISTAS\n");
                            break;

                        case 5:

                            printf("GENEROS\n");
                            break;

                        case 6:

                            printf("CERRAR SESION\n");
                            break;

                        default:

                            printf("Opcion invalida");
                            break;

                        }

                        if (opMenu == 6) break;
                        //break;


                    }

                }else{

                    printf("Datos incorrectos\n");

                }

            }

            break;

        default:

            printf("Opcion invalida");
            break;

        }

    }

    return 0;
}
