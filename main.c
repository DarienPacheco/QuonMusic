#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "funciones.h"
#include "list.h"
#include "map.h"
#include "treemap.h"

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

int higher_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) > 0) return 1;
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
/*
  función para comparar claves de tipo int
  retorna 1 si son key1>key2
*/
int higher_than_int(void * key1, void * key2) {
    if(*(int*)key1 > *(int*)key2) return 1;
    return 0;
}

int main(){
    //a continuación se declaran las variables a utilizar en el programa
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

    regUsuario = (char*) malloc(sizeof(char)); 
    regContra = (char*) malloc(sizeof(char));

    inicioUsuario = (char*) malloc(sizeof(char));
    inicioContrasena = (char*) malloc(sizeof(char));

    artistaRecomEscogido = (char*) malloc(sizeof(char));

    //a continuación se crean las estructuras de datos utilizadas
    Map *mapaCanciones = createMap(is_equal_int);
    Map *mapaArtista = createMap(is_equal_string);
    Map *mapaGenero = createMap(is_equal_string);
    Map *mapaUsuario = createMap(is_equal_string);
    TreeMap *arbol_canciones = createTreeMap(lower_than_string);
    TreeMap *arbolTop10 = createTreeMap(higher_than_int);

    llenarBD(mapaCanciones, mapaUsuario, mapaArtista, mapaGenero, arbol_canciones, arbolTop10);
    
    while(1){//Muestra el menu

        printf("---------------------QUON MUSIC---------------------\n");
        printf("-----------------1. Registrarse---------------------\n");
        printf("----------------2. Iniciar sesion-------------------\n");
        printf("--------------------0. Salir------------------------\n");
        printf("Escriba el numero de la opcion: ");
        scanf("%i", &op);
        system("@cls||clear");


        switch (op){
        //case 0 es para salir del programa
        case 0:

            return 0;

        case 1:

            regUsuario = (char*) malloc(sizeof(regUsuario));
            regContra = (char*) malloc(sizeof(char));
            regArtista_1 = (char*) malloc(sizeof(char));
            regArtista_2 = (char*) malloc(sizeof(char));
            regGenero_1 = (char*) malloc(sizeof(char));
            regGenero_2 = (char*) malloc(sizeof(char));

            printf("--------------------Registrarse---------------------\n");
            printf("Ingrese nombre de usuario sin espacios: \n");
            scanf("%s", regUsuario);
            printf("Ingrese contrasena sin espacios:\n");
            scanf("%s", regContra);

            usuarioRegistro = searchMap(mapaUsuario, regUsuario);//si el usuario no existe en el mapa, esta variable sigue siendo NULL

            if(usuarioRegistro == NULL){

              /**mostrar genero musical y artistas**/

              printf("Seleccione 2 artistas:\n\n");

              mostrarMapaArtistaRegistro(mapaArtista);

              printf("Ingrese nombre de artista:\n");
              printf("Artista 1: ");
              
              regArtista_1 = leerCharEspacio(regArtista_1);
              printf("Artista 2: ");
              
              regArtista_2 = leerCharEspacio(regArtista_2);

              

              printf("\nSeleccione 2 generos:\n\n");

              mostrarMapaGeneroRegistro(mapaGenero);

              printf("\nIngrese nombre de genero:\n");
              printf("Genero 1: ");
              
              regGenero_1 = leerCharEspacio(regGenero_1);
              printf("Genero 2: ");
              
              regGenero_2 = leerCharEspacio(regGenero_2);

              usuarioRegistro = crearUsuario(regUsuario, regContra, regArtista_1, regArtista_2, regGenero_1, regGenero_2);

              insertMap(mapaUsuario, usuarioRegistro->nombre, usuarioRegistro);
              escribir_usuarios_txt(mapaUsuario);

              system("@cls||clear");

              printf("SE HA REGISTRADO CORRECTAMENTE\n");

            }else{

              system("@cls||clear");
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

                system("@cls||clear");

                if( (strcmp (inicioContrasena, usuarioIngreso->contrasena)) == 0 ){
                  /**inicio de sesion valido, entra al menu principal de la aplicacion**/

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
                        system("@cls||clear");

                        switch(opMenu){

                        case 0:

                            return 0;

                        case 1:

                            //EXPLORAR CANCIONES
                            explorar_canciones(arbol_canciones, usuarioIngreso);
                            escribir_usuarios_txt(mapaUsuario);
                            escribir_canciones_txt(mapaCanciones);
                            break;

                        case 2:

                          

                            while(1) {

                              printf("RECOMENDACIONES\n");
                              printf("1.Segun tus gustos\n");
                              printf("2.Tu escoges\n");
                              printf("3.TOP\n");
                              printf("4.Atras\n");
                              printf("0.Salir\n");
                              printf("Escriba el numero de la opcion: ");
                              scanf("%i", &opRecomendar);

                              system("@cls||clear");

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

                                    system("@cls||clear");

                                    switch(opRecomendar){

                                      case 0:

                                        return 0;

                                      case 1:

                                        printf("RECOMENDACION DE ARTISTAS\n");
                                       
                                        recomendacion_de_artistas(mapaArtista, usuarioIngreso);
                                        
                                        break;

                                      case 2:

                                        printf("RECOMENDAR POR GENEROS\n");
                                        recomendacion_de_generos_fav(mapaGenero, usuarioIngreso);
                                        break;

                                      case 3:
                                        
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
                                 
                                        input = leerCharEspacio(input);

                                        cancion_por_genero(input, mapaGenero);

                                        break;

                                      case 2:

                                        artistaRecomEscogido = (char*) malloc(sizeof(char)*100);

                                        printf("Ingrese un artista para recibir una recomendacion\n");

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

                                  system("@cls||clear");
                                  printf("Este es el TOP 10 de las canciones más populares del momento\n");
                                  printf("{-------------------------------}\n");
                                  int contTop = 0;
                                  
                                  tipoCancion *topCancion = firstTreeMap (arbolTop10);

                                  while (contTop<10 && topCancion != NULL){//Se definen las condiciones para que las canciones entren al top

                                    printf("%d.-%s - %s\n",contTop+1,topCancion->nombre, topCancion->artista );
                                    topCancion = nextTreeMap(arbolTop10);
                                    contTop++;

                                  }
                                  printf("{-------------------------------}\n\n");

                                  break;

                                case 4:

                                  //opcion atras
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
                            canciones_del_usuario(mapaUsuario, mapaCanciones, usuarioIngreso);
                            escribir_usuarios_txt(mapaUsuario);
                            escribir_canciones_txt(mapaCanciones);
                            break;

                        case 4:

                            printf("ARTISTAS\n");
                            artistas_del_usuario(mapaUsuario, mapaArtista, usuarioIngreso);
                            escribir_usuarios_txt(mapaUsuario);
                            break;

                        case 5:

                            printf("GENEROS\n");
                            generosdelUsuario(mapaUsuario, mapaGenero, usuarioIngreso);
                            escribir_usuarios_txt(mapaUsuario);
                            break;

                        case 6:

                            printf("CERRAR SESION\n");
                            
                            break;

                        default:

                            printf("Opcion invalida");
                            break;

                        }

                        if (opMenu == 6) break;
                    }

                }else{

                  printf("Datos incorrectos\n");
                  
                }

            }

            break;

        default:

            printf("Opcion invalida\n");
            break;

        }

    }

    return 0;
}