/*
  Módulo de definición de 'usoTads'.

  Se definen funciones sobre tads.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/cadena.h"
#include "../include/binario.h"
#include "../include/utils.h"
#include "../include/conjunto.h"
#include "../include/grafo.h"
#include "../include/colaDePrioridad.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/float.h"

#include <stdio.h>  // sprintf
#include <stdlib.h>
#include <assert.h>


// nueva
/*
  Devuelve un arreglo que indica a cuales vértices se puede llegar desde 'v'.
  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.
  La coordenada 'i' (1 <= i <= N) es 'true' si y solo si el vértice 'i' es
  accesible desde 'v'.
  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Inicializar cada coordenada del arreglo a devolver con 'false'
     (se considera cada vértice no accesible).
   - Pasar 'v' como parámetro a una función auxiliar. Esta función
     -- marca el parámetro como accesible desde 'v'.
     -- para cada vécino de su parámetro que todavía sea no accesible
        desde 'v' hace una llamada recursiva.
   - Devolver el arreglo.
 */


static void vecinosTambAccesibles(nat vertice, ArregloBools &res, TGrafo g){
  
  res[vertice] = true;
  TIterador veci = vecinos(vertice, g);
  veci = reiniciarIterador(veci);
  
  while(estaDefinidaActual(veci)){
    if(res[actualEnIterador(veci)] == false ){
      vecinosTambAccesibles(actualEnIterador(veci), res, g);
      veci = avanzarIterador(veci);
    }
    else
      veci = avanzarIterador(veci);
  }
  liberarIterador(veci);
}

ArregloBools accesibles(nat v, TGrafo g){
  ArregloBools res = new bool[cantidadVertices(g) +1 ];
  for(nat i = 1; i <= cantidadVertices(g); i++){
      res[i] = false;
  }
  vecinosTambAccesibles(v, res, g);
  return res;
}

// nueva.5

