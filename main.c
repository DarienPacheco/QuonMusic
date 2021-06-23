#include <stdio.h>
#include <stdlib.h>

int main(){

    int op;
    int opInicioSesion;

    while(1){//Muestra el menu

        printf("QUON MUSIC\n");
        printf("1. Registrarse \n");
        printf("2. Iniciar sesion \n");
        printf("0. Salir \n");
        printf("Escriba el numero de la opcion: ");
        scanf("%i", &op);


        switch (op){
        //case 0 es para salir del programa
        case 0:

            return 0;

        case 1:

            printf("Ingreso a Registrarse\n");
            printf("Ingrese nombre de usuario\n");
            //un scanf del nombre de usuario
            printf("Ingrese contrasena\n");
            //un scanf de la contrasena

            break;

        case 2:


            while(1){

                printf("Iniciar Sesion\n");
                printf("Ingrese nombre de usuario\n");
                //scanf() del nombre de usuario
                printf("Ingrese contrasena\n");
                scanf("%i", &opInicioSesion);//estoy escaneando un int aca, hay qye cambiarlo, solo lo hice para avanzar y probar un poco el menu

                if( opInicioSesion == 2 ){/**inicio de sesion valido, entra al menu principal de la aplicacion**/

                    printf("Inicio sesion correctamente\n");

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
