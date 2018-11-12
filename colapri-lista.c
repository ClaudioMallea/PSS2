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
  cp->nodo= malloc(sizeof(Node*));
  return (ColaPri)cp;
}

/* Los elementos estan ordenados de mejor a peor prioridad */
static void agregar(ColaPri colapri, void *a) {
  ColaPriLista *cp= (ColaPriLista*)colapri;

    Node* start = cp->nodo; 
    Node NodoVacio= {NULL, NULL};

    void *prev= a;
 
    Node *n1= malloc(sizeof(Node));
    n1->valor= prev;
    n1->next= &NodoVacio;
    

    Node* temp = n1;
 


    
  if(cp->nodo->valor==NULL){

    
    Node *ins= malloc(sizeof(Node));
    ins->valor= prev;
    ins->next= &NodoVacio;
    cp->nodo= ins;
    start=cp->nodo;
  
    
  }
  else{
    if ( (*cp->comp)(a, start->valor)<0) { 
        temp->next = cp->nodo; 
        cp->nodo = temp; 

    } 
    else { 
        
  


        while (start->next != &NodoVacio && 
               (*cp->comp)(a, start->next->valor)>0 ) { 
        
            start = start->next;
            
        } 

        temp->next = start->next; 
        start->next = temp; 
   
      
        
    } }

}





static void* mejor(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
  
  return cp->nodo->valor;
}





static int tamano(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
    Node* n=cp->nodo;
    int j=0;
     while (n->valor!=NULL) {
      
      n= n->next;
      j++;
    }
    
    return j;
}

static void* extraer(ColaPri colapri) {
  ColaPriLista *cp= (ColaPriLista*)colapri;
  void *res= cp->nodo->valor;
  cp->nodo=cp->nodo->next;
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
    Node* n=iter->cp->nodo;
    int j=0;
     while (n->valor!=NULL) {     
      n= n->next;
      j++;
    }
  
  return iter->k < j;
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