/*
  Devuelve un arreglo con las longitudes de los caminos más cortos desde 'v'
  hasta cada vértice del grafo.

  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.

  En la coordenada 'i' (1 <= i <= N) se devuelve la longitud del camino más
  corto desde 'v' hasta 'i'. Si 'i' no es accesible desde 'v' el valor de esa
  coordenada es DBL_MAX (definido en float.h)

  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Crear colecciones 'C' y 'S', inicialmente vacías, de pares (u,du)
     donde 'u' representa un vértice y 'du' es la longitud del camino más
     corto desde 'v' hasta 'u'. El valor de 'du' en 'C' es provisorio
     mientras que en 'S' es definitivo.

   - Insertar (v,0) en 'C'.
   . Mientras 'C' no es vacía:
     -- se obtiene y remueve de 'C' el par (u, du) tal que 'du' es mínimo
        entre todos los pares de 'C'.
     -- se inserta ese par en 'S'.
     -- para cada vecino 'w' de 'u' que no está en S sea dw' = du + d(u,w),
        donde d(u,v) es la distancia entre 'u' y 'w'.
        Si 'w' no está en 'C' se inserta (w,dw') en 'C'.
        Si 'w' está en 'C' en el par (w,dw) y dw' < dw entoces se actualiza
        'C' con el par con (w,dw') en lugar de (w,dw).
   - Para cada vétice 'u' que no pertenece a 'S' se inserta en 'S' el par
     (u, infinito).
   - Devolver 'S'.

 */

ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g){

  //INICIALMENTE VACÍAS
  TColaDePrioridad C = crearCP(cantidadVertices(g) + 1);
  double *S = new double[cantidadVertices(g) + 1];
  for(nat i = 1; i <= cantidadVertices(g); i++){
    S[i] = DBL_MAX;
  }

  //POR SER VECINOS DIRECTO NO QUIERE DECIR QUE TENGA MENOR DISTANCIA
  TIterador vecis = vecinos(v, g); //Todos los vecinos de v en un iterador
  vecis = reiniciarIterador(vecis);

  //CREO TODO EL C CON LAS DISTANCIAS DE LOS VECINOS DIRECTOS
  while(estaDefinidaActual(vecis)){ //COLA PERO CON LA DISTANCIA DE TODOS LOS VECINOS
    double dist = distancia(v, actualEnIterador(vecis), g);
    C = insertarEnCP(actualEnIterador(vecis), dist, C);
    vecis = avanzarIterador(vecis);
  }
  liberarIterador(vecis);

  //C = insertarEnCP(v, 0, C); 
  S[v] = 0;
  while(!estaVaciaCP(C)){

    //INSERTO EL PRIORITARIO
    nat vecinoU = prioritario(C);
    //if(S[vecinoU] == DBL_MAX)
      S[vecinoU] = prioridad(vecinoU, C);

    //ME FIJO TODOS LOS VECINOS DEL PRIORITARIO, SI LA DISTANCIA ES MENOR LA ACTUALIZO
    /*para cada vecino 'w' de 'u' que no está en S sea dw' = du + d(u,w),
     donde d(u,v) es la distancia entre 'u' y 'w'. */
    TIterador vecinosDeU = vecinos(vecinoU, g);
    vecinosDeU = reiniciarIterador(vecinosDeU);

    /*Si 'w' no está en 'C' se inserta (w,dw') en 'C'.
      Si 'w' está en 'C' en el par (w,dw) y dw' < dw entoces se actualiza
      'C' con el par con (w,dw') en lugar de (w,dw). */
    while(estaDefinidaActual(vecinosDeU)){ // vecinoU = prioritario en C = u
      if(S[actualEnIterador(vecinosDeU)] == DBL_MAX){
        //          distancia (u, v)      +    distancia de (u, w)
        double dw = prioridad(vecinoU, C) + distancia(vecinoU, actualEnIterador(vecinosDeU), g);
        if(!estaEnCP(actualEnIterador(vecinosDeU), C))
          C = insertarEnCP(actualEnIterador(vecinosDeU), dw, C);
        else{
          if(prioridad(actualEnIterador(vecinosDeU), C) >= dw)
            C = actualizarEnCP(actualEnIterador(vecinosDeU), dw, C);
        }
        
      }
      vecinosDeU = avanzarIterador(vecinosDeU);
     }


    C = eliminarPrioritario(C);
    liberarIterador(vecinosDeU);
  }
  liberarCP(C);
  return S;
}



// nueva.4
/*
  Devuelve un 'TConjunto' con los elementos que pertenecen a 'c1' y 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n1 + n2 + n.log n),
  siendo 'n1' y 'n2' la cantidad de elementos de 'c1' y 'c2' respectivamente y
  'n' la del 'TConjunto' resultado.
 */
TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){ //TEORÍA DE CONJUNTOS
  TConjunto diferenciaC1C2 = diferenciaDeConjuntos(c1,c2);
  TConjunto interseccion = diferenciaDeConjuntos(c1, diferenciaC1C2);
  liberarConjunto(diferenciaC1C2);
  return interseccion;
}


/*
  Devuelve una 'TCadena' con los elementos del nivel 'l' de 'b'.
  La raíz es el nivel 1.
  La 'TCadena' resultado debe estar ordenada de manera creciente según los
  componentes naturales de sus elementos.
  Precondición: l > 0.
  La 'TCadena' devuelta no comparte memoria con 'b'.
 */
static void binarionivel (nat l, TBinario b, TCadena &cad){
  if( b!= NULL && l > 0){
    if(l == 1)
      cad = insertarAlFinal(copiaInfo(raiz(b)), cad);  
    else {
      binarionivel(l-1, izquierdo(b), cad);
      binarionivel(l-1, derecho(b), cad);
    }
  }
}

TCadena nivelEnBinario(nat l, TBinario b){
    assert(l > 0);
    TCadena res = crearCadena();
    binarionivel(l, b, res);
    return res;
}

