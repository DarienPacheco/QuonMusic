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
/*
void *crearUsuarioCSV(FILE *archivo, char *linea){

  archivo = fopen("usuarios.txt","r");
  if(archivo == NULL)
  {
    printf("ERROR AL ABRIR EL ARCHIVO\n");
    return 0;
  }
  
  tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

  fgets(linea, 1000, archivo);

  usuario->nombre = (char*) get_csv_field(linea, 0);
	usuario->contrasena = (char*) get_csv_field(linea, 1);

  char* artista = "error";
    
  fgets(linea, 1000, archivo);
  usuario->artistas_favoritos = list_create((void *)usuario->artistas_favoritos);

  for (int i=0 ; artista ; i++){

    artista = (char*) get_csv_field(linea, i);

    if (artista != NULL){
      list_push_back(usuario->artistas_favoritos, artista);
    }

  }
  
  
  
	return usuario;

}
*/
tipoUsuario *crearUsuario(char* user, char* contra, char* artista1, char* artista2, char* genero1, char* genero2){

  tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

  usuario->artistas_favoritos = list_create((void *) usuario->artistas_favoritos);
  usuario->generos_favoritos = list_create((void *) usuario->generos_favoritos);
  usuario->canciones_favoritas = list_create((void *) usuario->canciones_favoritas);

  list_push_back(usuario->artistas_favoritos, artista1);
  list_push_back(usuario->artistas_favoritos, artista2);
  list_push_back(usuario->generos_favoritos, genero1);
  list_push_back(usuario->generos_favoritos, genero2);

  list_push_back(usuario->canciones_favoritas, NULL);

  usuario->nombre = user;
	usuario->contrasena = contra;

	return usuario;

}

