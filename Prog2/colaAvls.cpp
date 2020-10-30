/*
  Módulo de implementación de TCcolaAvls'.

  Los elementos de tipo 'TColaAvls' son estructuras lineales con
  comportamiento FIFO cuyos elementos son de tipo 'avl'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/colaAvls.h"
#include "../include/avl.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>



// Declaración del tipo 'localizador'
typedef struct nodoColaAvls *localizador;

//struct nodo
struct nodoColaAvls{
  TAvl Avl;
  localizador siguiente;
};

// struct repColaAvls;
struct repColaAvls{
  localizador inicio;
  localizador final;
};

/*
  Devuelve una 'TColaAvls' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls crearColaAvls(){
  TColaAvls res = new repColaAvls;
  res->final = NULL;
  res->inicio = NULL;
  return res;
}

/*
  Encola 'avl' en 'c'.
  Devuelve 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls encolar(TAvl avl, TColaAvls c){ //Inserto al final
  localizador enco = new nodoColaAvls;
  enco->siguiente = NULL;
  enco->Avl = avl;
  if(estaVaciaColaAvls(c)){    
    c->inicio = enco;
    c->final = enco;
  }else{
    c->final->siguiente = enco;
    c->final = enco;
  }
  return c;
}

/*
  Remueve de 'c' el elemento que está en el frente.
  Si estaVaciaColaAvls(c) no hace nada.
  Devuelve 'c'.
  NO libera la memoria del elemento removido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls desencolar(TColaAvls c){ //Elimino al inicio
  if(!estaVaciaColaAvls(c)){
    localizador aDesencolar = c->inicio;
    if(c->inicio == c->final){
      c->inicio = NULL;
      c->final = NULL;
    }
    else
      c->inicio = c->inicio->siguiente;
    delete aDesencolar;
  }
  return c;
}

/*
  Libera la memoria asignada a 'c', pero NO la de sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'c'.
 */
static void libererC(TColaAvls &c){  // FUNCIÓN AUXILIAR para modificar la cola
    localizador aLiberar;
    while (c->inicio != NULL){
		  aLiberar = c->inicio;
		  c->inicio = c->inicio->siguiente;
		  delete aLiberar;
		}
	delete c;		
}
    
void liberarColaAvls(TColaAvls c){ //función auxiliar, el void no modifica la cola
  libererC(c);
}

/*
  Devuelve 'true' si y solo si 'c' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaColaAvls(TColaAvls c){
  return c->inicio == NULL; //alcanza solo con c == NULL ???
}

/*
  Devuelve el elemento que está en el frente de 'c'.
  Precondición: ! estaVaciaColaAvls(c);
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl frente(TColaAvls c){
  assert(!estaVaciaColaAvls(c));
  return c->inicio->Avl;
}
