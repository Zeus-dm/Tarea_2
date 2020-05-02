#ifndef NODO_H
#define NODO_H

#define MAX 50

typedef struct Nodito{
    void* data;
    struct Nodo* next;
    struct Nodo* prev;
}Nodo;

typedef struct{
    char Nombre[MAX];
    char Marca[MAX];
    char Tipo[MAX];
    long Stock;
    long Precio;
}Producto;


/** crea un nodo */
Nodo* crearNodo( void* data);

/** genera un Producto */
Producto* crearProducto( char* nombre, char* marca, char* tipo , long stock, long precio );


#endif // NODO_H
