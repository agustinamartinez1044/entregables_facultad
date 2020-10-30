/*
  Módulo de implementación de 'TIterador'.

  Los elementos de tipo 'TIterador' son estructuras para recorrer colecciones
  de elementos de tipo 'nat'.
  Tiene implcícita una posición actual.
  La posición no está definida si la colección es vacía o si se avanza cuando
  la posición es la última.

  La vida de un 'TIterador' tiene dos fases: en la primera se le puede agregar
  elementos pero no se puede recorrer; luego de que se reinicia se puede
  recorrer tantas veces como sea pero no se puede agregar elementos.

  Seudocódigo de una recorrida de un iterador:
  reiniciar
  mientras la posición actual está definida
    procesar el elemento definido por la posición actual
    avanzar

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */


#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h> 
#include <stdlib.h>

// Representación de 'TIterador',
// struct repIterador;
typedef struct nodoIt *PNodoIt;
struct nodoIt{
  nat elem;
  PNodoIt sig;
};
struct repIterador{
    PNodoIt inicio, fin, actual;
    bool bloqueado;
};

/*
  Crea un 'TIterador' vacío (sin elementos) cuya posición actual no está
  definida.
  Se le puede agregar elementos.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador crearIterador(){
    TIterador res = new repIterador;
    res->actual = res->inicio = res->fin = NULL;
    res->bloqueado = false;
    return res;
}

/*
  Agrega 'elem' al final de 'iter' si y solo si nunca se reinicio.
  Devuelve 'iter'.
  La posición actual sigue indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador agregarAIterador(nat elem, TIterador iter){
    if (!iter->bloqueado){
        nodoIt *nuevo = new nodoIt;
        nuevo->elem = elem;
        nuevo->sig = NULL;
        if (iter->fin != NULL)
            iter->fin->sig = nuevo;
        else
            iter->inicio = nuevo;
        iter->fin = nuevo;
    }
    return iter;
}
/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  Devuelve 'iter'.
  No se podrán agregar más elementos (aunque no hubiera ninguno).
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador reiniciarIterador(TIterador iter){
    if (iter->inicio != NULL){
        iter->actual = iter->inicio;
        iter->bloqueado = true;
    }
    return iter;
}

/*
  Avanza la posición actual de 'iter' hacia el siguiente si y solo si'
  estaDefinidaActual(iter).
  Devuelve 'iter'.
  Si ! haySiguienteEnIter(iter) la posición actual queda indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador avanzarIterador(TIterador iter){
    if(iter->actual != NULL){
      if(iter->actual->sig !=NULL)
        iter->actual = iter->actual->sig;
      else 
        iter->actual = NULL;
    }
    return iter;
}

/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat actualEnIterador(TIterador iter){
    assert(estaDefinidaActual(iter));
    return (iter->actual->elem);
}

/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaDefinidaActual(TIterador iter){
    return (iter->actual != NULL);
}

/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'iter'.
 */
void liberarIterador(TIterador iter){
    iter->actual = iter->inicio;
    while (estaDefinidaActual(iter)) {
    nodoIt *a_borrar = iter->actual;
    iter->actual = iter->actual->sig;
    delete a_borrar;
  }
  delete iter;
} 
