#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "Menu.h"
#include "funMain.h"
#include "CSV.h"
#include "TDA/Mapa.h"
#include "TDA/Nodo.h"
#include "TDA/Lista.h"

#define MAX 50
#define max 20

void MenuArchivo( char* ULT_ARCHIVO, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS );
void subMenuExp( char* ULT_ARCHIVO, Mapa* B_NOMBRES);
void MenuBuscar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS);
void MenuCarrito( Lista* CARRITOS, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS);

void ImportarArchivo( char* ULT_ARCHIVO, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS );
void ExportarArchivo( char* ARCHIVO, Mapa* B_NOMBRES );

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

    char ULT_ARCHIVO[MAX] = "\0" ;

    int opcion=0;

    do{
        char menuPrinc[7][MAX] = {"\tECONO","Opc. Archivo","Agregar Producto","Buscar Producto(s)","Mostrar todos los Productos","Carrito","Salir"};
        opcion = crearMenu( menuPrinc, 7, opcion );

        switch( opcion ){
            case 0:
                MenuArchivo( ULT_ARCHIVO, B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 1:
                system("cls");
                AgregarProducto( B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 2:
                MenuBuscar( B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 3:
                system("cls");
                MostrarTodosProductos( B_NOMBRES);
            break;
            case 4:
                system("cls");
                MenuCarrito( CARRITOS, B_NOMBRES, B_MARCAS, B_TIPOS);
            break;

        }

    }while( opcion != 5);
    return 0;
}

void MenuArchivo( char* ULT_ARCHIVO, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS ){
    int opcion = 0;
    do{
        char menuArc[4][MAX] = {"OPCIONES DE ARCHIVO", "Importar Archivo", "Exportar Archivo", "Atras"};
        opcion = crearMenu( menuArc, 4, opcion);

        switch(opcion){
            case 0:
                system("cls");
                ImportarArchivo( ULT_ARCHIVO, B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
            case 1:
                system("cls");
                subMenuExp( ULT_ARCHIVO, B_NOMBRES);
            break;
        }

    }while( opcion != 2);
}

void MenuBuscar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS){
    int opcion = 0;
    do{
        char menuBus[5][MAX] = {"BUSCAR PRODUCTO(S)", "Buscar por Marca", "Buscar por Tipo", "Buscar por Nombre", "Atras"};
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

void MenuCarrito( Lista* CARRITOS, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS){
    int opcion = 0;
    do{
        char menuCar[4][MAX] = {"CARRITO", "Agregar Producto", "Concretar Compra", "Atras"};
        opcion = crearMenu( menuCar, 4, opcion);

        switch(opcion){
            case 0:
                system("cls");
                AgregarCarrito( CARRITOS, B_NOMBRES);
            break;
            case 1:
                system("cls");
                ConcretarCompra( CARRITOS, B_NOMBRES, B_MARCAS, B_TIPOS);
            break;
        }

    }while( opcion != 2);
}

void subMenuExp( char* ULT_ARCHIVO, Mapa* B_NOMBRES){
    char archivo[MAX];
    if( strcmp( ULT_ARCHIVO, "") == 0){
        printf("\n\t\tEXPORTAR PRODUCTOS\n\n\n");
        printf("\tNombre de archivo(sin .csv): ");
        gets( archivo);
        strcat(archivo, ".csv");
        ExportarArchivo( archivo, B_NOMBRES);
        strcpy( ULT_ARCHIVO, archivo);
        Espera();
    }else{
        int opcion = 0;
        do{
            char menuSubArc[4][MAX] = {"ARCHIVO A EXPORTAR", "Nuevo Archivo"};
            strcpy( menuSubArc[2], ULT_ARCHIVO);
            strcpy( menuSubArc[3], "Atras");
            opcion = crearMenu( menuSubArc, 4, opcion);

            switch(opcion){
                case 0:
                    system("cls");
                    printf("\n\t\tEXPORTAR PRODUCTOS\n\n\n");
                    printf("\tNombre de archivo(sin .csv): ");
                    gets( archivo);
                    strcat(archivo, ".csv");
                    ExportarArchivo( archivo, B_NOMBRES);
                    strcpy( ULT_ARCHIVO, archivo);
                    opcion = 2;
                    Espera();
                break;
                case 1:
                    printf("\n\t\tEXPORTAR PRODUCTOS\n\n\n");
                    ExportarArchivo( ULT_ARCHIVO, B_NOMBRES);
                    opcion = 2;
                    Espera();
                break;
            }
        }while( opcion != 2);
    }
}

//------------------------------------------------------------------------

void ImportarArchivo( char* ULT_ARCHIVO, Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS ){
    long stock = -1, precio = -1;
    char archivo[MAX];

    printf("\n\t\tPRODUCTOS DESDE UN ARCHIVO\n\n\n");
    printf("\tNombre de archivo(sin .csv): ");
    gets( archivo);
    strcat(archivo, ".csv");

    FILE *productos = fopen( archivo, "r");

    if(productos == NULL){
        printf("\n     Archivo NO Existe");
    }else{
        strcpy( ULT_ARCHIVO, archivo);
        char linea[1024];
        printf("\n     Procesando archivo...\n");

        while( fgets( linea, 1023, productos) != NULL ){
            const char* nombre = get_csv_field( linea, 1);
            const char* marca = get_csv_field( linea, 2);
            const char* tipo = get_csv_field( linea, 3);
            stock = atol(get_csv_field( linea, 4));
            precio = atol(get_csv_field( linea, 5));

            Verificar( B_NOMBRES, B_MARCAS, B_TIPOS, nombre, marca, tipo, stock, precio, 0);
        }

        printf("\n     Archivo finalizado\n");
    }
    fclose( productos);
    Espera();
}

void ExportarArchivo( char* ARCHIVO, Mapa* B_NOMBRES ){
    FILE* productos = fopen( ARCHIVO, "w");
    if( productos == NULL){
        printf("\n     ERROR::Archivo no pudo ser creado o sobreescrito");
    }else{
        Producto* auxP = firstMap(B_NOMBRES);
        while( auxP != NULL){
            fprintf(productos,"%s,%s,%s,%ld,%ld\n", auxP->Nombre,auxP->Marca,auxP->Tipo,auxP->Stock,auxP->Precio);
            auxP = nextMap( B_NOMBRES);
        }
        fclose(productos);
        printf("\n     Exportado Correctamente");
    }
}

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
    printf("\n\t\tTODOS LOS PRODUCTOS\n\n");

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
        printf("\n     Producto NO existe");
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

