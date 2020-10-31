/*
  Módulo de dimplementación de 'TBinario'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h> 
#include <stdio.h> // sprintf
#include <stdlib.h>

typedef struct repBinario *TBinario;

// struct repBinario;
struct repBinario{
  TInfo dato;
  TBinario izq;
  TBinario der;
};

/*
  Devuelve un 'TBinario' vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
TBinario crearBinario(){
    return NULL;
}


/*
  Devuelve 'true' si y solo si 'b' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool esVacioBinario(TBinario b){
    return b == NULL;
}

static void insernario(TInfo i, TBinario &b){ //FUNCION AUXILIAR
    if(b == NULL){
        b = new repBinario;
        b->dato = i;
        b->der = NULL;
        b->izq = NULL;
    }
    else{ 
        if( natInfo(i) < natInfo(b->dato) )
                insernario(i, b->izq);
        else if( natInfo(i) > natInfo(b->dato) )
            insernario(i, b->der);     
    }
}
/*
  Inserta 'i' en 'b' respetando la propiedad de orden definida.
  Devuelve 'b'.
  Precondición: esVacioBinario(buscarSubarbol(natInfo(i), b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario insertarEnBinario(TInfo i, TBinario b){
    assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));
    insernario(i,b);
    return b;
}

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TInfo mayor(TBinario b){
    assert(!esVacioBinario(b));
    if(b->der == NULL)
        return b->dato;
    else 
        return mayor(b->der);
}

/*
  Remueve el nodo en el que se localiza el elemento mayor de 'b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario removerMayor(TBinario b){
    assert(!esVacioBinario(b));
    if(b->der == NULL){
        TBinario izq = b->izq;
        delete(b);
        b = izq;
    }
    else
        b->der = removerMayor(b->der);
    return b;   
}

/*
  Remueve de 'b' el nodo en el que el componente natural de su elemento es
  'elem'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve 'b'.
  Precondición: !esVacioBinario(buscarSubarbol(elem, b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
static void remover(nat elem, TBinario &b){  //FUNCION AUXILIAR
    TBinario res;
    if(!esVacioBinario(b) ){
        if (natInfo(b->dato) == elem){
            if (b->izq == NULL ) {
                res = b ;
                b = b->der ;
                liberarInfo(res->dato);
                delete res ;
            }
            else if (b->der == NULL ) {
                res = b ;
                b = b->izq ;
                liberarInfo(res->dato);
                delete res ;
            }
            else {
                liberarInfo(b->dato);
                b->dato = copiaInfo(mayor(b->izq) );
                remover(natInfo(b->dato), b->izq) ;
            }
        }
        else if ( elem < natInfo(b->dato))
            remover(elem , b->izq) ;
            else 
            remover(elem , b->der) ;
    }
}

TBinario removerDeBinario(nat elem, TBinario b){
    assert(!esVacioBinario(buscarSubarbol(elem, b)));
    remover(elem,b);
    return b;
}

/*
  Libera la memoria asociada a 'b' y todos sus elementos.
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
void liberarBinario(TBinario b){
    if(b!=NULL){
       liberarBinario(b->izq);
       liberarBinario(b->der);
       liberarInfo(b->dato);
       delete b;
       b = NULL;
    }
}

static nat maximo(nat n1, nat n2) //FUNCION AUXILIAR
	{return (n1 >= n2) ? n1 : n2;}

static int absoluto(int n)  //FUNCION AUXILIAR
	{return (n>=0) ? (n) : (-n);}

static bool AVL(nat &alt,TBinario b){ //FUNCION AUXILIAR
    if(esVacioBinario(b)){
        alt = 0;
        return true;
    }
    else{
        nat alturaIzq = 0; 
        nat alturaDer = 0;
        bool avlIzq = AVL(alturaIzq,b->izq);
        bool avlDer = AVL(alturaDer,b->der);
        alt = 1 + maximo(alturaIzq,alturaDer);
        int diferencia = absoluto(alturaDer - alturaIzq);
        if (!avlIzq || !avlDer || diferencia > 1)
            return false;
        else
            return true;   
    }           
}
/*
  Devuelve 'true' si y solo si cada nodo de 'b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
bool esAvl(TBinario b){
    nat alt = 0;
    return AVL(alt,b);
}

/*
  Devuelve el elemento asociado a la raíz de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TInfo raiz(TBinario b){
    assert(!esVacioBinario(b));
    return b->dato;
}

/*
  Devuelve el subárbol izquierdo de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario izquierdo(TBinario b){
    assert(!esVacioBinario(b));
    return b->izq;
}

/*
  Devuelve el subárbol derecho de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario derecho(TBinario b){
    assert(!esVacioBinario(b));
    return b->der;
}

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo
  componente natural es 'elem'.
  Si 'elem' no pertenece a 'b', devuelve el árbol vacío.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario buscarSubarbol(nat elem, TBinario b){
    TBinario res;
    if(esVacioBinario(b))
         res = crearBinario();
    else{
        if (elem < natInfo(b->dato))
            res = buscarSubarbol(elem, b->izq);
        else if (elem > natInfo(b->dato))
            res = buscarSubarbol(elem, b->der);
        else if(natInfo(b->dato) == elem)
            res = b;
    }
    return res;
}

/*
  Devuelve la altura de 'b'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat alturaBinario(TBinario b){
    if( b == NULL)
        return 0;
    else{
        nat hIzq = alturaBinario(b->izq);
        nat hDer = alturaBinario(b->der);
        if( hIzq > hDer)
            return hIzq +1;
        else 
            return hDer +1;
    }
}

/*
  Devuelve la cantidad de elementos de 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat cantidadBinario(TBinario b){
    if(b == NULL)
        return 0;
    else 
        return cantidadBinario(b->izq) + cantidadBinario(b->der) +1;

}

/*
  Devuelve la suma de los componentes reales de los últimos 'i' elementos
  (considerados según la propiedad de orden de los árboles TBinario)
  de 'b' cuyos componentes reales sean mayores que 0.
  Si en 'b' hay menos de 'i' elementos que cumplan esa condición devuelve la
  suma de los componenetes reales de ellos.
  No se deben crear estructuras auxiliares.
  No se deben visitar nuevos nodos después que se hayan encontrado los
  'i' elementos.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */

