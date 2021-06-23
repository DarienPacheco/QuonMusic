#include <stdio.h>
#include <stdlib.h>

int main(){

    while(1){//Muestra el menu

        int op;
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

            printf("Elija un nombre de usuario\n");


            break;

        case 2:

            printf("Ingrese Usuario\n");

            break;

        default:

            break;

        }




    }

    return 0;
}
