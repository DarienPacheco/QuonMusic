#include <stdio.h>
#include <stdlib.h>
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

    Map *mapaCanciones = createMap(is_equal_int);
    Map *mapaArtista = createMap(is_equal_string);
    Map *mapaGenero = createMap(is_equal_string);
    Map *mapaUsuario = createMap(is_equal_string);

    llenarBD(mapaUsuario, mapaCanciones, mapaArtista);
    mostrarMapaUsuario(mapaCanciones);
    mostrarMapaCanciones(mapaUsuario);
    mostrarMapaArtista(mapaArtista);

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

            printf("--------------------Registrarse---------------------\n");
            printf("Ingrese nombre de usuario: \n");
            //un scanf del nombre de usuario
            printf("Ingrese contrasena:\n");
            //un scanf de la contrasena

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
                        printf("7.Atras\n");
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

                        case 7:

                            break;

                        default:

                            printf("Opcion invalida");
                            break;

                        }

                        break;


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
