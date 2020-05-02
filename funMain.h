#ifndef FUNMAIN_H
#define FUNMAIN_H

#include "TDA/Mapa.h"
#include "TDA/Nodo.h"
#include "TDA/Lista.h"

/** Escribe una opcion(Atas), hasta que el usuario aprete enter o esc */
void Espera();

//---------------------------------------------------------------------

/** retorna el producto con el nombre  */
void* stringSearchListProduct( Lista* L, const char* ID);

/** Agrega el producto al mapa nombres */
void InsertMapaNombres( Mapa* B_NOMBRES, Producto* product );

/** Agrega el producto a un lista y luego al mapa */
void InsertMapaLista ( Mapa* MAPA, Producto* product , char* key );

/** Verifica si los datos son correctos */
void Verificar( Mapa* B_NOMBRES, Mapa* B_MARCAS, Mapa* B_TIPOS, char* nombre, char* marca, char* tipo, long stock, long precio, int flag);

//---------------------------------------------------------------------


#endif // FUNMAIN_H
