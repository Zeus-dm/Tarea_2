#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "funMain.h"
#include "TDA/Mapa.h"
#include "TDA/Nodo.h"
#include "TDA/Lista.h"

#define ENTER 13
#define ESC 27
#define MAX 50

//------------------------------------------------------------

void Espera(){
    printf("\n\n ->\t Atras\n");
    do{
        unsigned char tecla = getch();
        if( (tecla == ENTER) || tecla == ESC ){
            break;
        }
    }while(1);
    system("cls");
}

//------------------------------------------------------------

void* stringSearchListProduct( Lista* L, const char* ID){
    Producto* auxP = firstL( L );
    while( auxP != NULL){
        if( strcmp( auxP->Nombre, ID) == 0 ){
            return auxP;
        }
        auxP = nextL( L );
    }
    return NULL;
}

void InsertMapaNombres( Mapa* B_NOMBRES, Producto* product ){
    Producto* auxP = searchMap( B_NOMBRES, product->Nombre);
    if( auxP == NULL ){
        insertMap( B_NOMBRES, product->Nombre, product );
    }else{
        auxP->Stock += product->Stock;
    }
}

void InsertMapaLista ( Mapa* MAPA, Producto* product , char* key ){
    Lista* auxL = searchMap( MAPA, key);
    if( auxL == NULL ){
        Lista* newL = crearLista();
        pushBackL( newL, product );
        insertMap( MAPA, key, newL );
    }else{
        Producto* auxP = stringSearchListProduct( auxL, product->Nombre);
        if( auxP == NULL ){
            pushBackL( auxL, product);
        }
    }
}

void Verificar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS, char* nombre, char* marca, char* tipo, long stock, long precio, int flag){
    if( (strcmp( nombre, "")!=0) && (strcmp( marca, "")!=0) && (strcmp( tipo, "")!=0) && (stock != -1) && (precio != -1) ){
        Producto* product = crearProducto( nombre, marca, tipo, stock, precio);
        InsertMapaNombres( B_NOMBRES, product);
        InsertMapaLista( B_MARCAS, product, product->Marca );
        InsertMapaLista( B_TIPOS, product, product->Tipo );
        if( flag ){
            printf("\n     Producto Ingresado Correctamente");
        }
    }else{
        if( flag ){
            printf("\n     ERROR::Datos Incorrectos");
        }
    }
}

//------------------------------------------------------------

void DeleteMapaNombre( Mapa* B_NOMBRES, Producto* product ){
    deleteKeyMap( B_NOMBRES, product->Nombre);
}

void DeleteMapaList( Mapa* MAPA, char* key, Producto* product ){
    Lista* auxL = searchMap( MAPA, key);
    stringSearchListProduct( auxL, product->Nombre);
    deleteCurrentL( auxL );
    if( auxL->total == 0){
        deleteL( auxL);
        deleteKeyMap( MAPA, key);
    }
}

//------------------------------------------------------------

Carritos* crearCarritos( char* nombreC , Lista* lista){
    Carritos* newC = (Carritos*)malloc( sizeof(Carritos));
    strcpy( newC->NombreC, nombreC);
    newC->Productos = lista;
    return newC;
}

void* stringSearchListCarrito( Lista* L, const char* ID){
    Carritos* auxC = firstL( L );
    while( auxC != NULL ){
        if( strcmp( auxC->NombreC, ID) == 0){
            return auxC;
        }
        auxC = nextL( L );
    }
    return NULL;
}

void InsertListCarritos( Lista* CARRITOS, Mapa* B_NOMBRES, char* N_carrito, char* N_producto ){
    Producto* auxP = searchMap( B_NOMBRES, N_producto);
    if( auxP == NULL ){
        printf("\n     El Producto NO Existe");
    }else{
        Carritos* auxC = stringSearchListCarrito( CARRITOS, N_carrito);
        if( auxC ==  NULL ){
            Lista* newL = crearLista();
            pushBackL( newL, auxP);
            Carritos* newC = crearCarritos( N_carrito, newL);
            pushBackL( CARRITOS, newC);
        }else{
            Lista* auxL = auxC->Productos;
            pushBackL( auxL, auxP);
        }
    }
}

void ConcretarCarrito( Lista* CARRITOS, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS, char* N_carrito){
    long sumaT = 0;
    Carritos* auxC = stringSearchListCarrito( CARRITOS, N_carrito);
    if( auxC == NULL ){
        printf("\n     El Carrito NO Existe");
    }else{
        Lista* auxL = auxC->Productos;
        Producto* auxP = firstL( auxL);
        while( auxP != NULL){
            Producto* verP = searchMap( B_NOMBRES, auxP->Nombre);
            if( verP != NULL){
                sumaT += auxP->Precio;
                auxP->Stock--;
                if( auxP->Stock == 0){
                    DeleteMapaNombre( B_NOMBRES, auxP);
                    DeleteMapaList( B_MARCAS, auxP->Marca, auxP);
                    DeleteMapaList( B_TIPOS, auxP->Tipo, auxP);
                }
            }
            auxP = nextL( auxL);
        }
        deleteL( auxL );
        deleteCurrentL( CARRITOS);
        printf("\n     Total a pagar : %ld", sumaT);
    }
}

















