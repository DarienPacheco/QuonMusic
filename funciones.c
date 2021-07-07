#include "list.h"
#include "funciones.h"
#include "map.h"
#include "treemap.h"
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

tipoUsuario *crearUsuario(char* user, char* contra, char* artista1, char* artista2, char* genero1, char* genero2){ //crea un usuario a partir de los datos dados en el registrar

  tipoUsuario *usuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

  usuario->artistas_favoritos = list_create((void *) usuario->artistas_favoritos);
  usuario->generos_favoritos = list_create((void *) usuario->generos_favoritos);
  usuario->canciones_favoritas = list_create((void *) usuario->canciones_favoritas);

  //se insertan los datos en las listas del usuario
  list_push_back(usuario->artistas_favoritos, artista1);
  list_push_back(usuario->artistas_favoritos, artista2);
  list_push_back(usuario->generos_favoritos, genero1);
  list_push_back(usuario->generos_favoritos, genero2);

  list_push_back(usuario->canciones_favoritas, NULL);

  usuario->nombre = user;
	usuario->contrasena = contra;

	return usuario;

}

void *crearCancionCSV(char *linea){ //crea un dato tipo cancion con una linea extraida del canciones.txt

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

void *crearArtistaCSV(char *linea){ //crea un dato tipo artista con una linea extraida del canciones.txt

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

void *crearGeneroCSV(char *linea){ //crea un dato tipo genero con una linea extraida del canciones.txt

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

//esta funcion llena nustra base datos
void llenarBD(Map *mapaCanciones, Map* mapaUsuario, Map* mapaArtista, Map* mapaGenero, TreeMap* arbol_canciones, TreeMap* arbolTop10){

    FILE *archivo;
    char linea[1001];
    int cont=0, aux=0;

    //LEER DATOS PARA MAPA DE USUARIOS.

    tipoUsuario *datoUsuario;

    archivo = fopen("usuarios.txt","r");
    if(archivo == NULL)
    {
        perror("ERROR AL ABRIR EL ARCHIVO\n");
        
    }

    //se lee el usuarios.txt y se cuenta la cantidad de lineas para dividirlas por 3 y obtener la cantidad de usuarios
    while(fgets(linea, 1000, archivo)){
      aux = aux + 1;
    }
    aux = (aux/3); 
    rewind(archivo);

    while(cont < aux) //se leen los datos del usuario y se insertan en el mapa usuarios
    {
      tipoUsuario *datoUsuario = (tipoUsuario*) malloc (sizeof(tipoUsuario));

      fgets(linea, 1000, archivo);//primera linea de nombre,contraseña y lista de canciones
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
    
      fgets(linea, 1000, archivo);//segunda linea de artistas favoritos
      datoUsuario->artistas_favoritos = list_create((void *)datoUsuario->artistas_favoritos);

      for (int i=0 ; artista ; i++){

        artista = (char*) get_csv_field(linea, i);

        if (artista != NULL){
          list_push_back(datoUsuario->artistas_favoritos, artista);
        }

      }

      fgets(linea, 1000, archivo);//tercera linea de generos favoritos
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

    //LEER DATOS PARA MAPA DE CANCIONES, ARBOL TOP10 Y ARBOL CANCIONES.

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
        insertTreeMap(arbol_canciones, datoCancion->nombre, datoCancion);
        insertTreeMap(arbolTop10,&(datoCancion->puntaje), datoCancion);

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

void mostrarMapaUsuario(Map* mapa){ //muestra por pantalla el mapa de usuarios

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

    while(cancion != NULL){ //imprime todas las canciones del usuario

      printf("%s", cancion);

      cancion = list_next(datoUsuario->canciones_favoritas);
      if( cancion != NULL ) printf(", ");
    }

    printf("\n");

    artista = (char*) malloc(sizeof(artista));

    artista = list_first(datoUsuario->artistas_favoritos);
  
    while(artista != NULL ){ //imprime todos los artistas del usuario

      printf("%s", artista);

      artista = list_next(datoUsuario->artistas_favoritos);
      if( artista != NULL ) printf(", ");

    }

    printf("\n");

    genero = (char*) malloc(sizeof(genero));

    genero = list_first(datoUsuario->generos_favoritos);

    while(genero != NULL){ //imprime todos los generos del usuario

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

void mostrarMapaCanciones(Map* mapa){ //muestra por pantalla el mapa canciones

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

void mostrarMapaArtista(Map* mapa){ //muestra por pantalla el mapa artistas

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

void mostrarMapaArtistaRegistro(Map* mapa){ //muestra por pantalla los artistas ala hora de registrarse

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

    for(int i=1; artista != NULL; i=i+3){

      artista = list_next(listaArtista);
      if(artista ==NULL) break;
      artista2 = list_next(listaArtista);
      //if(artista2 == NULL) break;
      artista3 = list_next(listaArtista);
      //if(artista3 == NULL) break;

      printf("%d.-%s \t%d.-%s \t%d.-%s\n", i, artista, i+1, artista2, i+2, artista3);

    }

  }

  printf("\n");
  free(oArtista);

}

void mostrarMapaGenero(Map* mapa){ //muestra por pantalla el mapa de los generos

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

void mostrarMapaGeneroRegistro(Map* mapa){ //muestra por pantalla los generos a la hora de registrarse

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

//recomienda artistas según el genero de los artistas que tenga agregado el usuario
void recomendacion_de_artistas(Map* mapaArtista, tipoUsuario* usuarioIngreso){

  list *lista_artistas = list_create((void*)lista_artistas);

  char* artista = (char*) malloc(sizeof(artista));
  char* artista2 = (char*) malloc(sizeof(artista2));

  tipoArtista *oArtista = (tipoArtista*) malloc(sizeof(tipoArtista));
  tipoArtista *oArtistaBusqueda = (tipoArtista*) malloc(sizeof(tipoArtista));

  artista = list_first(usuarioIngreso->artistas_favoritos);

  printf("Te recomendamos estos artistas:\n");
  printf("{-------------------------------}\n");

  while (artista != NULL){ //se recorre la lista de los artistas que tiene el usuario

    oArtista = searchMap(mapaArtista, artista);

    oArtistaBusqueda = firstMap(mapaArtista);
    while(oArtistaBusqueda != NULL){//se buscan artistas que coincidan con los generos del artista que tiene agregado el usuario

      if( !(strcmp(oArtistaBusqueda->genero, oArtista->genero)) ){
        list_push_back(lista_artistas, oArtistaBusqueda->nombre); //se guardan en esta lista los artistas que precenten una coincidencia
      }

      oArtistaBusqueda = nextMap(mapaArtista);

    }

    artista = list_next(usuarioIngreso->artistas_favoritos);

  }

  artista2 = list_first(lista_artistas);

  while(artista2 != NULL){ //se muestran por pantalla los artistas recomendados

    printf("%s\n", artista2);
    artista2 = list_next(lista_artistas);

  }
  printf("{-------------------------------}\n\n");

}

void recomendacion_de_generos_fav(Map* mapaGenero, tipoUsuario* usuarioIngreso){
  //recibimos los datos del usuario y el mapaGenero como parametros desde el main con estos datos buscamos la lista generos_favoritos del usuario y la recorremos, con los generos favoritos que obtenemos de la lista generos_favoritos buscamos en el mapaGenero y en base a eso imprimimos los nombres de las canciones que tiene el genero en su listaCanciones 

  char* cancion="";
  char* genero_usuario;

  tipoGenero *oGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
  tipoGenero *oGenero_busqueda = (tipoGenero*) malloc(sizeof(tipoGenero));

  genero_usuario = list_first(usuarioIngreso->generos_favoritos);

  printf("Te recomendamos estas canciones según tus generos favoritos:\n");
  printf("{-------------------------------}\n");

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

  printf("{-------------------------------}\n\n");

}

void cancion_por_genero(char* input, Map* mapaGenero){

  tipoGenero *oGenero = (tipoGenero*) malloc(sizeof(tipoGenero));
  char *cancion;
  //printf("%s", input);
  oGenero = searchMap(mapaGenero, input);
  //printf("%s",oGenero->nombre);
  cancion = list_first(oGenero->listaCanciones);

  system("@cls||clear");
  printf("Te recomendamos estas canciones: \n");

  while ( cancion!= NULL ){

    printf("%s\n", cancion);
    
    cancion = list_next(oGenero->listaCanciones);

  }

}

void cancionPorArtista(Map* mapaArtista, char* artistaEscogido){
  //recibe un artista(char*) desde el main y lo buscamos  en el mapaArtista para poder imprimir sus canciones 

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
  //con esta funcion podemos ver los artistas que tiene agregado el usuario en su lista de artistas favoritos y agregar o quitar algun artista


  char* cancion;
  char* cancion_2;
  char* cancion_eliminar;
  int op;
  tipoCancion* busqueda_cancion = (tipoCancion*) malloc(sizeof(tipoCancion));
  tipoCancion* eliminarCancion = (tipoCancion*) malloc(sizeof(tipoCancion));

  while(1){
    
    cancion = list_first(usuarioIngreso->canciones_favoritas);
    printf("Estas son tus canciones favoritas:\n");
    printf("{-------------------------------}\n");
    while(cancion != NULL){

      printf("%s\n", cancion);
      cancion = list_next(usuarioIngreso->canciones_favoritas);
    }
    printf("{-------------------------------}\n");

    printf("Que quieres hacer\n");
    printf("1.Agregar una cancion\n");
    printf("2.Quitar una cancion\n");
    printf("3.Atras\n");
    printf("Escriba el numero de la opcion: ");
    
    scanf("%d", &op);

    switch(op){

      case 1:

        printf("Escribe la cancion que quieres agregar:\n");
        cancion_2 = leerCharEspacio(cancion_2);
        system("@cls||clear");
        
        busqueda_cancion = firstMap(mapaCanciones); //me coloco en el primer dato del mapa canciones

        while(busqueda_cancion != NULL){

          if(strcmp(cancion_2, busqueda_cancion->nombre) == 0){

            busqueda_cancion->puntaje++;
            
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

        eliminarCancion = firstMap(mapaCanciones); //me coloco en el primer dato del mapa canciones
        
        printf("Escribe la cancion que quieres eliminar:\n");
        cancion_eliminar = leerCharEspacio(cancion_eliminar);
        system("@cls||clear");

        cancion = list_first(usuarioIngreso->canciones_favoritas);

        while(cancion != NULL){

          if(strcmp(cancion, cancion_eliminar) == 0){

            while(eliminarCancion != NULL){

              if(strcmp(cancion, eliminarCancion->nombre) == 0){

                eliminarCancion = searchMap(mapaCanciones, eliminarCancion->id);
                
                if ( eliminarCancion->puntaje >= 1 ) eliminarCancion->puntaje--;

              }

              eliminarCancion = nextMap(mapaCanciones);

            }

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
        system("@cls||clear");
        break;

      default:

        break;
      
    }
    
    if(op == 3) break;

  }

}

void artistas_del_usuario(Map* mapaUsuario, Map* mapaArtista, tipoUsuario* usuarioIngreso){
  //con esta funcion podemos ver los artistas que tiene agregado el usuario en su lista de artistas favoritos y agregar o quitar algun artista


  char* artista;
  char* artista_2;
  char* cancion_eliminar;
  int op;
  tipoArtista* busqueda_artista = (tipoArtista*) malloc(sizeof(tipoArtista));

  while(1){

    artista = list_first(usuarioIngreso->artistas_favoritos);
    printf("Estos son tus artistas favoritos:\n");
    printf("{-------------------------------}\n");
    while(artista != NULL){

      printf("%s\n", artista);
      artista = list_next(usuarioIngreso->artistas_favoritos);
    }
    printf("{-------------------------------}\n");

    printf("Que quieres hacer\n");
    printf("1.Agregar un artista\n");
    printf("2.Quitar un artista\n");
    printf("3.Atras\n");
    printf("Escriba el numero de la opcion: ");

    scanf("%d", &op);
    system("@cls||clear");

    switch(op){

      case 1:

        printf("Escribe el Artista que quieres agregar:\n");
        artista_2 = leerCharEspacio(artista_2);
        
        system("@cls||clear");
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
        system("@cls||clear");

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
        //ATRAS
        break;

      default:

        break;
      
    }
    
    
    if(op == 3) break;

  }

}

void generosdelUsuario( Map* mapaUsuario, Map* mapaGenero, tipoUsuario* usuarioIngreso ){
  //con esta funcion podemos ver los generos que tiene agregado el usuario en su lista de generos favoritos y agregar o quitar algun genero

  char* generoPrinteo;
  char* generoAgregar;
  char* generoQuitar;
  char* listaGeneroQuitar;

  int op;

  tipoGenero* busquedaGenero = (tipoGenero*) malloc(sizeof(tipoGenero));

  listaGeneroQuitar = list_first(usuarioIngreso->generos_favoritos);
  generoPrinteo = list_first(usuarioIngreso->generos_favoritos);

  printf("Estos son tus generos favoritos:\n");
  printf("{-------------------------------}\n");

  while(generoPrinteo != NULL){

    printf("%s\n", generoPrinteo);
    generoPrinteo = list_next(usuarioIngreso->generos_favoritos);
    
  }
  printf("{-------------------------------}\n");

  while(1){

    printf("Que quieres hacer\n");
    printf("1.Agregar un genero\n");
    printf("2.Quitar un genero\n");
    printf("3.Atras\n");
    printf("Escriba el numero de la opcion: ");
    scanf("%i", &op);

    system("@cls||clear");

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
  //esta funcion lee un string con espacios y lo retorna, con esta funcion podemos leer canciones con espacios, artistas y/o generos que contengan espacios sin ningun problema

  palabra = malloc(sizeof(char)*100);

  fflush(stdin);
  getchar();
  scanf("%[^\n]s",palabra);

  return palabra;

}

void escribir_canciones_txt(Map* mapaCanciones){
  //reescribe el txt cancion (canciones.txt) con los nuevos datos actualizados (actualizados se refiere a cuando agregamos canciones y sube 1 su puntaje por ejemplo)

  FILE* flujo = fopen("canciones.txt", "w");
  char* dato;
  tipoCancion* cancion = (tipoCancion*) malloc(sizeof(tipoUsuario));

  if( flujo == NULL ){
    perror("Error en la lectura de archivo");
  }
  else{

    cancion = firstMap(mapaCanciones);

    while(cancion != NULL){
      
      fprintf(flujo, "%s,", cancion->id);
      fprintf(flujo, "%s,", cancion->nombre);
      fprintf(flujo, "%s,", cancion->artista);
      fprintf(flujo, "%s,", cancion->genero);
      fprintf(flujo, "%s,", cancion->subgenero);
      fprintf(flujo, "%d\n", cancion->puntaje);

      cancion = nextMap(mapaCanciones);
    }

    fflush(flujo);
    fclose(flujo);

  }
}

void escribir_usuarios_txt(Map* mapaUsuario){
  //reescribe el txt usuario (usuario.txt) con los nuevos datos actualizados 

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

  }

}

void mostrarArbol( TreeMap* arbolCanciones){
  //con esta funcion podemos mostrar un arbol con las canciones de nuestra base de datos ordenado de manera alfabetica

  tipoCancion* cancionesMostrar = (tipoCancion*) malloc(sizeof(tipoCancion));

  cancionesMostrar = firstTreeMap(arbolCanciones);

  while ( cancionesMostrar != NULL ){//recorremos el arbol hasta que lleguemos al final

    printf("%s\n", cancionesMostrar->nombre);

    cancionesMostrar = nextTreeMap(arbolCanciones);

  }

}

void explorar_canciones(TreeMap* arbol_canciones, tipoUsuario* usuarioIngreso){
  //en esta funcion mostramos un arbol ordenado alfabeticamente con las canciones de nuestra base de datos y el usuario puede agregarlas a su lista de canciones favoritas o salir de la opcion
  
  mostrarArbol(arbol_canciones);
  printf("\n");

  int op;
  char* cancion;

  tipoCancion * busqueda_cancion = firstTreeMap(arbol_canciones);

  while(1){

    printf("EXPLORAR\n");
    printf("1.Agregar cancion a mi lista\n");
    printf("2.Atras\n");
    printf("Escriba el numero de la opcion: ");
    scanf("%i", &op);
    //system("@cls||clear");

    switch(op){

      case 1:
        //AGREGAR CANCION A LA LISTA USUARIO
        printf("Escribe la cancion que quieres agregar:\n");
        cancion = leerCharEspacio(cancion);
        system("@cls||clear");
        
        busqueda_cancion = searchTreeMap(arbol_canciones, cancion); //me coloco en el primer dato del mapa canciones

          if(strcmp(cancion, busqueda_cancion->nombre) == 0){
            
            busqueda_cancion->puntaje++;//se le suma uno al puntaje de la cancion
            
            list_push_back(usuarioIngreso->canciones_favoritas, busqueda_cancion->nombre);
            //se agrega a la lista de canciones favoritas del usuario

            printf("Cancion agregada Exitosamente !!!\n");
            printf("{-------------------------------}\n\n");
            break;

          }
        
        if (busqueda_cancion == NULL) printf("La cancion que está intentando agregar no existe :(\n");
        break;

      case 2:
        //ATRAS
        system("@cls||clear");
        break;

      default:

        system("@cls||clear");
        printf("Opcion invalida\n");
        op = 2;
        break;

    }

    if ( op == 2 ) break;

  }
  
}
