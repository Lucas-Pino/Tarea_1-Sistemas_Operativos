//
// Created by Lucas Pino on 25-09-22.
//

#ifndef TAREA_1_LINKEDLIST_H
#define TAREA_1_LINKEDLIST_H

#endif //TAREA_1_LINKEDLIST_H

//TIPO DE DATO DEL PRODUCTO
typedef struct producto{
    char* name;
    int price;
    int id;
    int time;
}producto;

//DEFINICION DEL NODO PARA LA LISTA ENLAZADA
typedef struct node {
    producto* prod;
    struct node* next;
} node;

void initList(node* head);
void push(node ** head, producto* val);
int getId(node* head, char* productName);
int getTime(node* head, char* productName);
int getPrice(node* head, char* productName);
char* getNextPedido(char** Pedidos, int n);
