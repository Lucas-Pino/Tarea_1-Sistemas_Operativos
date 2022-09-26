#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "auxFuncs.h"
#include "linkedList.h"

#define pedidosFile "/Users/lucas/School/Sistemas operativos/Tarea_1/pedidos.txt"
#define productosFile "/Users/lucas/School/Sistemas operativos/Tarea_1/productos_disponibles.txt"
#define MAXPEDIDOS 100
#define STRLEN


int main() {
    printf("\n");

    //CREANDO LOS PROCESOS HIJOS
    // EL CAJERO SERA EL PROCESO PRINCIPAL


    pid_t repartidor1;
    pid_t repartidor2;
    repartidor1=fork();
    if (repartidor1 < 0){ //Ocurrio un error
        printf("Fallo el fork child1");
        return 1;
    }


    else if(repartidor1==0){ /// PROCESO HIJO 1/////////////////

    }


    else{
        repartidor2=fork();
        if (repartidor2 < 0){ //Ocurrio un error
            printf("Fallo el fork child 2");
            return 1;
        }
        else if (repartidor2==0){ /// PROCESO HIJO 2/////////////////

        } else {/// PROCESO PADRE//////////////////////////

            //variables auxiliares
            char line[256];
            char *token;

            //lista enlazada de productos disponibles, cada nodo contiene una struct 'producto'
            node *listaProductos = NULL;
            initList(listaProductos);

            char *pedidos[MAXPEDIDOS];

            //Creando un producto auxiliar
            producto *tempProd;
            if ((tempProd = (producto *) malloc(sizeof(producto))) == NULL) {
                return 1;
            }

            //CONTADORES PARA SABER CUANTOS PRODUCTOS HAY EN CADA ARCHIVO
            size_t productosCount = 0;
            size_t pedidosCount = 0;

            //ABRIENDO ARCHIVOS
            FILE *pedidosFilePtr;
            FILE *productosFilePtr;

            pedidosFilePtr = fopen(pedidosFile, "r");
            if (NULL == pedidosFilePtr) {
                printf("file can't be opened \n");
            }
            productosFilePtr = fopen(productosFile, "r");
            if (NULL == productosFilePtr) {
                printf("file can't be opened \n");
            }

//Moviendo los productos a mi lista enlazada de productos
            while (fgets(line, sizeof(line), productosFilePtr)) {

                //NAME
                token = strtok(line, ",");
                tempProd->name = malloc(strlen(token) + 1);
                strcpy(tempProd->name, token);

                //PRECIO
                token = strtok(NULL, ",");
                tempProd->price = atoi(token);

                //ID
                token = strtok(NULL, ",");
                tempProd->id = atoi(token);

                //TIME
                token = strtok(NULL, ",");
                tempProd->time = atoi(token);

                push(&listaProductos, tempProd);

            }
//    Agregando pedidos a lista de pedidos
            fgets(line, sizeof(line), pedidosFilePtr);
            token = strtok(line, ",");
            for (pedidosCount; token; pedidosCount++) {
                pedidos[pedidosCount] = malloc(strlen(token) + 1);
                strcpy(pedidos[pedidosCount], token);
                token = strtok(NULL, ",");
            }



//    Recorriendo la lista enlazada de productos disponibles
            printf("PRODUCTOS DISPONIBLES:\n");
            printf("PRODUCTO                 |PRECIO               |TIEMPO DE ESPERA          |CODIGO|\n");
            node *tempNode = listaProductos;
            while (tempNode->next) {
//        printf("%s,%d,%d,%d\n",tempNode->prod->name,tempNode->prod->price,tempNode->prod->id,tempNode->prod->time);
                printf("|%s                   |", tempNode->prod->name);
                printf("%d                   |", tempNode->prod->price);
                printf("%d                   |", tempNode->prod->time);
                printf("%d       ", tempNode->prod->id);
                printf("\n");
                tempNode = tempNode->next;
            }
            printf("\n");

            //RECORRIENDO LISTA DE PEDIDOS
            printf("PEDIDOS PENDIENTES :\n");
            char *current;
            for (int i = 0; i < pedidosCount; i++) {
                current = pedidos[i];
                printf("%s\n", current);
            }
            printf("\n");


            wait(NULL);
            fclose(productosFilePtr);
            fclose(pedidosFilePtr);
            free(listaProductos);
            // free(tempNode);
            // free(pedidos);
            return 0;
        }
    }
///////////FIN DEL PROCESO PADRE///////////////
    wait(NULL);
}