void *crearCancionCSV(char *linea){

  tipoCancion *cancion = (tipoCancion*) malloc (sizeof(tipoCancion));

  cancion->id = (char*) get_csv_field(linea, 0);
	cancion->nombre = (char*) get_csv_field(linea, 1);
	cancion->artista = (char*) get_csv_field(linea, 2);
	cancion->genero = (char*) get_csv_field(linea, 3);
	cancion->subgenero = (char*) get_csv_field(linea, 4);
	cancion->puntaje = strtol(get_csv_field(linea, 5), NULL, 10);
  //printf("%d", cancion->puntaje);

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
    int cont=0, aux=0;

    //LEER DATOS PARA MAPA DE USUARIOS.

    tipoUsuario *datoUsuario;

    archivo = fopen("usuarios.txt","r");
    if(archivo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        //ExitProcess(0);
    }

    while(fgets(linea, 1000, archivo)){
      aux = aux + 1;
    }
    aux = (aux/3);
    rewind(archivo);

    while(cont < aux/**CAMBIAR ESTO -- fgets(linea, 1000, archivo) != NULL**/)
    {
      tipoUsuario *datoUsuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

      fgets(linea, 1000, archivo);
      datoUsuario->canciones_favoritas = list_create((void*) datoUsuario->canciones_favoritas);

      datoUsuario->nombre = (char*) get_csv_field(linea, 0);
	    datoUsuario->contrasena = (char*) get_csv_field(linea, 1);

      char* cancion = "";

      for(int j=2 ; cancion ; j++){

        cancion = (char*) get_csv_field(linea, j);
        if (cancion != NULL){
          list_push_back(datoUsuario->canciones_favoritas, cancion);
        }

      }

      char* artista = "error";
    
      fgets(linea, 1000, archivo);
      datoUsuario->artistas_favoritos = list_create((void *)datoUsuario->artistas_favoritos);

      for (int i=0 ; artista ; i++){

        artista = (char*) get_csv_field(linea, i);

        if (artista != NULL){
          list_push_back(datoUsuario->artistas_favoritos, artista);
        }

      }

      fgets(linea, 1000, archivo);
      datoUsuario->generos_favoritos = list_create((void*) datoUsuario->generos_favoritos);

      char* genero = "error";

      for (int k=0; genero ; k++){

        genero = (char*) get_csv_field(linea, k);

        if (genero != NULL){
          list_push_back(datoUsuario->generos_favoritos, genero);
        }

      }

      //datoUsuario = crearUsuarioCSV(archivo, linea);
      insertMap(mapaUsuario, datoUsuario->nombre, datoUsuario);
      cont++;
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

  char* artista = (char*) malloc(sizeof(artista));
  char* genero = (char*) malloc(sizeof(genero));
  char* cancion = (char*) malloc(sizeof(cancion));

  datoUsuario = firstMap(mapa);
  printf("-----Mapa de Usuarios y contrasenas-----\n");

  while( datoUsuario != NULL ){

    printf("%s \n", datoUsuario->nombre);
    printf("%s \n", datoUsuario->contrasena);

    cancion = (char*) malloc(sizeof(cancion));

    cancion = list_first(datoUsuario->canciones_favoritas);

    while(cancion != NULL){

      //printf("%s, ", cancion);
      printf("%s", cancion);

      cancion = list_next(datoUsuario->canciones_favoritas);
      if( cancion != NULL ) printf(", ");
    }

    printf("\n");

    artista = (char*) malloc(sizeof(artista));

    artista = list_first(datoUsuario->artistas_favoritos);
  
    while(artista != NULL ){

      printf("%s", artista);

      artista = list_next(datoUsuario->artistas_favoritos);
      if( artista != NULL ) printf(", ");

    }

    printf("\n");

    genero = (char*) malloc(sizeof(genero));

    genero = list_first(datoUsuario->generos_favoritos);

    while(genero != NULL){

      printf("%s", genero);

      genero = list_next(datoUsuario->generos_favoritos);
      if( genero != NULL ) printf(", ");

    }

    printf("\n\n");
    
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

        printf("%s \n", datoCancion->id);
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
  char* artista2;
  char* artista3;

  artista = list_first(listaArtista);
  artista2 = "";
  artista3 = "";
  
  
  while(artista != NULL ){

    /**printf("%s \n", artista);

    artista = list_next(listaArtista);**/

    for(int i=1; artista != NULL; i=i+3){

      artista = list_next(listaArtista);
      if(artista ==NULL) break;
      artista2 = list_next(listaArtista);
      //if(artista2 == NULL) break;
      artista3 = list_next(listaArtista);
      //if(artista3 == NULL) break;

      //printf("%d.-%s %3d.-%s %3d.-%s\n", i, artista, i+1, artista2, i+2, artista3);
      printf("%d.-%s \t%d.-%s \t%d.-%s\n", i, artista, i+1, artista2, i+2, artista3);

    }

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

void recomendacion_de_artistas(Map* mapaArtista, tipoUsuario* usuarioIngreso){

  list *lista_artistas = list_create((void*)lista_artistas);

  char* artista = (char*) malloc(sizeof(artista));
  char* artista2 = (char*) malloc(sizeof(artista2));

  tipoArtista *oArtista = (tipoArtista*) malloc(sizeof(tipoArtista));
  tipoArtista *oArtistaBusqueda = (tipoArtista*) malloc(sizeof(tipoArtista));

  artista = list_first(usuarioIngreso->artistas_favoritos);

  printf("Te recomendamos estos artistas:\n");

  while (artista != NULL){

    oArtista = searchMap(mapaArtista, artista);
    //printf("%s \n", oArtista->genero);

    oArtistaBusqueda = firstMap(mapaArtista);
    while(oArtistaBusqueda != NULL){

      if( !(strcmp(oArtistaBusqueda->genero, oArtista->genero)) ){
        list_push_back(lista_artistas, oArtistaBusqueda->nombre);
      }

      oArtistaBusqueda = nextMap(mapaArtista);

    }

    artista = list_next(usuarioIngreso->artistas_favoritos);

  }

  artista2 = list_first(lista_artistas);

  while(artista2 != NULL){

    printf("%s\n", artista2);
    artista2 = list_next(lista_artistas);

  }

}

void recomendacion_de_generos_fav(Map* mapaGenero, tipoUsuario* usuarioIngreso){

  char* cancion="";
  char* genero_usuario;

  tipoGenero *oGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
  tipoGenero *oGenero_busqueda = (tipoGenero*) malloc(sizeof(tipoGenero));

  genero_usuario = list_first(usuarioIngreso->generos_favoritos);

  printf("Te recomendamos estas canciones según tus generos favoritos:\n");

  while( genero_usuario != NULL ){

    oGenero = searchMap(mapaGenero, genero_usuario);

    oGenero_busqueda = oGenero;

    cancion = list_first(oGenero_busqueda->listaCanciones);

    while(cancion != NULL){

      printf("%s \n", cancion);
      cancion = list_next(oGenero_busqueda->listaCanciones);

    }

    genero_usuario = list_next(usuarioIngreso->generos_favoritos);

  }

}

void cancion_por_genero(char* input, Map* mapaGenero){

  tipoGenero *oGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
  char *cancion;
  //printf("%s", input);
  oGenero = searchMap(mapaGenero, input);
  //printf("%s",oGenero->nombre);
  cancion = list_first(oGenero->listaCanciones);

  printf("Te recomendamos esta cancion: \n");
  printf("%s\n", cancion);

}

void cancionPorArtista(Map* mapaArtista, char* artistaEscogido){

  list *listaCanciones = list_create((void*)listaCanciones);

  tipoArtista* oArtista = (tipoArtista*) malloc(sizeof(tipoArtista));

  oArtista = searchMap(mapaArtista, artistaEscogido);

  listaCanciones = oArtista->listaCanciones;

  char* cancion;

  cancion = list_first(listaCanciones);

  printf("Te recomendamos estas canciones: \n");

  while( cancion != NULL ){

    printf("%s\n", cancion);

    cancion = list_next(listaCanciones);

  }

}

void canciones_del_usuario(Map* mapaUsuario, Map* mapaCanciones, tipoUsuario* usuarioIngreso){


  char* cancion;
  char* cancion_2;
  char* cancion_eliminar;
  int op;
  tipoCancion* busqueda_cancion = (tipoCancion*) malloc(sizeof(tipoCancion));

  while(1){
    
    cancion = list_first(usuarioIngreso->canciones_favoritas);
    printf("Estas son tus canciones favoritas:\n");
    while(cancion != NULL){

      printf("%s\n", cancion);
      cancion = list_next(usuarioIngreso->canciones_favoritas);
    }
    printf("{---------------------}\n");

    printf("Que quieres hacer\n");
    printf("1.Agregar una cancion\n");
    printf("2.Quitar una cancion\n");
    printf("3.Atras\n");

    scanf("%d", &op);

    switch(op){

      case 1:

        printf("Escribe la cancion que quieres agregar:\n");
        cancion_2 = leerCharEspacio(cancion_2);
        system("clear");
        
        busqueda_cancion = firstMap(mapaCanciones); //me coloco en el primer dato del mapa canciones

        while(busqueda_cancion != NULL){

          if(strcmp(cancion_2, busqueda_cancion->nombre) == 0){
            
            list_push_back(usuarioIngreso->canciones_favoritas, busqueda_cancion->nombre);
            //usuario_temp = firstMap(mapaUsuario);
            eraseMap(mapaUsuario, usuarioIngreso->nombre);
            insertMap(mapaUsuario, usuarioIngreso->nombre, usuarioIngreso);
            //mostrarMapaUsuario(mapaUsuario);
            printf("Cancion agregada Exitosamente !!!\n");
            printf("{-------------------------------}\n\n");
            break;

          }

          busqueda_cancion = nextMap(mapaCanciones);
          
        }
        if (busqueda_cancion == NULL) printf("La cancion que está intentando agregar no existe :(\n");

        break;

      case 2:
        
        printf("Escribe la cancion que quieres eliminar:\n");
        cancion_eliminar = leerCharEspacio(cancion_eliminar);
        system("clear");

        cancion = list_first(usuarioIngreso->canciones_favoritas);
        while(cancion != NULL){

          if(strcmp(cancion, cancion_eliminar) == 0){
            list_pop_current(usuarioIngreso->canciones_favoritas);
            printf("Cancion eliminada Exitosamente !\n");
            //mostrarMapaUsuario(mapaUsuario);
            break;
            
          }
          cancion = list_next(usuarioIngreso->canciones_favoritas);
        }

        if(cancion == NULL) printf("La cancion que ingresó no la tiene agregada\n");
        //printf("La cancion que ingresó no la tiene agregada\n");

        break;

      case 3:

        break;

      default:

        break;
      
    }
    
    if(op == 3) break;

  }

}

void artistas_del_usuario(Map* mapaUsuario, Map* mapaArtista, tipoUsuario* usuarioIngreso){


  char* artista;
  char* artista_2;
  char* cancion_eliminar;
  int op;
  tipoArtista* busqueda_artista = (tipoArtista*) malloc(sizeof(tipoArtista));

  while(1){

    artista = list_first(usuarioIngreso->artistas_favoritos);
    printf("Estos son tus artistas favoritos:\n");
    while(artista != NULL){

      printf("%s\n", artista);
      artista = list_next(usuarioIngreso->artistas_favoritos);
    }
    printf("{---------------------}\n");

    printf("Que quieres hacer\n");
    printf("1.Agregar un artista\n");
    printf("2.Quitar un artista\n");
    printf("3.Atras\n");
    printf("Escriba el numero de la opcion: ");

    scanf("%d", &op);

    switch(op){

      case 1:

        printf("Escribe el Artista que quieres agregar:\n");
        artista_2 = leerCharEspacio(artista_2);
        
        system("clear");
        busqueda_artista = firstMap(mapaArtista); //me coloco en el primer dato del mapa artistas

        while(busqueda_artista != NULL){

          if(strcmp(artista_2, busqueda_artista->nombre) == 0){
            
            list_push_back(usuarioIngreso->artistas_favoritos, busqueda_artista->nombre);

            eraseMap(mapaUsuario, usuarioIngreso->nombre);
            insertMap(mapaUsuario, usuarioIngreso->nombre, usuarioIngreso);
            //mostrarMapaUsuario(mapaUsuario);
            printf("Artista agregado Exitosamente !!!\n");
            printf("{-------------------------------}\n\n");
            break;

          }

          busqueda_artista = nextMap(mapaArtista);
          
        }
        if (busqueda_artista == NULL) printf("El artista que está intentando agregar no existe :(\n");

        break;

      case 2:
        
        printf("Escribe el artista que quieres eliminar:\n");
        cancion_eliminar = leerCharEspacio(cancion_eliminar);
        system("clear");

        artista = list_first(usuarioIngreso->artistas_favoritos);
        while(artista != NULL){

          if(strcmp(artista, cancion_eliminar) == 0){
            list_pop_current(usuarioIngreso->artistas_favoritos);
            printf("Artista eliminado Exitosamente !\n");
            //mostrarMapaUsuario(mapaUsuario);
            break;
            
          }
          artista = list_next(usuarioIngreso->artistas_favoritos);
        }

        if(artista == NULL) printf("El artista que ingresó no lo tiene agregado\n");

        break;

      case 3:

        break;

      default:

        break;
      
    }
    
    
    if(op == 3) break;

  }

}

void generosdelUsuario( Map* mapaUsuario, Map* mapaGenero, tipoUsuario* usuarioIngreso ){

  char* generoPrinteo;
  char* generoAgregar;
  char* generoQuitar;
  char* listaGeneroQuitar;

  int op;

  tipoGenero* busquedaGenero = (tipoGenero*) malloc(sizeof(tipoGenero));

  listaGeneroQuitar = list_first(usuarioIngreso->generos_favoritos);
  generoPrinteo = list_first(usuarioIngreso->generos_favoritos);

  printf("Estos son tus generos favoritos:\n");

  while(generoPrinteo != NULL){

    printf("%s\n", generoPrinteo);
    generoPrinteo = list_next(usuarioIngreso->generos_favoritos);
    
  }
  printf("{---------------------}\n");

  while(1){

    printf("Que quieres hacer\n");
    printf("1.Agregar un genero\n");
    printf("2.Quitar un genero\n");
    printf("3.Atras\n");
    printf("Escriba el numero de la opcion: ");
    scanf("%i", &op);

    switch(op){

      case 1:
        //AGREGAR GENERO
        printf("Escribe el genero que quieres agregar:\n");
        generoAgregar = leerCharEspacio(generoAgregar);
        
        busquedaGenero = firstMap(mapaGenero);

        while(busquedaGenero != NULL){

          if(strcmp(generoAgregar, busquedaGenero->nombre) == 0){
            
            list_push_back(usuarioIngreso->generos_favoritos, busquedaGenero->nombre);
            printf("Se ha agregado correctamente\n");
            
          }

          busquedaGenero = nextMap(mapaGenero);

        }
        
        break;

      case 2:
        //QUITAR GENERO
        printf("Escribe el genero que quiere quitar:\n");
        generoQuitar = leerCharEspacio(generoQuitar);

        listaGeneroQuitar = list_first(usuarioIngreso->generos_favoritos);

        while( listaGeneroQuitar != NULL ){

          if( strcmp(generoQuitar, listaGeneroQuitar) == 0 ){

            list_pop_current(usuarioIngreso->generos_favoritos);
            listaGeneroQuitar = list_next(usuarioIngreso->generos_favoritos);
            printf("Se ha quitado correctamente\n");

          }

          listaGeneroQuitar = list_next(usuarioIngreso->generos_favoritos);

        }

        break;

      case 3:
        //ATRAS
        break;

      default:

        break;
      
    }

    if(op == 3) break; 

  }

}

char* leerCharEspacio( char* palabra ){

  palabra = malloc(sizeof(char)*100);

  fflush(stdin);
  getchar();
  scanf("%[^\n]s",palabra);

  //printf("%s\n",artista);

  return palabra;

}

void escribir_txt(Map* mapaUsuario){

  FILE* flujo = fopen("usuarios.txt", "w");
  char* dato;
  tipoUsuario* usuario = (tipoUsuario*) malloc(sizeof(tipoUsuario));

  if( flujo == NULL ){
    perror("Error en la lectura de archivo");
  }
  else{

    usuario = firstMap(mapaUsuario);

    while(usuario != NULL){

      fprintf(flujo, "%s,", usuario->nombre);
      fprintf(flujo, "%s", usuario->contrasena);

      dato = list_first(usuario->canciones_favoritas);
      while(dato != NULL){

        fprintf(flujo, ",%s", dato);
        dato = list_next(usuario->canciones_favoritas);
      }
      fprintf(flujo, "\n");

      dato = list_first(usuario->artistas_favoritos);
      while(dato != NULL){

        fprintf(flujo, "%s", dato);
        dato = list_next(usuario->artistas_favoritos);
        if(dato != NULL) fprintf(flujo, ",");
      }
      fprintf(flujo, "\n");

      dato = list_first(usuario->generos_favoritos);
      while(dato != NULL){

        fprintf(flujo, "%s", dato);
        dato = list_next(usuario->generos_favoritos);
        if(dato != NULL) fprintf(flujo, ",");
      }
      fprintf(flujo, "\n");

      usuario = nextMap(mapaUsuario);

    }

    fflush(flujo);
    fclose(flujo);

    printf("TXT SOBRESCRITO");
  }

}