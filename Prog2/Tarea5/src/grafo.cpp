/*
  Módulo de implemetación de 'TGrafo'.

  Los elementos de tipo 'TGrafo' son grafos cuya cantidad de nodos se determina
  con un parámetro, N, y se identifican con naturales desde 1 hasta N.
  La cantidad de aristas está acotada por un parámetro, M, y tienen costo de
  tipo double.
  Los valores N y M son parámetros pasados al crear el grafo.
  El espacio ocupado para representar un grafo debe ser O(N + M).

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */


#include "../include/grafo.h"
#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/mapping.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdio.h>  // sprintf
#include <stdlib.h>

// Representación de 'TGrafo'.
// Se debe definir en grafo.cpp.
// struct repGrafo;
// Declaración del tipo 'TGrafo'.

//Mapping para aristas   -----> (mı́n(v i , v j ) − 1) × N + (máx(v i , v j ) − 1) funcion hash
//Arreglo para vertices
//Y vertices tienen avl con sus vecinos 
struct repGrafo{
  TMapping MappAristas; //Asociación para las aristas
  TAvl *ArrayVertices; //En cada campo hay un avl con sus vecinos, identificar al vertice por el numero de celda
  nat cantVertices; //Total posible de vertices = N
  //nat cantAristas; //Total posible de aristas (vecino) = M
  //nat topeAristas;
  //nat topeVertices;
};

static nat maximo(nat n1, nat n2){
  if(n1>n2)
    return n1;
  else
    return n2;
}

static nat minimo(nat n1, nat n2){
  if(n1>n2)
    return n2;
  else
    return n1;
}

static nat funHash(nat Vi, nat Vj,nat N){
  nat max = maximo(Vi, Vj);
  nat min = minimo(Vi, Vj);
  nat fun = ((min - 1)*(N+1) + (max - 1));
  //(mı́n(v1, v2) − 1) × N + (máx(v1, v2 ) − 1)
  return fun;
}

/*
  Devuelve un 'TGrafo' con 'N' vértices identificados desde 1 hasta 'N'
  sin parejas de vecinos establecidos.
  Podŕa haber hasta 'M' parejas de vecinos.
  El tiempo de ejecución en peor caso es O(max{N,M}).
 */
TGrafo crearGrafo(nat N, nat M){
  TGrafo grafo = new repGrafo;
  grafo->MappAristas = crearMap(M);
  grafo->ArrayVertices = new TAvl[N + 1];
  for(nat i = 1; i <= N; i++){
    grafo->ArrayVertices[i] = crearAvl();
  }
  grafo->cantVertices = N;
  return grafo;
}

/*
  Devuelve la cantidad de vértices de 'g'.
  El tiempo de ejecución en peor caso es O(1).
 */
nat cantidadVertices(TGrafo g){
  return g->cantVertices;
}

/*
  Devuelve 'true' si y solo si en 'g' ya hay M parejas de vecinos,
  siendo M el segundo parámetro pasado en crearGrafo.
  El tiempo de ejecución en peor caso es O(1).
 */
bool hayMParejas(TGrafo g){
  return estaLlenoMap(g->MappAristas);
}

/*
  Establece que 'v1' y 'v2' son vecinos en 'g' y la distancia entre ambos es
  'd'.
  Precondición: 1 <= v1, v2 <= N.
  Precondición: v1 != v2
  Precondición: !sonVecinos(v1, v2, g).
  Precondición: !hayMParejas(g).
  Precondición: d >= 0.
  Devuelve 'g'.
  El tiempo de ejecución es en peor caso O(max{log n1, log n2}), siendo 'n1' y
  'n2' la cantidad de vecinos de 'v1' y 'v2' respectivamente.
 */
TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){ //insertar en el arbol
  assert((1 <= v1 && v2 <= g->cantVertices) && ( v1 != v2) && (!sonVecinos(v1, v2, g)) && (!hayMParejas(g)) && (d >= 0));
  //Para hacer vecinos debo agregar (bucket, distancia) al mapp 
    //AsociarEnMap se encarga
  //Insertar g->ArrayAvl[v1] = insertarEnAvl(v2) 
    //Lo mismo para v2
  g->ArrayVertices[v1] = insertarEnAvl(v2, g->ArrayVertices[v1]);
  g->ArrayVertices[v2] = insertarEnAvl(v1, g->ArrayVertices[v2]);
  g->MappAristas = asociarEnMap(funHash(v1, v2, g->cantVertices), d, g->MappAristas);
  return g;
}

/*
  Devuelve 'true' si y solo si 'v1' y 'v2' son vecinos.
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
bool sonVecinos(nat v1, nat v2, TGrafo g){
  assert( 1 <= v1 && v2 <= cantidadVertices(g));
  nat bucket = funHash(v1, v2, g->cantVertices);         
  return existeAsociacionEnMap(bucket, g->MappAristas);
}

/*
  Devuelve la distancia entre 'v1' y 'v2'.
  Precondición: sonVecinos(v1, v2, g).
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
double distancia(nat v1, nat v2, TGrafo g){
  assert(sonVecinos(v1, v2, g) && (1 <= v1 && v2 <= g->cantVertices));
  nat bucket = funHash(v1, v2, g->cantVertices);
  return valorEnMap(bucket, g->MappAristas);
}

/*
  Devuelve un 'TIterador' con los vecinos de 'v' ordenados de manera creciente.
  Precondición: 1 <= v <= N.
  El tiempo de ejecución en peor caso es O(n), siendo 'n' la cantidad de
  vecinos de 'v'.
 */
TIterador vecinos(nat v, TGrafo g){
  assert(1 <= v && v <= cantidadVertices(g));
  return enOrdenAvl(g->ArrayVertices[v]);
}

/*
  Libera la memoria asignada a 'g'.
  El tiempo de ejecuión en el peor caso en O(N + M), siend0 'N' y 'M' los
  parámetros pasados en crearGrafo.
 */
void liberarGrafo(TGrafo g){
    liberarMap(g->MappAristas);
    for(nat i = 1; i <= cantidadVertices(g); i++){
      liberarAvl(g->ArrayVertices[i]);
    }
    delete[] g->ArrayVertices;
    delete g;
}

