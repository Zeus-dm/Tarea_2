#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "Menu.h"
#include "funMain.h"
#include "TDA/Mapa.h"
#include "TDA/Nodo.h"
#include "TDA/Lista.h"

#define MAX 50
#define max 20

void MenuBuscar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS);

void AgregarProducto( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS);
void MostrarTodosProductos( Mapa* B_NOMBRES );

void BuscarNombre( Mapa* B_NOMBRES );
void BuscarLista( Mapa* MAPA, int flag );

void AgregarCarrito( Lista* CARRITOS, Mapa* B_NOMBRES );
void ConcretarCompra( Lista* CARRITOS, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS);

int main(void){
    Mapa* B_NOMBRES = crearMapa( max);
    Mapa* B_MARCAS = crearMapa( max);
    Mapa* B_TIPOS = crearMapa( max);
    Lista* CARRITOS = crearLista();

    int opcion=0;

    do{
        char menuPrinc[9][MAX] = {"\tEcono","Importar Productos","Exportar Productos","Agregar Producto","Buscar Producto(s)","Mostrar todos los Productos","Agregar Producto al Carrito","Concretar Compra","Salir"};
        opcion = crearMenu( menuPrinc, 9, opcion );

        switch( opcion ){
            case 0:
            break;
            case 1:
            break;
            case 2:
                system("cls");
                AgregarProducto( B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 3:
                system("cls");
                MenuBuscar( B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 4:
                system("cls");
                MostrarTodosProductos( B_NOMBRES);
            break;
            case 5:
                system("cls");
                AgregarCarrito( CARRITOS, B_NOMBRES);
            break;
            case 6:
                system("cls");
                ConcretarCompra( CARRITOS, B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
        }

    }while( opcion != 7);
    return 0;
}

void MenuBuscar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS){
    int opcion = 0;
    do{
        char menuBus[5][MAX] = {"\tBuscar Producto(s)", "Buscar por Marca", "Buscar por Tipo", "Buscar por Nombre", "Atras"};
        opcion = crearMenu( menuBus, 5, opcion);

        switch(opcion){
            case 0:
                system("cls");
                BuscarLista( B_MARCAS, 0);
            break;
            case 1:
                system("cls");
                BuscarLista( B_TIPOS, 1);
            break;
            case 2:
                system("cls");
                BuscarNombre( B_NOMBRES );
            break;
        }


    }while( opcion != 3);
}

//------------------------------------------------------------------------

void AgregarProducto( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS ){
    char nombre[MAX], marca[MAX], tipo[MAX], ex[MAX]="";
    long stock = -1 , precio = -1;
    printf("\n\t\tAGREGAR PRODUCTO\n\n\n");
    printf("\t Nombre     : ");
    gets(nombre);
    printf("\t Marca      : ");
    gets(marca);
    printf("\t Tipo       : ");
    gets(tipo);
    printf("\t Stock      : ");
    scanf("%ld", &stock);
    printf("\t Precio     : ");
    scanf("%ld", &precio);
    gets(ex);

    if( strcmp( ex, "") == 0){
        Verificar( B_NOMBRES, B_MARCAS, B_TIPOS, nombre, marca, tipo, stock, precio, 1);
    }else{
        printf("\n     ERROR::Datos Incorrectos");
    }

    Espera();
}

void MostrarTodosProductos( Mapa* B_NOMBRES ){
    Producto* product = firstMap( B_NOMBRES);
    if( product == NULL){
        printf("\n\t No existen productos actualmente");
    }else{
        while( product != NULL){
            printf("\n\t----------------------");
            printf("\n\t Nombre : %s", product->Nombre);
            printf("\n\t Marca  : %s", product->Marca);
            printf("\n\t Tipo   : %s", product->Tipo);
            printf("\n\t Stock  : %ld", product->Stock);
            printf("\n\t Precio : %ld", product->Precio);
            product = nextMap( B_NOMBRES);
        }
        printf("\n\t----------------------");
    }

    Espera();
}

//------------------------------------------------------------------------

void BuscarNombre( Mapa* B_NOMBRES ){
    char nombre[MAX];
    printf("\n\t\tBUSCAR PRODUCTO POR NOMBRE\n\n\n");
    printf("\t Nombre     : ");
    gets(nombre);

    Producto* product = searchMap( B_NOMBRES, nombre);
    if( product == NULL ){
        printf("\n     El producto NO existe");
    }else{
        printf("\n\t----------------------");
        printf("\n\t Nombre : %s", product->Nombre);
        printf("\n\t Marca  : %s", product->Marca);
        printf("\n\t Tipo   : %s", product->Tipo);
        printf("\n\t Stock  : %ld", product->Stock);
        printf("\n\t Precio : %ld", product->Precio);
        printf("\n\t----------------------");
    }

    Espera();
}

void BuscarLista( Mapa* MAPA, int flag ){
    char key[MAX];
    if( flag == 0){
        printf("\n\t\tBUSCAR PRODUCTOS POR MARCA\n\n\n");
        printf("\t Marca      : ");
    }else{
        printf("\n\t\tBUSCAR PRODUCTOS POR TIPO\n\n\n");
        printf("\t Tipo       : ");
    }
    gets( key );

    Lista* listProd = searchMap( MAPA, key);
    if( listProd == NULL ){
        if( flag == 0){
            printf("\n     Productos de la marca %s NO existen", key);
        }else{
            printf("\n     Productos del tipo %s NO existen", key);
        }
    }else{
        Producto* product = firstL( listProd );
        while( product != NULL ){
            printf("\n\t----------------------");
            printf("\n\t Nombre : %s", product->Nombre);
            printf("\n\t Marca  : %s", product->Marca);
            printf("\n\t Tipo   : %s", product->Tipo);
            printf("\n\t Stock  : %ld", product->Stock);
            printf("\n\t Precio : %ld", product->Precio);
            product = nextL( listProd );
        }
        printf("\n\t----------------------");
    }

    Espera();
}

//------------------------------------------------------------------------

void AgregarCarrito( Lista* CARRITOS, Mapa* B_NOMBRES ){
    char N_carrito[MAX], N_producto[MAX];
    printf("\n\t\tAGREGAR PRODUCTO AL CARRITO\n\n\n");
    printf("\t Nombre del Carrito   : ");
    gets(N_carrito);
    printf("\t Nombre del Producto  : ");
    gets(N_producto);

    InsertListCarritos( CARRITOS, B_NOMBRES, N_carrito, N_producto);

    Espera();
}

void ConcretarCompra( Lista* CARRITOS, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS){
    char N_carrito[MAX];
    printf("\n\t\tCONCRETAR COMPRA\n\n\n");
    printf("\t Nombre del Carrito   : ");
    gets(N_carrito);

    ConcretarCarrito( CARRITOS, B_NOMBRES, B_MARCAS, B_TIPOS, N_carrito);

    Espera();
}

