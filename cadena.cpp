/*
  Módulo de implementación de 'TCadena'.

  Los elementos de tipo 'TCadena' son lista doblemente enlazada de elementos
  de tipo 'Tinfo', con cabezal con punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>  // sprintf
#include <stdlib.h>

/*
  Las variables de tipo 'TLocalizador' permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una cadena enlazada esas
  variables son punteros a los nodos.
*/

// struct nodo;
struct nodo{
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

// Declaración del tipo 'TLocalizador'
typedef struct nodo *TLocalizador;

// struct repCadena;
struct repCadena{
  TLocalizador inicio;
  TLocalizador final;
};

// Declaración del tipo 'TCadena'
typedef struct repCadena *TCadena;

/*
  Devuelve 'true' si y solo si 'loc' es un 'TLocalizador' válido.
  En cadenas enlazadas un 'TLocalizador' es válido si y solo si no es 'NULL'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esLocalizador(TLocalizador loc){
    return loc != NULL;
}

/*
  Devuelve la 'TCadena' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena crearCadena(){
    TCadena res = new repCadena;
    res->inicio = res->final = NULL;
    return res;
}

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
void liberarCadena(TCadena cad){
    TLocalizador a_borrar;
    while (cad->inicio != NULL){
        a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(a_borrar->dato);
        delete a_borrar;
    }
    delete cad;
}

/*
  Devuelve 'true' si y solo si 'cad' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esVaciaCadena(TCadena cad){
    assert(((cad->inicio == NULL) && (cad->final == NULL)) || 
           ((cad->inicio != NULL) && (cad->final != NULL)) );
    return ((cad->inicio == NULL) /*&& (cad->final == NULL) */);
}

