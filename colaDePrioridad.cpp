/*
  Módulo de implementación de 'TColaDePrioridad'.

  Los elementos de tipo 'TColaDePrioridad' son colas de prioridad cuyos
  elementos son de tipo 'nat' entre 1 y N, siendo N un parámetro pasado al
  crear la cola de prioridad.
  No hay elementos repetidos.
  La prioridad asociada al elemento es de tipo double y la determina un valor
  estalecido al insertar el elemento. Ese valor puede ser modificado.
  Un elemento es prioritario ante otro si su valor asociado es menor.
  Si hay más de un elemento con mínimo valor asociado cualquiera de ellos es
  el prioritario. 


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/colaDePrioridad.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/info.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// struct repCP;
struct repCP{
  nat max;         //valor máximo que puede tener un elemento de 'cp', parámetro de crearCP.
  nat tope;         //para saber en O(1) si hay elementos y cuantos hay
  TInfo *ColaP;     //arreglo del heap
  nat *posiciones;  //posiciones de los elementos en O(1)
};
/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N){
  TColaDePrioridad resultado = new repCP;
  resultado->max = N;
  resultado->tope = 0;
  resultado->ColaP = new TInfo[N + 1];
  resultado->posiciones = new nat[N + 1];
  for(nat i = 1; i <= N; i++){
    resultado->posiciones[i] = 0; 
    resultado->ColaP[i] = NULL;
  }
  return resultado;
}


//////////////////////////FUNCIONES AUXILIARES PARA FILTARAR//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
static void filtradoDescendente(TColaDePrioridad &cp, nat pos){
  
  nat hijoMayor = pos*2;  //Posicion del hijo
  bool filtrado = false;
  while (hijoMayor <= cp->tope && !filtrado){
    if((hijoMayor+1 <= cp->tope) && (realInfo(cp->ColaP[hijoMayor+1]) < realInfo(cp->ColaP[hijoMayor]))) //Tomo el menor de los hijos
      hijoMayor = hijoMayor + 1; //Si la prioridad del hijo derecho es mayor sigue con ese
                                //Sino continua con el hijo izquierdo
    if(realInfo(cp->ColaP[pos]) < realInfo(cp->ColaP[hijoMayor])) //Si prioridad del hijo es mayor que el padre esta bien ordenado
      filtrado = true;
    else{
      TInfo infoPadre = copiaInfo(cp->ColaP[pos]);
      TInfo infoHijo = copiaInfo(cp->ColaP[hijoMayor]);

      liberarInfo(cp->ColaP[pos]);
      cp->ColaP[pos] = infoHijo;
      liberarInfo(cp->ColaP[hijoMayor]);
      cp->ColaP[hijoMayor] = infoPadre;

      nat elemPadre = natInfo(infoPadre);
      nat elemHijo = natInfo(infoHijo);
      nat posAuxPadre = cp->posiciones[elemPadre];

      cp->posiciones[elemPadre] = cp->posiciones[elemHijo];
      cp->posiciones[elemHijo] = posAuxPadre;

      pos = hijoMayor;
      hijoMayor = hijoMayor*2;
    }
  }
}

static void filtradoAscendenteRec(TColaDePrioridad &cp, nat pos){ 
	if (pos > 1){
		if((realInfo(cp->ColaP[pos/2])) > (realInfo(cp->ColaP[pos]))){ //si el padre es prioritario respecto al hijo
			cp->posiciones[natInfo(cp->ColaP[pos])] = pos/2;
			cp->posiciones[natInfo(cp->ColaP[pos / 2])] = pos;
		  TInfo swap = cp->ColaP[pos/2];	 
      cp->ColaP[pos/2] = cp->ColaP[pos];
  		cp->ColaP[pos] = swap;
      filtradoAscendenteRec(cp, pos/2); 
	  }
  }
}

//////////////////////////////////PARA INSERTAR Y REMOVER/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

/*
  Devuelve el valor máximo que puede tener un elemento de 'cp', que es el
  parámetro de crearCP.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat rangoCP(TColaDePrioridad cp){
  return cp->max;
}
/*
  Inserta 'elem' en 'cp'. La prioridad asociada a 'elem' es 'valor'.
  Precondición 1 <= elem <= rangoCP(cp).
  Precondición: !estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){ // !!? insertar segun la prioridad
  assert( (1 <= elem && elem <= rangoCP(cp)) && (!estaEnCP(elem, cp)));
  cp->tope++;
  TInfo nuevo = crearInfo(elem, valor);
  cp->ColaP[cp->tope] = nuevo;
  cp->posiciones[elem] = cp->tope;
  filtradoAscendenteRec(cp, cp->tope);
  return cp;
}
/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp){
  return cp->tope == 0;
}
/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVacioCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp){
  assert(!estaVaciaCP(cp));
  return natInfo(cp->ColaP[1]);
}

/*
  Elimina de 'cp' el elemento prioritario.
  Precondición: !estaVacioCP(cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */

static void eliminarMenor(TColaDePrioridad &cp){
	int i = 1;                                                                      
    
	cp->posiciones[natInfo(cp->ColaP[i])] = 0;
	liberarInfo(cp->ColaP[i]);
	if( cp->tope != 1){ 
	
        cp->ColaP[i] = cp->ColaP[cp->tope];                     
        cp->posiciones[natInfo(cp->ColaP[cp->tope])] = i; 
        cp->tope = cp->tope-1;
        filtradoDescendente(cp,i);
  } 
  else{
    cp->tope = cp->tope -1; 
  } 
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
 eliminarMenor(cp);
 return cp;
}

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp){
  return cp->posiciones[elem] != 0;
}

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
double prioridad(nat elem, TColaDePrioridad cp){
  /*nat pos = cp->posiciones[elem];
  return realInfo(cp->ColaP[pos]);
  */
 double res = realInfo(cp->ColaP[cp->posiciones[elem]]);
 return res;
}

/*
  Modifica el valor de la propiedad asociada a 'elem'; pasa a ser 'valor'.
  Precondición: estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */


TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
  assert(estaEnCP(elem,cp));
  TInfo nuevo = crearInfo(elem,valor);                      //Creo Info con valor actualizado
  nat posicionDeElem = cp->posiciones[elem];                //Guardo posicion de elem en el heap
  double anteriorPri = realInfo(cp->ColaP[posicionDeElem]);  //Guardo valor antes de actualizarlo para comparar
  liberarInfo(cp->ColaP[posicionDeElem]); 
  cp->ColaP[posicionDeElem] = nuevo;
  if (valor < anteriorPri)
    filtradoAscendenteRec(cp,posicionDeElem);
  else if (valor >= anteriorPri)
    filtradoDescendente(cp,posicionDeElem);
  return cp;
}

/*
  Libera la menoria asignada a 'cp'.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp){
  if(cp != NULL){
	  for(nat i = 1; i <= cp->tope; i++)  //hasta "max" da error en tiempo de ejecución
      liberarInfo(cp->ColaP[i]);
    delete[] cp->ColaP;    //dudoso
	  delete[] cp->posiciones;
	  delete cp;
    cp = NULL;
  }
}