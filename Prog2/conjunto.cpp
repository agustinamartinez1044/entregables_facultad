/*
  Módulo de implementación de 'TConjunto'.

  Los elementos de tipo 'TConjunto' son conjuntos de elementos de tipo 'nat'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/conjunto.h"
#include "../include/colaAvls.h"
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// struct repConjunto
struct repConjunto{
  TAvl avl;
};

/*
  Devuelve un 'TConjunto' vacío (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TConjunto crearConjunto(){
  TConjunto resultado = new repConjunto;
  resultado->avl = crearAvl();
  return resultado;
}

/*
  Devuelve un 'TConjunto' cuyo único elemento es 'elem'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TConjunto singleton(nat elem){
  TConjunto res = crearConjunto();
  res->avl = insertarEnAvl(elem,res->avl); 
  return res; 
}

/*
  Devuelve un 'TConjunto' con los elementos que pertenecen a 'c1' o 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n),
  siendo  'n' la cantidad de elementos del 'TConjunto' resultado.
 */
TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
  TConjunto conjuntoResultado = crearConjunto();
 
 /* 
 /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  CASOS QUE RESUELVE DE MÁS ////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////
  if(estaVacioConjunto(c1) && estaVacioConjunto(c2)){
    conjuntoResultado = NULL;
    return conjuntoResultado ;
  }
  else if (estaVacioConjunto(c1)){
    TIterador avl2 = iteradorDeConjunto(c2);
    avl2 = reiniciarIterador(avl2);
    while(estaDefinidaActual(avl2)){
      conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl2), conjuntoResultado->avl );
			avanzarIterador(avl2);
    }
    liberarIterador(avl2);    
  }

  else if (estaVacioConjunto(c2)){
    TIterador avl1 = iteradorDeConjunto(c1);
    avl1 = reiniciarIterador(avl1);
    while(estaDefinidaActual(avl1)){
      conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			avanzarIterador(avl1);
    }
    liberarIterador(avl1);         
  }

  else { */ 
  ////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////

    TIterador avl1 = iteradorDeConjunto(c1);
    TIterador avl2 = iteradorDeConjunto(c2);
    avl1 = reiniciarIterador(avl1);
    avl2 = reiniciarIterador(avl2);
    while(estaDefinidaActual(avl1) && estaDefinidaActual(avl2) ) {
      
		  if(actualEnIterador(avl1) < actualEnIterador(avl2)) {
        conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			  avanzarIterador(avl1);
      }
      else if (actualEnIterador(avl1) > actualEnIterador(avl2) ){
			  conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl2), conjuntoResultado->avl );
			  avanzarIterador(avl2);
		  }        
		  else {
        conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			  avanzarIterador(avl1);
        avanzarIterador(avl2);
      }
    }
		while(estaDefinidaActual(avl1)){
      conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			avanzarIterador(avl1);
		}

		while(estaDefinidaActual(avl2)){
      conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl2), conjuntoResultado->avl );
			avanzarIterador(avl2);
		}
    liberarIterador(avl2);
    liberarIterador(avl1);
  
  return conjuntoResultado;   
}

/*
  Devuelve un 'TConjunto' con los elementos de 'c1' que no pertenecen a 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n1 + n2),
  siendo 'n1' y 'n2' la cantidad de elementos de 'c1' y 'c2' respectivamente y
  'n' la del 'TConjunto' resultado.
 */
TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto conjuntoResultado = crearConjunto();

/*
 /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  CASOS QUE RESUELVE DE MÁS ////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////

    if(estaVacioConjunto(c1) && estaVacioConjunto(c2))
        conjuntoResultado = NULL;
    
    else if (estaVacioConjunto(c1)){
       conjuntoResultado = NULL;
        }

    else if (estaVacioConjunto(c2)){
      TIterador avl1 = iteradorDeConjunto(c1);
      avl1 = reiniciarIterador(avl1);
      while(estaDefinidaActual(avl1)){
        conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			  avanzarIterador(avl1);
      }
      liberarIterador(avl1);  
    }
    
    else{*/

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

      TIterador avl1 = iteradorDeConjunto(c1);
      TIterador avl2 = iteradorDeConjunto(c2);
      avl1 = reiniciarIterador(avl1);
      avl2 = reiniciarIterador(avl2);

      while(estaDefinidaActual(avl1) && estaDefinidaActual(avl2) ) {

		    if(actualEnIterador(avl1) < actualEnIterador(avl2)){
          conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			    avanzarIterador(avl1);
        }

        else if (actualEnIterador(avl1) == actualEnIterador(avl2) ){
          avanzarIterador(avl1);
          avanzarIterador(avl2);
        }

        else
          avanzarIterador(avl2);      
      }
      while(estaDefinidaActual(avl1) && !estaDefinidaActual(avl2)){
        conjuntoResultado->avl = insertarEnAvl(actualEnIterador(avl1), conjuntoResultado->avl );
			  avanzarIterador(avl1);
		  }
      liberarIterador(avl1);
      liberarIterador(avl2);
    
    return conjuntoResultado;
}

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'c'.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad de
  elementos de 'c'.
 */


static void perteneceAux(nat elem, TAvl avl, bool &pertenece){ //FUNCIÓN AUXILIAR
  if (!estaVacioAvl(avl) && !pertenece){                      //para poder operar mejor sobre el arbol
    if(elem < raizAvl(avl))                                 //y poder retornar mejor el resultado
      perteneceAux(elem,izqAvl(avl), pertenece);
    else if(elem > raizAvl(avl))
      perteneceAux(elem,derAvl(avl), pertenece);
    else
      pertenece = true;
  };
}
bool perteneceAConjunto(nat elem, TConjunto c){
  bool pertenece = false;
  if (!estaVacioConjunto(c))
    perteneceAux(elem,c->avl,pertenece);
  return pertenece;

}

/*
  Devuelve 'true' si y solo si 'c' es vacío (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVacioConjunto(TConjunto c){
  return c->avl == NULL;
}

/*
  Devuelve la cantidad de elementos de 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cardinalidad(TConjunto c){
  return cantidadEnAvl(c->avl);
}

/*
  Devuelve un 'TConjunto' con los 'n' elementos que están en en el rango
  [0 .. n - 1] del arreglo 'elems'.
  Precondiciones:
  - n > 0
  - Los elementos están ordenados de manera creciente estricto
  (creciente y sin repetidos).
  El tiempo de ejecución en el peor caso es O(n).
 */
TConjunto arregloAConjunto(nat *elems, nat n){
  if(n!=0){
    TConjunto res = new repConjunto;
    res->avl = arregloAAvl(elems, n); 
    return res;
  }else{return NULL;}
}

/*
  Devuelve un 'TIterador' de los elementos de 'c'.
  En la recorrida del iterador devuelto los elementos aparecerán en orden
  creciente.
  El 'TIterador' resultado no comparte memoria con 'c'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'c'.
 */
TIterador iteradorDeConjunto(TConjunto c){
  return enOrdenAvl(c->avl);
}

/*
  Libera la memoria asignada a 'c' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'c'.
 */
void liberarConjunto(TConjunto c){
  liberarAvl(c->avl);
  delete c;
}

