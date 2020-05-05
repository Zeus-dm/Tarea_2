#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Nodo.h"

Nodo* crearNodo( void* data){
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->data = data;
    nuevoNodo->next = NULL;
    nuevoNodo->prev = NULL;
    return nuevoNodo;
}

Producto* crearProducto( const char* nombre, const char* marca, const char* tipo , long stock, long precio ){
    Producto* newP = (Producto*)malloc(sizeof(Producto));
    strcpy( newP->Nombre, nombre);
    strcpy( newP->Marca, marca);
    strcpy( newP->Tipo, tipo);
    newP->Precio = precio;
    newP->Stock = stock;
    return newP;
}

