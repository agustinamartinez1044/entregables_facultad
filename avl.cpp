/*
  Módulo de implementación de 'TAvl'.

  Los elementos de tipo 'TAvl' son avls cuyos elementos son de tipo nat.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/pila.h"
#include "../include/colaAvls.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// struct repAvl;
struct repAvl {
  nat dato;
  nat altura;
  nat cantidad;
  TAvl izq, der;
};

/*
  Devuelve un 'avl' vacío (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl crearAvl(){
  return NULL;
}

/*
  Devuelve 'true' si y solo si 'avl' es vacío (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVacioAvl(TAvl avl){
  return avl == NULL;
}

//ROTACIONES

static nat maximo(nat n1, nat n2){
  if(n1>=n2)
    return n1;
  else
    return n2;
}

	
//rotación a la derecha
static void rotarD(TAvl &avl){
    TAvl y = avl->izq;
    TAvl x = y->der;
    y->der = avl;
    avl->izq = x;
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    y->cantidad = (cantidadEnAvl(y->izq) + cantidadEnAvl(y->der))+1;
    avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    y->altura = maximo(alturaDeAvl(y->izq),alturaDeAvl(y->der))+1;
    avl = y;
}

//rotación a la izquierda       
static void rotarI(TAvl &avl){
    TAvl y = avl->der;
    TAvl x = y->izq;
    y->izq = avl;
    avl->der = x;
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    y->cantidad = (cantidadEnAvl(y->izq) + cantidadEnAvl(y->der))+1;
    avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    y->altura = maximo(alturaDeAvl(y->izq),alturaDeAvl(y->der))+1;
    avl = y;
}

/*
  Inserta 'elem' en 'avl' respetando la propiedad de orden definida.
  Precondición: estaVacioAvl(buscarEnAvl(elem, TAvl).
  Devuelve 'avl'.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad
  de elementos de 'avl'.
*/

TAvl insertarEnAvl(nat elem, TAvl avl){
    if (avl == NULL){
        avl = new repAvl;
        avl->dato = elem ;
        avl->izq = avl->der = NULL;
        avl->altura = 1;
        avl->cantidad = 1;
    }else{
        if (elem < avl->dato){
            avl->izq = insertarEnAvl(elem ,avl->izq);
            avl->cantidad = avl->cantidad +1;
            avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
            int factorDeBalanceo =(alturaDeAvl(avl->izq) - alturaDeAvl(avl->der));
            if (factorDeBalanceo > 1){
                if (alturaDeAvl(avl->izq->izq) > alturaDeAvl(avl->izq->der)){
                    rotarD(avl);
                }else{ //alturaDeAvl (avl->izq->izq  < alturaDeAvl(avl->izq->der)
                    rotarI(avl->izq);
                    rotarD(avl);
                    }
                }
        }else{
            avl->der = insertarEnAvl(elem ,avl->der);
            avl->cantidad = avl->cantidad +1;
            avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
            int fb = (alturaDeAvl(avl->izq) - alturaDeAvl(avl->der));
            if (fb<-1){
                if (alturaDeAvl(avl->der->der) > alturaDeAvl(avl->der->izq)){
                    rotarI(avl);
                }else{ //alturaDeAvl (avl->der->der  < alturaDeAvl(avl->der->izq)
                    rotarD(avl->der);
                    rotarI(avl);

                    }
            }
        }
    }
    return avl ;
}
/*
  Devuelve el subárbol cuya raíz es 'elem'.
  Si ningún nodo cumple esa condición devuelve el árbol vacío.
  El 'avl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad
  de elementos de 'avl'.
 */
TAvl buscarEnAvl(nat elem, TAvl avl){
  TAvl resultado;
  if(estaVacioAvl(avl)){
    resultado = crearAvl();
  }
  else{
    if(avl->dato == elem)
      resultado = avl;
    else
      if (elem < avl->dato)
        resultado = buscarEnAvl(elem, avl->izq);
      else
        resultado = buscarEnAvl(elem, avl->der);
  } 
  return resultado;
}

