#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->current = lista->head;
    lista->tail = NULL;
    return lista;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return (list->current->data);
}

void * nextList(List * list) {
    if (list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return (list->current->data);
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return (list->current->data);
}

void * prevList(List * list) {
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return (list->current->data);
}

void pushFront(List * list, void * data) {
    Node * nuevo = createNode(data);
    if (list->head == NULL){
        list->head = nuevo;
        list->tail = nuevo;
    }
    else{
        nuevo->next = list->head;
        list->head->prev = nuevo;
        list->head = nuevo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * nuevo = createNode(data);
    
    //si no hay más nodos
    if (list->head == NULL){
        list->head = nuevo;
        list->tail = nuevo;
    }
    //si hay solo uno
    else if (list->head->next == NULL){
        list->head->next = nuevo;
        nuevo->prev = list->head;
        list->tail = nuevo;
    }
    //si el current esta en el tail
    else if (list->current == list->tail){
        list->tail->next = nuevo;
        nuevo->prev = list->tail;
        list->tail = nuevo;
    }
    //si hay más de un nodo y el current no es el tail
    else{
        Node* aux = list->current->next;
        list->current->next = nuevo;
        nuevo->prev = list->current;
        nuevo->next = aux;
        aux->prev = nuevo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void * elemento = list->current->data;
    //si el current es el head
    if (list->current == list->head){
        list->head = list->head->next;
        list->head->prev = NULL;
        free(list->current);
        list->current = list->head;
    }
    //si el current es el tail
    else if (list->current == list->tail){
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(list->current);
        list->current = list->tail;
    }
    //si el current es otro nodo
    else{
        Node* aux = list->current->next; //el current se volvera el auxiliar despues del free
        list->current->prev->next = aux;
        aux->prev = list->current->prev;
        free(list->current);
        list->current = aux;        
    }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