// nueva.3
/*
  Devuelve 'true' si y solo si en 'b' hay un camino desde la raiz hasta una
  hoja que sea compatible con 'c'.
  Decimos que una cadena y un camino son compatibles si tienen la misma
  longitud y al recorrer la cadena desde el inicio hasta el final y el camino
  desde la raíz hasta la hoja los componentes naturales de los respectivos
  elementos son iguales.
  Ver ejemplos en la letra.
  Si 'b' y 'c' son vacíos devuelve 'true'.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' es la cantidad de
  elementos de 'b'.
 */

static void es_auxmino(TCadena cad, TBinario b,TLocalizador localizador, bool &auxBool){
  if (!auxBool){
    if(!localizadorEnCadena(localizador,cad) && b == NULL){
      auxBool = true;    
    }else if(b == NULL && localizadorEnCadena(localizador,cad)){
      auxBool = false;
    }else if (b != NULL && !localizadorEnCadena(localizador,cad)){
      auxBool = false;
    }else if (natInfo(infoCadena(localizador,cad)) == natInfo(raiz(b))){
      if(derecho(b) == NULL && izquierdo(b) != NULL ){
        es_auxmino(cad,izquierdo(b),siguiente(localizador,cad), auxBool);
      }else if (derecho(b) != NULL && izquierdo(b) == NULL){
        es_auxmino(cad,derecho(b),siguiente(localizador,cad), auxBool);
      }else{
        es_auxmino(cad,derecho(b),siguiente(localizador,cad), auxBool);
        if (!auxBool){
          es_auxmino(cad,izquierdo(b),siguiente(localizador,cad), auxBool);
        }
      }
    }else{
      auxBool = false;
    }
  }
}

bool esCamino(TCadena c, TBinario b){
  bool auxBool = false;
  TLocalizador localizador = inicioCadena(c);
  es_auxmino(c,b,localizador, auxBool);
  return auxBool;
}
/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
bool pertenece(nat elem, TCadena cad){
  TLocalizador aux = inicioCadena(cad);
  bool res = false;
  while((aux!=NULL) && (natInfo(infoCadena(aux, cad)) != elem))
    aux = siguiente(aux, cad);
  if (localizadorEnCadena(aux, cad))
    res = (natInfo(infoCadena(aux, cad)) == elem);
  return res;

}

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad){
  int cant = 0;
  TLocalizador aux = inicioCadena(cad);
  while(aux!=NULL){
    cant++;
    aux = siguiente(aux, cad);
  }
  return cant;
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad){
  bool res = true;
  if (!esVaciaCadena(cad)){
    TLocalizador aux = inicioCadena(cad);
    while ((siguiente(aux,cad)!=NULL) && ((natInfo(infoCadena(aux,cad)))<=(natInfo(infoCadena(siguiente(aux,cad),cad))))){
      aux = siguiente(aux, cad);    
    }
    res = (siguiente(aux,cad) == NULL);
  }
  return res;
}

