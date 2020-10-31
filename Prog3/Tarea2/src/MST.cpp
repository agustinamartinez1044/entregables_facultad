/*
  Módulo de implementación de `MST'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/MST.h"
#include "../include/cola_de_prioridad.h"
#include "../include/pila.h"
#include <climits>
#include <stdio.h>

/**
 * Precondiciones:
 *  - 'G' es un grafo no dirigido, conexo, compuesto de 'n'
 *     vertices y 'm' aristas. Los vertices se numeran del 1 al n.
 *     Cada arista de 'G' tiene un peso distinto asociado, mayor a 0.
 *
 * Postcondiciones:
 *  - Devuelve el costo total de un árbol de cubrimiento mínimo de G
 *  - Devuelve en la variable mst un árbol de cubrimiento mínimo de G
 *  - El tiempo de ejecucion de Prim debe ser O(mlog(n)).
 *  - El grafo pasado como entrada NO DEBE SER MODIFICADO.
 **/
nat Prim(Grafo G, Grafo &mst) {
  Grafo copiaG = copia_grafo(G);
  

	return 0;
}

/*
La idea fundamental consiste en añadir en cada paso una arista de peso mínimo a un árbol previamente construido. Para verlo de un modo más explícito, se definen los siguientes pasos:

Se elige un vértice U de G y se considera el árbol S={U}.
Se considera la arista e de mínimo peso que une un vértice de S y un vértice que no es de S, y se hace S=S+e .
Si el número de aristas de T es n-1, el algoritmo termina. En caso contrario, volveríamos al paso 2.
*/

Grafo grafo_arista(Grafo T, nat v, nat w, nat costo) {

	return crear_grafo(1);
}
