/*5001764*/
/*
  Módulo de implementación de `caminos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/caminos.h"
#include "../include/lista.h"
#include "../include/grafo.h"
#include "../include/cola.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cstddef>

nat *CantCaminos(Grafo G, nat s){
  Grafo copiaG = copia_grafo(G);

  bool *visitados = new bool[cantidad_vertices(copiaG) + 1];
  for (nat i = 1; i < cantidad_vertices(copiaG) + 1; i++){
    visitados[i] = false;
  }
  nat *cantC = new nat[cantidad_vertices(copiaG) + 1];
  for (nat i = 1; i < cantidad_vertices(copiaG) + 1; i++){
    cantC[i] = 0;
  }
  nat *nivel = new nat[cantidad_vertices(copiaG) + 1];
  for (nat i = 1; i < cantidad_vertices(copiaG) + 1; i++){
    nivel[i] = 0;
  }
  
  visitados[s] = true;
  cantC[s] = 1;

  Cola vertices = crear_cola();
  encolar(s, vertices);

  while (!es_vacia_cola(vertices)){

    nat vertice = frente(vertices);
    desencolar(vertices);
    Lista adyacentesVertice = copia_lista(adyacentes(vertice, copiaG));

    while (!es_vacia_lista(adyacentesVertice)){

      nat verticeAd = primero(adyacentesVertice);
      
      if (!visitados[verticeAd]){
        visitados[verticeAd] = true;
        cantC[verticeAd] = cantC[verticeAd] + cantC[vertice];
        nivel[verticeAd] = nivel[vertice] + 1;
        encolar(verticeAd, vertices);
      }
      else if (nivel[vertice] < nivel[verticeAd]){
        cantC[verticeAd] = cantC[vertice] + cantC[verticeAd];
      }
      
      remover(primero(adyacentesVertice), adyacentesVertice);
    }

    destruir_lista(adyacentesVertice);

  }

  destruir_cola(vertices);
  destruir_grafo(copiaG);
  delete[] visitados;
  delete[] nivel;
  return cantC;

}
