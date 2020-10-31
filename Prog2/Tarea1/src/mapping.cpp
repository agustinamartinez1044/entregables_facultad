/*
  Módulo de implementacón de 'TMapping'.

  Los elementos de tipo 'TMapping' son mappings cuyos elementos son
  asociaciones de 'nat' a 'double'.
  Puede haber hasta M asociaciones, siendo M un parámetro pasado al crear
  el 'TMapping'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/mapping.h"
#include "../include/cadena.h"
#include "../include/info.h"


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// struct repMap;
struct repMap{
  nat capacidad;
  nat cant;
  TCadena *hash;
};

static nat funhash(nat clave, TMapping map){ //FUNCIÓN AUXILIAR QUE DEVUELVE LA ASOCIACIÓN
  return (clave % map->capacidad);
}

/*
  Crea un 'TMapping' vacío (sin elementos) de asociaciones nat -> double.
  Podrá haber hasta M asociaciones.
  El tiempo de ejecución en el peor caso es O(M).
 */
TMapping crearMap(nat M){
  TMapping nuevo = new repMap;
  nuevo->capacidad = M;
  nuevo->cant = 0;
  nuevo->hash = new TCadena[M];
  for(nat i = 0; i < M; i++){
    nuevo->hash[i] = crearCadena();
  }
  return nuevo;
}

/*
  Inserta en 'map' la asociación entre 'clave' y 'valor'.
  Precondición: !estaLlenoMap(map) y !existeAsociacionEnMap(clave, map).
  Devuelve 'map'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TMapping asociarEnMap(nat clave, double valor, TMapping map){
  assert(!estaLlenoMap(map) && !existeAsociacionEnMap(clave, map));
  if(map != NULL){
    TInfo ins = crearInfo(clave, valor);
    map->hash[funhash(clave, map)] = insertarAlFinal(ins, map->hash[funhash(clave, map)]);
    map->cant++;
  }
  return map;
}

/*
  Elimina de 'map' la asociación correspondiente a 'clave' y libera la
  menoria  asignada a mantener esa asociación.
  Precondición: existeAsociacionenMap(clave, h).
  Devuelve 'map'.
  El 'TMapping' resultado comparte memoria con el parámetro'.
  El tiempo de ejecución es O(1) en promedio.
 */
TMapping desasociarEnMap(nat clave, TMapping map){
  assert(existeAsociacionEnMap(clave, map));
  if(map != NULL){
    int pos = funhash(clave,map); /*OPCIONES :- USAR CON SIGUIENTE CLAVE */    
    TLocalizador iterador = inicioCadena(map->hash[pos]);
    while((natInfo(infoCadena(iterador,map->hash[pos])) != clave) ){
      iterador = siguiente(iterador, map->hash[pos]);
    }
    removerDeCadena(iterador,map->hash[pos]); 
    map->cant--;
  }
  return map;
}

/*
  Devuelve 'true' si y solo si en 'map' hay una asociación correspondiente
  a 'clave'.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existeAsociacionEnMap(nat clave, TMapping map){
  bool esta = false;
  if( map != NULL){
    nat bucket = funhash(clave, map); /*preguntar desde el final al inicio si nat info == clave?          */

    TLocalizador iterador = finalCadena(map->hash[bucket]);
    while (esLocalizador(iterador) && natInfo(infoCadena(iterador,map->hash[bucket])) != clave ) {
      iterador = anterior(iterador, map->hash[bucket]);        
    }
    if(esLocalizador(iterador))
      esta = true;
  }
    return esta; 
  
}

/*
  Devuelve el valor correspondiente a la asociacion de 'clave' en 'map'.
  Precondición: existeAsociacionenMap(clave, map).
  El tiempo de ejecución es O(1) en promedio.
 */
double valorEnMap(nat clave, TMapping map){
  assert(existeAsociacionEnMap(clave, map));
  double res = 0;
  nat bucket = funhash(clave, map); 
  TLocalizador iterador = finalCadena(map->hash[bucket]);
  while (iterador != inicioCadena(map->hash[bucket]) && natInfo(infoCadena(iterador,map->hash[bucket])) != clave ) {
      iterador = anterior(iterador, map->hash[bucket]);        
    }
    res = realInfo(infoCadena(iterador,map->hash[bucket]));
  return res;
}

/*
  Devuelve 'true' si y solo si 'map' tiene 'M' elementos, siendo 'M' el
  parámetro pasado en crearMap.
  El tiempo de ejecución es O(1).
 */
bool estaLlenoMap(TMapping map){
  return (map->cant == map->capacidad);
}

/*
  Libera la memoria asignada a 'map' y todos sus elementos.
  El tiempo de ejecución en el peor caso es O(M), siendo 'M' el parámetro
  pasado en crearMap.
 */
void liberarMap(TMapping map){
  if(map != NULL){
    for(nat i = 0; i < map->capacidad; i++){
      if(map->hash[i] != NULL)
        liberarCadena(map->hash[i]);
    }
    delete[] map->hash;
    delete map;
    map = NULL;
  }
}
