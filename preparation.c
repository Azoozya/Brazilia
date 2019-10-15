
/* Insertion en "tête de liste" */
void insertionTete(Lnode** ph,short item)
  { REMPLI MOI CHAGASSE }

/* Insertion en "queue de liste" */
void insertionQueue(Lnode** ph,short item)
  { REMPLI MOI CHAGASSE }

/* Suppression en "tête de liste" */
void suppressionTete(Lnode** ph)
  { REMPLI MOI CHAGASSE }

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode** ph)
  { REMPLI MOI CHAGASSE }

  /* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode* ptr)
  {
  	if ( NULL == ptr )
  		printf("Liste vide!") ;
  	else
  		printf("Contenu de la liste : ") ;
  	while ( NULL != ptr ) 	{
  		printf("%hd ",ptr->data);
  		ptr = ptr->next ;
  		}
  	printf("\n") ;
  }

int main(int argc,char* argv[])
{

  // listeAffiche(tete) ;
  // insertionTete(&tete,'a') ;
  // listeAffiche(tete) ;
  // insertionTete(&tete,'c') ;
  // listeAffiche(tete) ;
  // insertionQueue(&tete,'t') ;
  // listeAffiche(tete) ;
  // insertionQueue(&tete,'s') ;
  // listeAffiche(tete) ;
  // suppressionTete(&tete) ;
  // listeAffiche(tete) ;
  // suppressionTete(&tete) ;
  // listeAffiche(tete) ;
  // suppressionQueue(&tete) ;
  // listeAffiche(tete) ;
  // suppressionTete(&tete) ;
  // listeAffiche(tete) ;

  return 0;
}
