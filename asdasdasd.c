 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>



  typedef struct node {
    int x;
    struct node *next;
  } Node;


    void mostrarLista(Node *n) {
    while (n!=NULL) {
      printf("%d ", n->x);
      n= n->next;
    }
    printf("\n"); /* Fin de línea */
  }


    void insertar(Node **ppnode, int y) {
    Node *pnode= *ppnode;
    while (pnode != NULL  &&  pnode->x < y) {
      ppnode= & pnode->next;
      pnode= *ppnode;
    }
  
    Node *ins= malloc(sizeof(Node));
    ins->x= y;
    ins->next= pnode;
    *ppnode= ins;
  }


    int main() {
    Node n1= {5, NULL};
    Node n2= {1, &n1};
    Node *h= &n2;
    mostrarLista(h);
    insertar(&h, 3);
    mostrarLista(h);
    return 0;
  }