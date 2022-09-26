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

    //variables auxiliares
    char line[256];
    char* token;

    //lista enlazada de productos disponibles, cada nodo contiene una struct 'producto'
    node * listaProductos;
    initList(listaProductos);

    char* pedidos[MAXPEDIDOS];

    //Creando un producto auxiliar
    producto* tempProd;
    if((tempProd = (producto *)malloc(sizeof(producto))) == NULL){
        return 1;
    }

    //CONTADORES PARA SABER CUANTOS PRODUCTOS HAY EN CADA ARCHIVO
    size_t productosCount=0;
    size_t pedidosCount=0;

    //ABRIENDO ARCHIVOS
    FILE *pedidosFilePtr;
    FILE *productosFilePtr;

    pedidosFilePtr = fopen(pedidosFile,"r");
    if (NULL == pedidosFilePtr) {
        printf("file can't be opened \n");
    }
    productosFilePtr = fopen(productosFile, "r");
    if (NULL == productosFilePtr) {
        printf("file can't be opened \n");
    }

//Moviendo los productos a mi lista enlazada de productos
    while (fgets(line,sizeof(line),productosFilePtr)){

        //NAME
        token= strtok(line,",");
        tempProd->name= malloc(strlen(token)+1);
        strcpy(tempProd->name,token);

        //PRECIO
        token= strtok(NULL,",");
        tempProd->price= atoi(token);

        //ID
        token= strtok(NULL,",");
        tempProd->id= atoi(token);

        //TIME
        token= strtok(NULL,",");
        tempProd->time= atoi(token);

        push(&listaProductos, tempProd);

    }
//    Agregando pedidos a lista de pedidos
    fgets(line,sizeof(line),pedidosFilePtr);
    token= strtok(line,",");
    for (pedidosCount;token;pedidosCount++){
        pedidos[pedidosCount]= malloc(strlen(token)+1);
        strcpy(pedidos[pedidosCount],token);
        token= strtok(NULL,",");
    }

    //RECORRIENDO LISTA DE PEDIDOS
    char* current;
    for (int i=0;i<pedidosCount;i++){
        current=pedidos[i];
        printf("%s\n",current);
    }






//    Recorriendo la lista enlazada
    node* tempNode=listaProductos;
    while (tempNode->next){
        printf("%s,%d,%d,%d\n",tempNode->prod->name,tempNode->prod->price,tempNode->prod->id,tempNode->prod->time);
        tempNode=tempNode->next;
    }

    pid_t child_a, child_b;
    pid_t parentPid=getpid();

    child_a = fork();

    if (child_a == 0) {
        printf("predicted PID: %d\n",parentPid+1);
        printf("this is child_A PID: %d\n",getpid());
    } else {
        child_b = fork();

        if (child_b == 0) {
            /* Child B code */
            printf("predicted PID: %d\n",parentPid+2);
            printf("this is child_B PID: %d\n",getpid());
        } else {
            /* Parent Code */
            printf("predicted PID: %d\n",parentPid);
            printf("this is the PARENT PID: %d\n",getpid());
        }
    }



//
////   Proceses
////   Cajero
//    if (id==0){
//
//    }
//
////    Repartidor 1
//    if (id==0){
//
//    }
//
////  Repartidor 2
//    if (id==0){
//    }
//

// limpiando basura?
    wait(NULL);
    fclose(productosFilePtr);
    fclose(pedidosFilePtr);
    free(listaProductos);
    // free(tempNode);
    // free(pedidos);
    return 0;
}