/*
  Devuelve el 'TLocalizador' con el que se accede al inicio de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador inicioCadena(TCadena cad){
    TLocalizador res;
    if (esVaciaCadena(cad)){       
        res = NULL; 
    }
    else{
        res = cad->inicio;
    }
    return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al final de 'cad'.
  Si es_vacia_cadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador finalCadena(TCadena cad){
    TLocalizador res;
    if (esVaciaCadena(cad))
        res = NULL;
    else
        res = cad->final;
    return res;
}

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TInfo infoCadena(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc,cad));
    return loc->dato;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente siguiente a 'loc'.
  Si esFinalCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador siguiente(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    TLocalizador res;
    if (esFinalCadena(loc, cad))
        res = NULL;
    else 
        res = loc->siguiente;
    return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente anterior a 'loc'.
  Si esInicioCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador anterior(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    TLocalizador res; 
    if (esInicioCadena(loc, cad))
        res = NULL;
    else
        res = loc->anterior;
    return res;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esFinalCadena(TLocalizador loc, TCadena cad){
    bool res;
    if(!esVaciaCadena(cad) )
        res = (loc == finalCadena(cad));
    else
       res = false; 
   return res; 
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esInicioCadena(TLocalizador loc, TCadena cad){
    bool res;
    if (!esVaciaCadena(cad))
        res = (loc == inicioCadena(cad));
    else
        res = false; 
    return res;
}

/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarAlFinal(TInfo i, TCadena cad){
    nodo *nuevo = new nodo;
    nuevo->dato = i;
    nuevo->siguiente = NULL;
    if(esVaciaCadena(cad)) {
        cad->inicio = nuevo;
        nuevo->anterior = NULL;
    } else {
        nuevo->anterior = cad->final;
        cad->final->siguiente = nuevo;
    }
    cad->final = nuevo;
    return cad;
}

/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc,cad));
    nodo *nuevo = new nodo; 
    nuevo->dato = i;
       if(esInicioCadena(loc, cad)) {
            cad->inicio = nuevo;
            nuevo->anterior = loc->anterior;
            
        } else {
            nuevo->anterior = loc->anterior;
            loc->anterior->siguiente=nuevo;
            
        }
        loc->anterior = nuevo;
        nuevo->siguiente = loc;
  return cad;    
}

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena removerDeCadena(TLocalizador loc, TCadena cad){
  assert(localizadorEnCadena(loc,cad));
  if (!esInicioCadena(loc, cad) && !esFinalCadena(loc, cad)) {
    loc->anterior->siguiente = loc->siguiente;
    loc->siguiente->anterior = loc->anterior;
  }
  else{
    if (esInicioCadena(loc, cad) && esFinalCadena(loc, cad)){
      cad->inicio=NULL;
      cad->final=NULL;
    }          
    else{
      if (esFinalCadena(loc, cad) && !esInicioCadena(loc, cad) ) {
        cad->final = loc->anterior;
        loc->anterior->siguiente = NULL;        
      }
      else {
        if(esInicioCadena(loc, cad) && !esFinalCadena(loc,cad)){
          cad->inicio = loc->siguiente;
          loc->siguiente->anterior=NULL;    
        }
      }
    }
  }
  liberarInfo(loc-> dato);
  delete loc;   
  return cad;    
}


/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donde 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
void imprimirCadena(TCadena cad){
 if(!esVaciaCadena(cad)) {
        char *salida;
        TLocalizador aux; aux=inicioCadena(cad);
        while (esLocalizador(aux)){
            salida = infoATexto(aux->dato);
            printf("%s",salida);
            delete[] salida;
            aux = siguiente(aux,cad);
            
        }
        
    }
    printf("\n");
}



/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador kesimo(nat k, TCadena cad){
  TLocalizador res;
  if(esVaciaCadena(cad) || k == 0)
    res = NULL;
  else {
    nat contador = 1;
    res = inicioCadena(cad);
    while((siguiente(res,cad) != NULL) && contador < k) {
      res = siguiente(res,cad);
      contador++;
    }
    if (contador != k)
        res = NULL;
  }
  return res;  
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede a un elemento de 'cad',
  (o sea, si apunta a un nodo de 'cad').
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
bool localizadorEnCadena(TLocalizador loc, TCadena cad){
    TLocalizador cursor = inicioCadena(cad);
    while (esLocalizador(cursor) && (cursor != loc))
        cursor = siguiente(cursor,cad);
    return esLocalizador(cursor);
  }
/*
  Devuelve 'true' si y solo si 'loc1' es igual o precede a 'loc2' en 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    bool res;
    res = localizadorEnCadena(loc1,cad);
    if (res){
        TLocalizador cursor = loc1;
        while (esLocalizador(cursor) && (cursor !=loc2))
            cursor = siguiente(cursor, cad);
        res = esLocalizador(cursor);
        assert(!res || localizadorEnCadena(loc2, cad));
    }
    return res;
}

/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
    if (esVaciaCadena(cad)) {
        cad->inicio = sgm->inicio;
        cad->final = sgm->final;
    } else {
        if (!esVaciaCadena(sgm)) {
            sgm->inicio->anterior = loc;
            sgm->final->siguiente = loc->siguiente;
            if(esFinalCadena(loc, cad))
                cad->final = sgm->final;
            else
                loc->siguiente->anterior = sgm->final;
            
            loc->siguiente = sgm->inicio;
        }
    }
    delete sgm;
    return cad;
}

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
  assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
  TCadena res = crearCadena();
  if(!esVaciaCadena(cad)){
      TLocalizador aux = desde;
      while (aux != hasta){
        res = insertarAlFinal(copiaInfo(aux->dato), res);
        aux = aux->siguiente;
      }
      res = insertarAlFinal(copiaInfo(hasta->dato), res); 
  }
  return res;  
}

/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
  assert (esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad)); 
  if(!esVaciaCadena(cad)){
    TLocalizador lpos = desde;
	  while(esLocalizador(lpos) && desde != hasta){
		  lpos = siguiente(lpos, cad);
		  removerDeCadena(desde, cad);
      desde = lpos;
		}
    removerDeCadena(hasta, cad);  
  }
  return cad;
}


/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
  assert (localizadorEnCadena(loc, cad));
  loc->dato = i;
  return cad;
}

/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
  localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
  assert(localizadorEnCadena (loc1, cad) && localizadorEnCadena (loc2, cad));
  TInfo aux = loc1->dato; 
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
}
/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  TLocalizador aux = loc;
  if (esVaciaCadena(cad))
    aux = NULL;
  else{
    while (esLocalizador(aux) && natInfo(aux->dato) != clave){
      aux = siguiente(aux, cad);
    }
  }
  return aux;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  TLocalizador aux = loc;
  if (esVaciaCadena(cad))
    aux = NULL;
  else{
    while (esLocalizador(aux) && natInfo(aux->dato) != clave){
      aux = anterior(aux, cad);
    }
  }
  return aux;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
  assert(localizadorEnCadena(loc, cad));
  TLocalizador min = loc;
  while (localizadorEnCadena(siguiente(loc, cad), cad)){
    loc = siguiente(loc, cad);
    if(natInfo(loc->dato) < natInfo(min->dato))
      min = loc;
  }
  return min;
  
}