static void auxSuma(nat &i, TBinario b, double &suma){
    if(i>0 && b!= NULL){
    	auxSuma(i, b->der,suma);
    	if (realInfo(b->dato) > 0 && i > 0){
        	suma = suma + realInfo(b->dato);
        	i--;   
    	}
    	auxSuma(i, b->izq,suma);
    }    
}
double sumaUltimosPositivos(nat i, TBinario b){
    double suma = 0;
    nat ii= i;
    auxSuma(ii,b,suma);
    return suma;
}


static void lineauxzacion(TCadena & cad, TBinario b){ //FUNCION AUXILIAR
    if(b!=NULL){
        lineauxzacion(cad,b->izq);
        cad = insertarAlFinal(copiaInfo(b->dato),cad);
        lineauxzacion(cad,b->der);
    }
}
/*
  Devuelve una 'TCadena' con los elementos de 'b' en orden lexicográfico
  creciente según sus componentes naturales.
  La 'TCadena' devuelta no comparte memoria con 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
TCadena linealizacion(TBinario b){
    TCadena cad = crearCadena();
    lineauxzacion(cad,b);
    return cad;
}

/*
  Devuelve un árbol con copias de los elementos de 'b' que cumplen la condición
  "realInfo(elemento) < cota".
  La estructura del árbol resultado debe ser análoga a la de 'b'. Esto
  significa que dados dos nodos 'U' y 'V' de 'b' en los que se cumple la
  condición y tal que 'U' es ancestro de 'V', en el árbol resultado la copia de
  'U' debe ser ancestro de la copia de 'V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo 'V' no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de 'V' deberá ser ancestro de
  las copias de todos los descendientes de 'V' que cumplen la condición.
  Ver ejemplos en la letra.
  El árbol resultado no comparte memoria con 'b'. *)
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
TBinario menores(double cota, TBinario b){
    if (esVacioBinario(b)){
        TBinario be = crearBinario();
        return be;
    }
    else {
        TBinario mizq, mder;
        mizq = menores(cota,izquierdo(b));
        mder = menores(cota,derecho(b));
        TInfo root = raiz(b);
        if(realInfo(root) < cota){
            TBinario bi = new repBinario;
            bi->dato = copiaInfo(root);
            bi->izq = mizq;
            bi->der = mder;
            return bi;
        }
        else if(esVacioBinario(mizq)){
            return mder;
            liberarBinario(mizq);
            
        }else if(esVacioBinario(mder)){
            return mizq;
            liberarBinario(mder);
            
        }
        else{
            TBinario bi = new repBinario;
            TInfo infox = mayor(mizq);
            bi->dato = copiaInfo(infox);
            liberarInfo(infox);
            bi->izq = removerMayor(mizq);
            bi->der = mder;
            return bi;   
        }    
    }
}

/*
  Imprime los elementos de 'b', uno por línea, en orden descendente de la
  propiedad de orden de los árboles 'TBinario'.
  Antes del elemento imprime una cantidad de guiones igual a su profundidad.
  El elemento se imprime según la especificación dada en 'infoATexto'.
  La profundidad de la raíz es 0.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVacioBinario(b) solo se imprime el fin de línea.
  El tiempo de ejecución es O(n . log n) en promedio, siendo 'n' la cantidad
  de elementos de 'b'.
 */

static void imprimirX(int nivel, TBinario b){
	if(!esVacioBinario(b)){
        imprimirX(nivel+1, b -> der);
	    for (int j = 0; j < nivel; j++ )
		    printf("-");
        char*salida;
        salida = infoATexto(b->dato);
		printf("%s", salida);
		printf("\n");
        delete[] salida;
        
        imprimirX(nivel+1, b -> izq);
        
    }
}

void imprimirBinario(TBinario b){
    printf("\n");
    int n = 0;
    imprimirX(n,b);
}
