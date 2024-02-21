#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char comida[15];
    struct Nodo* siguiente;
    struct Nodo* anterior;    
} Nodo;

 typedef struct MiLista
 {
     Nodo* head;
     Nodo* tail;
     Nodo* current;
 }MiLista;

void AddHead(MiLista* Lista, char* comida)
{
    Nodo* nuevo= (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->comida,comida);
    if(Lista->head==NULL)
    {
        Lista->tail=nuevo;
        nuevo->siguiente=NULL;
        nuevo->anterior=NULL;
    }
    else
    {
        nuevo->siguiente=Lista->head;
        nuevo->siguiente->anterior=nuevo;
    }
    Lista->head=nuevo;
}

void AddTail(MiLista* Lista, char* comida) 
{
    Nodo* nuevo= (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->comida,comida);
    if(Lista->tail==NULL)
    {
        Lista->head=nuevo;
        nuevo->siguiente=NULL;
        nuevo->anterior=NULL;
    }
    else
    {
        nuevo->anterior=Lista->tail;
        Lista->tail->siguiente=nuevo;
        nuevo->siguiente=NULL;
    }
    Lista->tail=nuevo;
}

void AddPosicion(MiLista *Lista, int posicion, char *comida) 
{
    if (posicion <= 0) {
        printf("La posicion debe ser un numero positivo.\n");
        return;
    }
    if (posicion == 1) {
        AddHead(Lista, comida);
        return;
    }
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->comida,comida);
    Nodo *temp = Lista->head;
    for (int i = 1; i < posicion - 1 && temp != NULL; i++) {
        temp = temp->siguiente;
    }
    if (temp == NULL) {
        printf("La posicion no existe.\n");
        return;
    }
    nuevo->siguiente = temp->siguiente;
    nuevo->anterior= temp->anterior->siguiente;
    temp->siguiente = nuevo;
    nuevo->siguiente->anterior= nuevo;
}    
void BorrarNodo(MiLista *Lista, char *comida) {
    if (Lista->head == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *temp = Lista->head;
    Nodo *anterior = NULL;

    while (temp != NULL) {
        if (strcmp(temp->comida, comida) == 0) {
            if (anterior == NULL) {
                Lista->head = temp->siguiente;
            } else {
                anterior->siguiente = temp->siguiente;
                anterior->anterior = temp->anterior;
            }
            free(temp);
            return;
        }
        anterior = temp;
        temp = temp->siguiente;
    }
    printf("El dato '%s' no se encontró en la lista.\n", comida);
}

void LiberarLista(MiLista* Lista) 
{
    Nodo* actual = Lista->head;
    Nodo* siguiente=NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    Lista->head = NULL;
}

void ImprimirLista(MiLista* Lista) 
{
    Nodo *temp = Lista->head;
    while (temp != NULL) {
        printf("%s -> ", temp->comida);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}

int main() {
    MiLista lista;
    lista.head= NULL;
    lista.tail= NULL;
    lista.current= NULL;

    AddHead(&lista, "Ramen");
    AddTail(&lista,"Sopes");
    AddHead(&lista,"Burritos");
    AddPosicion(&lista,3,"Tacos");
    AddPosicion(&lista,3,"Sopa");
    AddHead(&lista,"Onigiris");
    BorrarNodo(&lista,"Ramen");
    BorrarNodo(&lista,"Tacos");
    BorrarNodo(&lista,"Onigiris");
    ImprimirLista(&lista);
    LiberarLista(&lista);
    return 0;
}