/*
  Devuelve el elemento asociado a la raíz de 'avl'.
  Precondición: ! estaVacioAvl(avl).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat raizAvl(TAvl avl){
  assert(!estaVacioAvl(avl));
  return avl->dato;
}

/*
  Devuelve el subárbol izquierdo de 'avl'.
  Precondición: ! estaVacioAvl(avl).
  El 'avl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl izqAvl(TAvl avl){
  assert(!estaVacioAvl(avl));
  return avl->izq;
}

/*
  Devuelve el subárbol derecho de 'avl'.
  Precondición: ! estaVacioAvl(avl).
  El 'avl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl derAvl(TAvl avl){
  assert(!estaVacioAvl(avl));
  return avl->der;
}

/*
  Devuelve la cantidad de elementos en 'avl'.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cantidadEnAvl(TAvl avl){
  int cant = 0;
  if(avl != NULL)
    cant = avl->cantidad;
  return cant;
}

/*
  Devuelve la altura de 'avl'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat alturaDeAvl(TAvl avl){
  int alt = 0;
  if(avl != NULL)
    alt = avl->altura;
  return alt;
}

/*
  Devuelve un 'TIterador' de los elementos de 'avl'.
  En la recorrida del iterador devuelto los elementos aparecerán en orden
  creciente.
  El 'TIterador' resultado no comparte memoria con 'avl'.
  El tiempo de ejecución en el peor caso es O(n) siendo 'n' la cantidad de
  elementos de 'avl'.
 */
 static void enOrdenAvlRec(TIterador res, TAvl &avl){
  if(avl!= NULL){
    enOrdenAvlRec(res,avl->izq);
    res = agregarAIterador(avl->dato,res);
    enOrdenAvlRec(res, avl->der);
  }
}

TIterador enOrdenAvl(TAvl avl){
  TIterador resultado  = crearIterador();
  enOrdenAvlRec(resultado,avl);
  return resultado;
}

/*
  Devuelve un 'TAvl' con los 'n' elementos que están en el rango [0 .. n - 1]
  del arreglo 'elems'.
  Precondiciones:
  - n > 0
  - Los elementos están ordenados de manera creciente estricto
  (creciente y sin  repetidos).
  En cada nodo del árbol resultado la cantidad de elementos de su subárbol
  izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
  derecho.
  El tiempo de ejecución en el peor caso es O(n).
 */

  static TAvl arregloAAvlRec(nat *elems,int inf, int sup){
  TAvl res;
  if( inf > sup){
    res = NULL;
  }else{
    res = new repAvl;
    nat medio = (inf+sup) / 2;
   
    res -> dato = elems[medio];
    res -> izq = arregloAAvlRec(elems,inf,(medio - 1));
    res -> der  = arregloAAvlRec(elems,(medio + 1),sup);
    res-> altura = maximo(alturaDeAvl(derAvl(res)),alturaDeAvl(izqAvl(res))) + 1;
    res-> cantidad = (cantidadEnAvl(derAvl(res)) + cantidadEnAvl(izqAvl(res)) + 1);
  }
  return res;
} 
TAvl arregloAAvl(nat *elems, nat n){
  assert(n>0);
  TAvl res = arregloAAvlRec(elems,0,n-1);
  return res;
}

/*
  Devuelve un 'TAvl' de altura 'h' con 'n' nodos, siendo 'n' la mínima cantidad
  de elementos que puede tener un 'TAvl' de altura 'h'.
  Los elementos van desde 1 hasta 'n'.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(n).
  Ver ejemplos en la letra.
 */



static TAvl AvlMinAux(nat h, TAvl &avl){
  if(h == 0)              //CASO BASE
    return NULL;
  if(h == 1){             //CASO BASE
    avl = new repAvl;
    avl->dato = 1;
    avl->izq = NULL;
    avl->der = NULL;
    avl->altura = 1;
    avl->cantidad = 1;
  }
  else{
    avl = new repAvl;
    avl->izq = AvlMinAux(h - 1, avl->izq);
    avl->der = AvlMinAux(h - 2, avl->der);

    //CHEQUEAR LOS CASOS EN LOS QUE NO ESTÁ DEFINIDO EL DATO
    if(avl->der != NULL && avl->izq != NULL)
      avl->dato = avl->der->dato + avl->izq->dato + 1; 

    else if(avl->izq != NULL)
      avl->dato = avl->izq->dato + 1; 

    else if(avl->der != NULL)
      avl->dato = avl->der->dato + 1; 

    avl->altura = h;
    avl->cantidad = cantidadEnAvl(avl->der) + cantidadEnAvl(avl->izq) +1; 
  }  
  return avl;
}

static void fil(nat &ultimo, TAvl &avl, nat &inicio) {  //FILTRADO
  if(!estaVacioAvl(avl)){   
    if(avl->izq != NULL){  
      avl->dato =  avl->izq->dato +  ultimo  + inicio  ;      
    }else{
      avl-> dato =   inicio + ultimo ;
    }
    fil(ultimo, avl->izq, inicio);
    fil(avl->dato, avl->der, inicio); 
  }
}

