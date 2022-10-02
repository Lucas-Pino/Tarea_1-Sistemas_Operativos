//
// Created by Lucas Pino on 25-09-22.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"



void initList(node* head){
    head = NULL;
    head = (node *) malloc(sizeof(node));
    if (head == NULL) {
        exit(-1);
    }

    head->prod = NULL;
    head->next = NULL;
}



void push(node ** head, producto* val) {
    node* new_node;
    new_node = (node *)malloc(sizeof(node));

    producto *prodTemp;
    prodTemp = (producto*)malloc(sizeof(producto));



    *prodTemp=*val;

    new_node->prod=prodTemp;
    new_node->next = *head;
    *head = new_node;
}

int getId(node* head, char* productName){

    node *tempNode = head;

    while (tempNode->next) {
        if(!strcmp(productName,tempNode->prod->name)){
            return tempNode->prod->id;
        } else tempNode = tempNode->next;
    }

}

int getTime(node* head, char* productName){

    node *tempNode = head;

    while (tempNode->next) {
        if(!strcmp(productName,tempNode->prod->name)){
            return tempNode->prod->id;
        } else tempNode = tempNode->next;
    }

}
int getPrice(node* head, char* productName){

    node *tempNode = head;

    while (tempNode->next) {
        if(!strcmp(productName,tempNode->prod->name)){
            return tempNode->prod->id;
        } else tempNode = tempNode->next;
    }

}

char* getNextPedido(char** Pedidos, int n){
    char * tempPedido;
//    for (size_t i = 0; i < sizeof(Pedidos) / sizeof(Pedidos[0]); i++)
    for (size_t i = 0; i < n;i++)
    {
        if(Pedidos[i]!=NULL){
            tempPedido=Pedidos[i];
            Pedidos[i]=NULL;
            return  tempPedido;
        }
    }

}