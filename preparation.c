#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/
typedef struct node {
		short data ;
		struct node *link ;
		} Lnode ;


/* Insertion en "tête de liste" */
void insertionTete(Lnode** ph,short item)
  {
    Lnode* cell;
    cell = malloc(sizeof(Lnode));
    cell->link = *ph;
    cell->data = item;
    ph = &cell;
  }

/* Insertion en "queue de liste" */
void insertionQueue(Lnode** ph,short item)
  {
    Lnode* cell;
    Lnode* buffer;
    cell = malloc(sizeof(Lnode));
    buffer = *ph;

    while(buffer != NULL) buffer = buffer->link;

    cell->data = item;
    cell->link = NULL;
    buffer->link = cell;

  }

/* Suppression en "tête de liste" */
void suppressionTete(Lnode** ph)
  {
    Lnode* buffer = *ph;
    ph = &(buffer->link);
    free(buffer);
  }

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode** ph)
  {
    Lnode* buffer;
    Lnode* buffer2;
    buffer = *ph;

    while(buffer->link != NULL) buffer = buffer->link;

    buffer2 = buffer->link;
    buffer->link = NULL;
    free(buffer2);
  }

  /* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode* ptr)
  {
  	if ( NULL == ptr )
  		printf("Liste vide!") ;
  	else
  		printf("Contenu de la liste : ") ;
  	while ( NULL != ptr ) 	{
  		printf("%hd ",ptr->data);
  		ptr = ptr->link ;
  		}
  	printf("\n") ;
  }

  int main(void) {
  	Lnode *tete = NULL ;

  	listeAffiche(tete) ;
  	insertionTete(&tete,'a') ;
  	listeAffiche(tete) ;
  	insertionTete(&tete,'c') ;
  	listeAffiche(tete) ;
  	insertionQueue(&tete,'t') ;
  	listeAffiche(tete) ;
  	insertionQueue(&tete,'s') ;
  	listeAffiche(tete) ;
  	suppressionTete(&tete) ;
  	listeAffiche(tete) ;
  	suppressionTete(&tete) ;
  	listeAffiche(tete) ;
  	suppressionQueue(&tete) ;
  	listeAffiche(tete) ;
  	suppressionTete(&tete) ;
  	listeAffiche(tete) ;

     return EXIT_SUCCESS;
     }
