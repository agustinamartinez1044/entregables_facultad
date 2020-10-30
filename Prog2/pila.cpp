/*
  Módulo de implementación de 'TPila'.

  Los elementos de tipo 'TPila' son estructuras lineal acotadas con
  comportamiento LIFO cuyos elementos son naturales.

  La cantidad de elementos que puede mantener se establece en el parámetro
  de 'crearPila'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/pila.h"
#include "../include/info.h"

#include <assert.h>


// struct repPila;
struct repPila{
    int *datos;
    int tope;
    int cantidad;
};

/*
  Devuelve una 'TPila' vacía (sin elementos) que puede tener hasta 'tamanio'
  elementos.
  Precondición: tamanio > 0.
 */
TPila crearPila(nat tamanio) {
  assert(tamanio > 0);
  TPila p = new repPila;
  p->tope = 0;
  p->datos = new int [tamanio];
  p->cantidad = tamanio;
  return p;
}

/*
  Apila 'num' en 'p'.
  Devuelve 'p'.
  Si estaLenaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila apilar(nat num, TPila p){
  if(!estaLlenaPila(p)){
    p->datos[p->tope] = num;
    p->tope++;      
  }
  return p;
}

/*
  Remueve de 'p' el elemento que está en la cima.
  Devuelve 'p'.
  Si estaVaciaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila desapilar(TPila p){
  if(!estaVaciaPila(p)){
    p->tope--;
  }
  return p;
}

/*
  Libera la memoria asignada a 'p'.
 */
void liberarPila(TPila p){
  delete[] p->datos;
  p->tope = 0;
  delete p;

}

/*
  Devuelve 'true' si y solo si 'p' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaPila(TPila p){
  return (p->tope == 0);
}

/*
  Devuelve 'true' si y solo si la cantidad de elementos en 'p' es 'tamanio'
  (siendo 'tamanio' el valor del parámetro con que fue creada 'p').
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaLlenaPila(TPila p){
  return (p->tope == p->cantidad);
}

/*
  Devuelve el elemento que está en la cima de 'p'.
  Precondición: ! estaVaciaPila(p);
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cima(TPila p){
  assert(!estaVaciaPila(p));
  return(p->datos[p->tope -1]);
}