/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad){
  bool res = false;
  if(!esVaciaCadena(cad)){
    TLocalizador elem = inicioCadena(cad);
    nat clave = natInfo(infoCadena(elem, cad));
    while(!esFinalCadena(elem, cad) && !esLocalizador(siguienteClave(clave, siguiente(elem, cad), cad))){
      elem = siguiente(elem, cad);
      clave = natInfo(infoCadena(elem, cad));
    }
    res = (esLocalizador(siguienteClave(clave, elem, cad)) && elem != finalCadena(cad));
  }
  return res;
}

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2){
    bool res;
  if(esVaciaCadena(c1) && esVaciaCadena(c2))
    res = true;
  else{
    if( !esVaciaCadena(c1) && !esVaciaCadena(c2)){
      TLocalizador aux1 = inicioCadena(c1);
      TLocalizador aux2 = inicioCadena(c2);
      bool iguales = sonIgualesInfo(infoCadena(aux1, c1), infoCadena(aux2, c2));
      while(esLocalizador(siguiente(aux1, c1)) && esLocalizador(siguiente(aux2, c2)) && iguales){
        aux1 = siguiente(aux1, c1);
        aux2 = siguiente(aux2, c2);
        if(sonIgualesInfo(infoCadena(aux1, c1), infoCadena(aux2, c2)))
          iguales = true;
      }
      if (esFinalCadena(aux1, c1) && esFinalCadena(aux2, c2) && sonIgualesInfo(infoCadena(finalCadena(c1), c1), infoCadena(finalCadena(c2), c2)))
        res = true;
      else 
        res = false;
    }
    else
      res = false; 
  }
  return res;
  
}

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2){
    TCadena base = crearCadena();
   if(!esVaciaCadena(c1) && esVaciaCadena(c2)){
     base = insertarSegmentoDespues(copiarSegmento(inicioCadena(c1),finalCadena(c1), c1), inicioCadena(base), base);
     
    }
    else{
      if(esVaciaCadena(c1) && !esVaciaCadena(c2)){
        base = insertarSegmentoDespues(copiarSegmento(inicioCadena(c2),finalCadena(c2), c2), inicioCadena(base), base);
       
      }
      else{
        if(!esVaciaCadena(c1) && !esVaciaCadena(c2)){
          base =insertarSegmentoDespues(copiarSegmento(inicioCadena(c1),finalCadena(c1), c1), inicioCadena(base), base);
          TCadena enlace = copiarSegmento(inicioCadena(c2),finalCadena(c2), c2);
          TLocalizador enlazar = finalCadena(base);
          base = insertarSegmentoDespues(enlace,enlazar, base);
        }
      }
    }
  return base;
}

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad){
    assert(!hayNatsRepetidos(cad));
  if(!esVaciaCadena(cad)){
    TLocalizador segmento = inicioCadena(cad);
    TLocalizador menor = menorEnCadena(segmento,cad);
    while(esLocalizador(siguiente(segmento, cad))){
      intercambiar(segmento,menor, cad);
      segmento = siguiente(segmento, cad);
      menor = menorEnCadena(segmento, cad);
    }
  }
  return cad;
}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
    if(!esVaciaCadena(cad)){
    TLocalizador locc = inicioCadena(cad);
    nat elem = natInfo(infoCadena(locc, cad));
    double real;
    TInfo ins;
    while(esLocalizador(siguiente(locc, cad))){
      if(elem == original){
        real = realInfo(infoCadena(locc, cad));
        ins = crearInfo(nuevo, real);
        liberarInfo(infoCadena(locc,cad));
       cambiarEnCadena(ins, locc, cad);
      }
    locc = siguiente(locc,cad);
    elem = natInfo(infoCadena(locc, cad));
    }
    if ((esFinalCadena(locc,cad)) && (elem == original)){
       real = realInfo(infoCadena(locc, cad));
        ins = crearInfo(nuevo, real);
        liberarInfo(infoCadena(locc,cad));
       cambiarEnCadena(ins, locc, cad);
    }

  }
  return cad;
}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad){
    assert ((estaOrdenadaPorNaturales (cad)) && (menor <= mayor) && (pertenece (menor, cad)) && (pertenece (mayor, cad)));
  TCadena res;
  if(!esVaciaCadena(cad)){

     TLocalizador cursordesde = inicioCadena(cad);
     while(menor != natInfo(infoCadena(cursordesde, cad))){
       cursordesde = siguiente(cursordesde, cad);
     }
     TLocalizador cursorhasta = finalCadena(cad);
     while(mayor != natInfo(infoCadena(cursorhasta, cad))){
       cursorhasta = anterior(cursorhasta, cad);
     }
     
    res = copiarSegmento(cursordesde, cursorhasta, cad); 
  }
  else
    res = crearCadena();
  
  return res;

}