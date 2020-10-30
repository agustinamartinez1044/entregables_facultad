/*
  Módulo de implementación de 'TCola'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/listaInfo.h"
#include "../include/colaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repCola {
	TLista lista ;
} ;

TCola crearCola()  {
         TCola colaNueva = new repCola ;
         (colaNueva->lista) = crearLista () ;
      return colaNueva ;
}

bool esVaciaCola(TCola cola) {
	 return longitud(cola->lista) == 0 ;
}

TCola encolar(info_t nuevo, TCola cola) {
	     if (longitud(cola->lista) < MAX) {
	         cola->lista = insertar(longitud(cola->lista)+1, nuevo, cola->lista) ;
	     }
	   return cola ;
}

info_t frente(TCola cola) {
	      assert(!esVaciaCola(cola)) ;
	   return infoLista(1, cola->lista) ;
}

TCola desencolar(TCola cola) {
	     assert(!esVaciaCola(cola)) ;
	     cola->lista = remover(1,cola->lista) ;
	  return cola ;
}

