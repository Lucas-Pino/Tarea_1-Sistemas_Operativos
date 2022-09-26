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