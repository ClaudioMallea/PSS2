#include <stdio.h>
#include <stdlib.h>
#include "colapri.h"
#include "colapri-arreglo.h"
#include <string.h>
/* La idea principal de una colapri es que no se sabe
 * que' almacena el arreglo.  Podria almacenar strings,
 * punteros a personas, punteros a longs e incluso longs,
 * pero el codigo de este archivo no cambia.
 *
 * Lo unico que se requiere es que el que cree la cola de prioridades
 * con nuevaColaPri debe suministrar su tamaño maximo
 * y una funcion 'comp' que sirva para comparar prioridades.
 */
typedef struct node {
  void* valor;
  struct node *next;
} Node;

typedef struct {
  ColaPriOps *ops;
  CompPri comp;
  Node* nodo;
  int n;
} ColaPriLista; /* ColaPriLista no es un puntero, ColaPri si lo es */

static void agregar(ColaPri colapri, void *a);
static void* extraer(ColaPri colapri);
static void* mejor(ColaPri colapri);
static int tamano(ColaPri colapri);
static void destruir(ColaPri colapri); /* debe estar vacia */
static IterColaP iterador(ColaPri colapri);

/*******************************************
 * Implementacion de la cola de prioridades
 *******************************************/
static ColaPriOps colapri_lista_ops= {
  agregar, extraer, mejor, tamano, destruir, iterador
};

ColaPri nuevaColaPriLista(CompPri comp) {
  ColaPriLista *cp= malloc(sizeof(ColaPriLista));
  cp->ops= &colapri_lista_ops;
  cp->comp= comp;
  cp->nodo= malloc(sizeof(Node));
  cp->n=0;
  /*cp->nodo->valor=NULL;*/
  cp->nodo->next=NULL;
  return (ColaPri)cp;
}
/* Los elementos estan ordenados de mejor a peor prioridad */
static void agregar(ColaPri colapri, void *a) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
    Node* start = cp->nodo; 
 
    Node *temp= (Node*)malloc(sizeof(Node));
    temp->valor= a;
    temp->next= NULL;
    
    
    
  
  
    
  if(cp->n==0){

    
    cp->nodo->valor=a;
    
    cp->n++;  
  }


  else{

    if ( (*cp->comp)(a, start->valor)<0) { 
        temp->next = cp->nodo; 
        cp->nodo = temp; 
        cp->n++;
      } 
    else { 
        while (start->next != NULL && 
               ((*cp->comp)(a, start->next->valor)>0 )) { 
            start = start->next;
            
        } 
        temp->next = start->next; 
        start->next = temp; 
        cp->n++;  
      } 
  }
}





static void* mejor(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
  
  return cp->nodo->valor;
}


static int tamano(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;  
    return cp->n;
}

static void* extraer(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
  void *res= cp->nodo->valor;
  Node *sgte= cp->nodo->next;

  if(cp->n==1){
  cp->nodo->valor=NULL;

  }
  else{
  cp->nodo->next=sgte->next;  
  cp->nodo->valor=sgte->valor;
  }

  cp->n--;
  return res;
  
}

static void destruir(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
  free(cp);  
}

/*******************************************
 * Implementacion de la cola de prioridades
 *******************************************/

typedef struct {
  IterColaPOps *ops;
  ColaPriLista *cp;
  int k;
} IterColaPLista;

static int continua(IterColaP iter);
static void* proximo(IterColaP iter);
static void destruirIter(IterColaP iter);

static IterColaPOps iterOps= { continua, proximo, destruirIter };

IterColaP iterador(ColaPri colapri) {
  IterColaPLista *iter= malloc(sizeof(IterColaPLista));
  iter->ops= &iterOps;
  iter->cp= (ColaPriLista*)colapri;
  iter->k= 0;
  return (IterColaP)iter;
}

static int continua(IterColaP itercp) {
  IterColaPLista *iter= (IterColaPLista*)itercp;

  return iter->k < iter->cp->n;;
}

static void *proximo(IterColaP itercp) {
  IterColaPLista *iter= (IterColaPLista*)itercp;

  Node* NodoActual=iter->cp->nodo;
  int i=0;
  while(1){
    if(i==iter->k){
      break;
    }
    NodoActual=NodoActual->next;
    i++;
  }

  iter->k++;
  return NodoActual->valor;
}

static void destruirIter(IterColaP iter) {
  free(iter);
}

