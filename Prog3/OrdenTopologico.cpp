/*5001764*/
/*
  Módulo de implementación de `OrdenTopologico'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/lista.h"
#include "../include/grafo.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Lista OrdenTopologico(Grafo G)
{
  if (cantidad_vertices(G) == 0)
  {
    return crear_lista();
  }
  else
  {
    Grafo copiaG = copia_grafo(G);
    Lista OrdenElementos = crear_lista();
    Lista incidencidenciaCero = crear_lista();
    nat i = 1;
    while (i < max_vertice(G))
    {
      if ((existe_vertice(i, copiaG)) && (in_grado(i, copiaG) == 0))
      {
        insertar_al_final(i, incidencidenciaCero);
      }
      i++;
    }
    comienzo(incidencidenciaCero);
    while (!es_vacia_lista(incidencidenciaCero))
    {
      comienzo(incidencidenciaCero);
      nat n = actual(incidencidenciaCero);
      insertar_al_final(n, OrdenElementos);
      Lista adyacentesN = copia_lista(adyacentes(n, copiaG));
      while (!es_vacia_lista(adyacentesN))
      {
        comienzo(adyacentesN);
        nat m = actual(adyacentesN);
        remover_arista(n, m, copiaG);
        if (in_grado(m, copiaG) == 0)
        {
          insertar_al_final(m, incidencidenciaCero);
        }
        remover_al_inicio(adyacentesN);
      }
      destruir_lista(adyacentesN);
      remover_al_inicio(incidencidenciaCero);
      remover_vertice(n, copiaG);
    }
    destruir_lista(incidencidenciaCero);
    if (cantidad_vertices(copiaG) == 0)
    {
      destruir_grafo(copiaG);
      return OrdenElementos;
    }
    else
    {
      destruir_lista(OrdenElementos);
      bool *visitados = new bool[max_vertice(G)+1];
      for(nat i =1; i < max_vertice(G)+1; i++){
        visitados[i] = false;
      }
      Lista verticesV = (vertices(copiaG));
      comienzo(verticesV);
      nat v = actual(verticesV);
      Lista nodosVisitados = crear_lista();
      bool hayCiclo = false;
      while (!hayCiclo)
      {
        if (visitados[v])
        {
          hayCiclo = true;
        }
        else
        {
          visitados[v] = true;
          insertar_al_inicio(v, nodosVisitados);
          Lista in = copia_lista(incidentes(v, copiaG));
          comienzo(in);
          v = actual(in);
          destruir_lista(in);
        }
      }
      insertar_al_inicio(v, nodosVisitados);
      while(!es_vacia_lista(nodosVisitados) && ultimo(nodosVisitados)!= v ){
        remover_al_final(nodosVisitados);
      }
      destruir_grafo(copiaG);
      destruir_lista(verticesV);
      delete [] visitados;
      return nodosVisitados;
    }
  }
}