TAvl avlMin(nat h){
  TAvl res = crearAvl();
  res = AvlMinAux(h, res);
  nat ultimo = 0;
  nat inicio = 1; //Inicio de los datos
  fil(ultimo, res, inicio);
  return res;
}


/*
////////////////////////////////////////////////////////////////////////////////////////
///////////////AVL MIN OTRA POSIBLE SOLUCIÓN CON ESTRUCTURA AUXILIAR///////////////////
///////////////   FUNCIONA MAL AL INCREMENTAR EL VALOR DEL DATO     ///////////////////
////////////////////////////////////////////////////////////////////////////////////////


struct avlUltimo {
    TAvl avl;
    int ultimo;
};

static avlUltimo avlMinRec(int h, int &primero){
	avlUltimo res;
	if (h<=0){
		res.avl = NULL;
		res.ultimo = primero-1;
	}else if (h==1){
		res.avl = new repAvl;
        res.avl->dato = primero++;  //solo primero?
        res.ultimo = primero - 1;   //primero++?
        res.avl->izq = NULL;
        res.avl->der = NULL;
        res.avl->altura = 1;
        res.avl->cantidad = 1;
	}else {
		res.avl = new repAvl;
		res.avl->izq = avlMinRec(h-1, primero).avl;
		res.avl->altura = h;
		res.avl->dato = primero++;
		avlUltimo enganche = avlMinRec(h-2, primero);   
		res.avl->der = enganche.avl;
		res.avl->cantidad = 1 + cantidadEnAvl(res.avl->der) + cantidadEnAvl(res.avl->izq);
		if (res.avl-> der == NULL)
			res.ultimo = primero;
	}
	return res;
}
TAvl avlMin(nat h){
	int comienzoDatos = 1;
	TAvl res = avlMinRec(h, comienzoDatos).avl;
	return res;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////

/*
  Imprime los elementos de cada nivel de 'avl'.
  Imprime una línea por nivel, primero el más profundo y al final el que
  corresponde a la raíz.
  Cada nivel se imprime en orden creciente. Se debe dejar un espacio en
  blanco después de cada número.
  Se puede asumir que 0 no es ningún elemento.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'TAvl'.
  Ver ejemplos en la letra.
 */


void imprimirAvl(TAvl avl){ //usar "0" como separador en pila, tipo centinela
                            //usar "NULL" como separador en cola, tipo centinela
    if (avl != NULL) {
        TPila p = crearPila(avl->cantidad + avl->altura);
        TColaAvls q = crearColaAvls();
        q = encolar(avl , q);
        q = encolar(NULL,q); 

        while(!estaVaciaColaAvls(q)){
            avl = frente(q);

            if(avl != NULL){
              q = desencolar(q);
              p = apilar(avl->dato, p);
              
              if(avl->der != NULL)
                q = encolar(avl->der,q);
              
              if(avl->izq!= NULL)
                q = encolar (avl->izq,q);

            }else{
                q = desencolar (q);
                if(!estaVaciaColaAvls(q)){
                    p = apilar(0,p);
                    q = encolar (NULL,q);
                }
            }
        }   
        liberarColaAvls(q);  

        while (!estaVaciaPila(p)){ //Impresiones
            if(cima(p) != 0)
                printf("%d ",cima(p));
            else
                printf("\n");
            p = desapilar(p);
        }
        
    printf("\n");
    liberarPila(p);        
    }
}


/*
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// IMPRIMIR RECURSIVO (?) No anda :( ///////////////////////////////

static void ImprimirRec(int nivel, TAvl avl ){
  if(avl != NULL && nivel > 0){
    if (nivel == 1 )
      printf("%d ", raizAvl(avl));
    ImprimirRec(nivel-1, avl->izq);
    ImprimirRec(nivel-1, avl->der);
  }
}

void imprimirAvl(TAvl avl){
  if(avl != NULL){
    int nivel = avl->altura;
    for(int i = nivel; i > 0; i--){
      ImprimirRec(nivel, avl);
      printf("\n");
    }
  }
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////

/*
  Libera la memoria asignada a 'TAvl'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'TAvl'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'avl'.
 */
void liberarAvl(TAvl avl){
  if (avl != NULL){
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
    avl = NULL;
  }
}

