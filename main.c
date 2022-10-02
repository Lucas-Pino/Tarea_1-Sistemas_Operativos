#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "auxFuncs.h"
#include "linkedList.h"

#define IS_CHILD 0
#define pedidosFile "/Users/lucas/School/Sistemas operativos/Tarea_1/pedidos.txt"
#define productosFile "/Users/lucas/School/Sistemas operativos/Tarea_1/productos_disponibles.txt"
#define MAXPEDIDOS 100
#define YES 1
#define NO 0

#define DONE 888
#define WORKING 666
#define STRLEN


int main() {
    printf("\n");

    //creando los pipes

    int data1[2];
    int data2[2];
    pipe(data1);
    pipe(data2);

    //CREANDO LOS PROCESOS HIJOS
    // EL CAJERO SERA EL PROCESO PRINCIPAL
    pid_t repartidor1;
    pid_t repartidor2;
    repartidor1=fork();
    if (repartidor1 < 0){ //Ocurrio un error
        printf("Fallo el fork child1");
        return 1;
    }

///////////////////////// PROCESO HIJO 1/////////////////
    else if(repartidor1==IS_CHILD){


        size_t pedidosCount;

        int pedido;
        read(data1[0], &pedido, sizeof(int));
        printf("\n child 1 WAITING for %d \n", pedido);
        sleep(1);
        printf("\n child 1 FINISHED pedido %d \n", pedido);
        pedido=DONE;
        sleep(1);
        write(data1[1], DONE, sizeof(int ));
    }


    else{
        repartidor2=fork();
        if (repartidor2 < 0){ //Ocurrio un error
            printf("Fallo el fork child 2");
            return 1;
        }
////////////////////////// PROCESO HIJO 2/////////////////
        else if (repartidor2==IS_CHILD){
            int pedido;
            read(data2[0], &pedido, sizeof(int));
            printf("\n child 2 waiting for %d \n", pedido);
            sleep(2);
            printf("\n child 2 FINISHED pedido %d \n", pedido);
            pedido=DONE;
            sleep(2);
            write(data2[1], &pedido, sizeof(int ));
        } else {
///////////////// PROCESO PADRE//////////////////////////

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

            for (int i = 0; i < pedidosCount; i++) {
                printf("%s\n", pedidos[i]);

            }
            printf("\n");

            //TESTING THE PIPES
            int x=888;
            int x1=999;
            //enviando los pedidos por el pipe

            write(data1[1], &x, sizeof(int));
            write(data1[1], &x1, sizeof(int));

            int p1_status=DONE;
            int p2_status=DONE;
            int prod1;
            int prod2;
            int finished=0;
            int pedidosDone=0;


            char temp[256];
            strcpy(temp,pedidos[2]);

            prod1=getId(listaProductos,pedidos[2]);
            printf("get id %d", prod1);

            write(data1[1], &prod1, sizeof(int));

            //SCHEDULER PART
            for (int i = 0; i < pedidosCount; i++) {
                printf("%s\n", pedidos[i]);
//                if(pedidos)
            }
            while(pedidosDone!=pedidosCount){
//                read(data1[0], &p1_status, sizeof(int));
                if(p1_status==DONE){
                    prod1=getId(listaProductos,getNextPedido(pedidos,MAXPEDIDOS));
                    printf("sent prod %d to child 1 \n", prod1);
                    write(data1[1], &prod1, sizeof(int));
                    pedidosDone++;
                    p1_status=WORKING;
                }
//                read(data1[0], &p2_status, sizeof(int));
                if(p2_status==DONE){
                    prod2=getId(listaProductos,getNextPedido(pedidos,MAXPEDIDOS));
                    printf("sent prod %d to child 2 \n", prod2);
                    write(data2[1], &prod2, sizeof(int));
                    pedidosDone++;
                    p2_status=WORKING;
                }
                sleep(1);
                read(data1[0], &p1_status, sizeof(int));

                read(data2[0], &p2_status, sizeof(int));
                sleep(1);
            }


            printf("DONE ALL \n");




            wait(NULL);
            close(data1[0]);
            close(data1[1]);
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
