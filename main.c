#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    int opRecomendar;
    char* regUsuario;
    char* regContra;
    char* regArtista_1;
    char* regArtista_2;
    char* regGenero_1;
    char* regGenero_2;
    char* inicioUsuario;
    char* inicioContrasena;
    char* input;
    char* artistaRecomEscogido;

    tipoUsuario* usuarioRegistro = (tipoUsuario*) malloc(sizeof(tipoUsuario));
    tipoUsuario* usuarioIngreso = (tipoUsuario*) malloc(sizeof(tipoUsuario));

    regUsuario = (char*) malloc(sizeof(char)); //cambie todos los sizeof parentesis
    regContra = (char*) malloc(sizeof(char));

    inicioUsuario = (char*) malloc(sizeof(char));
    inicioContrasena = (char*) malloc(sizeof(char));

    //input = (char*) malloc(sizeof(input));
    artistaRecomEscogido = (char*) malloc(sizeof(char));

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

            regUsuario = (char*) malloc(sizeof(char));
            regContra = (char*) malloc(sizeof(char));
            regArtista_1 = (char*) malloc(sizeof(char));
            regArtista_2 = (char*) malloc(sizeof(char));
            regGenero_1 = (char*) malloc(sizeof(char));
            regGenero_2 = (char*) malloc(sizeof(char));

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

              mostrarMapaUsuario(mapaUsuario);

              printf("SE HA REGISTRADO CORRECTAMENTE\n");

            }else{

                printf("ESTE USUARIO YA SE ENCUENTRA REGISTRADO\n");

            }

            break;

        case 2:


            while(1){

                printf("-------------------Iniciar Sesion-------------------\n");
                printf("Ingrese nombre de usuario:\n");
                scanf("%s", inicioUsuario);//scanf() del nombre de usuario

                usuarioIngreso = searchMap(mapaUsuario, inicioUsuario);
                         
                printf("Ingrese contrasena:\n");
                scanf("%s", inicioContrasena);
/*
                printf("%s\n",usuarioIngreso->nombre);
                
                canciones = list_first(usuarioIngreso->canciones_favoritas);

                while(canciones != NULL){
                  printf("%s, ", canciones);
                  canciones = list_next(usuarioIngreso->canciones_favoritas);
                }
                printf("\n");
                */

    
                system("clear");

                if( !(strcmp (inicioContrasena, usuarioIngreso->contrasena)) ){/**inicio de sesion valido, entra al menu principal de la aplicacion**/

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

                          //opRecomendar = (int) malloc(sizeof(opRecomendar)); 

                            while(1) {

                              printf("RECOMENDACIONES\n");
                              printf("1.Segun tus gustos\n");
                              printf("2.Tu escoges\n");
                              printf("3.TOP\n");
                              printf("4.Atras\n");
                              printf("0.Salir\n");
                              printf("Escriba el numero de la opcion: ");
                              scanf("%i", &opRecomendar);

                              system("clear");

                              switch(opRecomendar){

                                case 0:

                                  return 0;

                                case 1:

                                  while(1){

                                    printf("Te recomendaremos música segun tus:\n");
                                    printf("1.Artistas favoritos\n");
                                    printf("2.Generos favoritos\n");
                                    printf("3.Atras\n");
                                    printf("0.Salir\n");
                                    printf("Escriba el numero de la opcion: ");
                                    scanf("%i", &opRecomendar);

                                    switch(opRecomendar){

                                      case 0:

                                        return 0;

                                      case 1:

                                        printf("RECOMENDACION DE ARTISTAS\n");
                                        //arreglar caso en que se repita el genero
                                        recomendacion_de_artistas(mapaArtista, usuarioIngreso);
                                        
                                        break;

                                      case 2:

                                        printf("RECOMENDAR POR GENEROS\n");
                                        recomendacion_de_generos_fav(mapaGenero, usuarioIngreso);
                                        break;

                                      case 3:

                                        printf("Atras\n");
                                        //porque está top 10 aqui?
                                        //tipoCancion * cancionTop = malloc(size_t __size)
                                        break;

                                      default:

                                        printf("Opcion invalida\n");
                                        break;

                                    }

                                    if(opRecomendar == 3) break;

                                  }

                                  break;

                                case 2:

                                  while(1){

                                    printf("Te recomendaremos música según:\n");
                                    printf("1.Un genero de música escogido\n");
                                    printf("2.Un artista escogido\n");
                                    printf("3.Atras\n");
                                    printf("0.Salir\n");
                                    printf("Escriba el numero de la opcion: ");
                                    scanf("%i", &opRecomendar);

                                    switch(opRecomendar){

                                      case 0:

                                        return 0;
                                      
                                      case 1:

                                        input = (char*) malloc(sizeof(char)*100);

                                        printf("Ingrese un genero de música para recibir una recomendacion:\n");
                                        //getchar();
                                        fflush(stdin);
                                        scanf("%s",input);
                                        getchar();
                                        printf("%s", input);
                                        cancion_por_genero(input, mapaGenero);

                                        break;

                                      case 2:

                                        artistaRecomEscogido = (char*) malloc(sizeof(char)*100);

                                        printf("Ingrese un artista para recibir una recomendacion\n");
                                        //scanf("%s", artistaRecomEscogido);//falta arreglar
                                        /**fflush(stdin);
                                        getchar();
                                        scanf("%[^\n]s",artistaRecomEscogido);**/

                                        artistaRecomEscogido = leerCharEspacio(artistaRecomEscogido);

                                        cancionPorArtista(mapaArtista, artistaRecomEscogido);

                                        break;
                                      
                                      case 3:

                                        break;

                                      default:
                                        
                                        printf("Opcion invalida");
                                        break;

                                    }

                                    if(opRecomendar == 3) break;

                                  }

                                  break;

                                case 3:

                                  break;

                                case 4:

                                  break;

                                default:

                                  printf("Opcion invalida");
                                  break; 

                              }

                              if(opRecomendar == 4) break;

                            }

                            break;

                        case 3:

                            printf("CANCIONES\n");
                            canciones_del_usuario(mapaUsuario, usuarioIngreso);
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

                        if (opMenu == 6) break;//falta limpiar los datos de inicio de sesion
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

