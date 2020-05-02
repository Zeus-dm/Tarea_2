#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "TDA/Mapa.h"
#include "TDA/Nodo.h"
#include "TDA/Lista.h"

#define ENTER 13
#define ESC 27
#define MAX 50


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























