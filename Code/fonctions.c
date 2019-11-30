#include "header.h"

int test_success(void* name)
{
  if(name == NULL)
    return NO;
  else
    return YES;
}

void* smalloc(int size)
{
    int try = 0;
    void* to_return = NULL;
      do {
        to_return = malloc(size);
        try++;
        if (try > 100)
          exit(2);
      } while(to_return == NULL);
    return to_return;
  }

//Nom de la fonction suffisament explicite
void my_strncpy(char* src,char* dst,int size)
{
  for(int rank = 0 ; rank < size ; rank++ )
    {
      dst[rank] = src[rank];
    }
}

// Initialisation de la table FAT et de obj (obj sera la tête de la liste et agira en tant que telle et rien d'autre (absence de données))
void initialise_fat(void)
{
  if (fat == NULL)
  {
    fat = (unsigned short*)smalloc(sizeof(short) * BLOCNUM);
    for (short index = 0; index < BLOCNUM; index++)
    {
      fat[index] = EMPTY;
      freeblocks++;
    }
  }

  if (obj == NULL)
  {
    obj = (objet*)smalloc(sizeof(objet));
    my_strncpy("\0",obj->nom,1);
    obj->taille = 0;
    obj->auteur = 0;
    obj->index = 0;
    obj->next = NULL;
  }
}

// Permet de trouver un objet qui porte tel nom
objet* find_object_by_name(char* name)
{
  objet* to_return = obj;
  int verif = 1;

  while (to_return != NULL && verif != 0)
  {
    verif = strncmp(name,to_return->nom,NAMELEN);
    if (verif != 0) to_return = to_return->next;
  }

  if (verif != 0) to_return = NULL;
  return to_return;
}

/*
 int success = 0;
 int index = 0;
 int verif = 0;

 do
   {
 verif = 0;
 index = 0;

 while (verif == 0 && index < NAMELEN)
 {
   if(to_return->nom[index] != name[index]) verif = 1;
   index++;
 }

 if (verif == 1) to_return = to_return->next;
 else success = 1;

   } while (success == 0 && to_return != NULL);

 return to_return;
} */


//Création d'une entité objet et mise à jour du FAT
void creer_objet(char* nom, unsigned short auteur,unsigned int taille, short* data)
{
  int nbr_blocs;
  if ((taille/BLOCSIZE)%BLOCSIZE == 0) nbr_blocs = taille/BLOCSIZE;
  else nbr_blocs = (taille/BLOCSIZE) + 1;
  //Si taille n'est pas un multiple de BLOCSIZE, alors un bloc en plus est nécessaire pour stocké l'excedent de données
  objet* name_test = find_object_by_name(nom);

  if (name_test != NULL) printf("Création d'objet impossible : nom déjà donné à un objet\n");
  else if (fat == NULL) printf("Création d'objet impossible : FAT non initialisée\n");
  else if (nbr_blocs > freeblocks) printf("Création d'objet impossible : Pas suffisament d'espace libre dans FAT\n");
  else
  {
    objet* previous = obj;

    //création de l'objet
    objet* cell = NULL;
    //C'est une procédure y'a rien a return !
    char name_of_cell[NAMELEN] = "\0";
    cell = smalloc(sizeof(objet));

    for (int name_index = 0; name_index < NAMELEN; name_index++) name_of_cell[name_index] = *(nom + name_index);

    //Tu ajoutes le fichier dans la liste chaînée avant ton test de possibilité
    my_strncpy(name_of_cell, cell->nom, NAMELEN);
    cell->taille = taille;
    cell->auteur = auteur;
    cell->next = NULL;
    while (previous->next != NULL) previous = previous->next;
    previous->next = cell;

    //Mise à jour de FAT
    int bloc_counter = nbr_blocs;
    int fat_index = 0;
    //Donne lui une valeur par défaut !
    int save_FI = 0;  //save_FI pour save_fat_index

    //Segfault en cas de FAT vierge
    while (fat[fat_index] != EMPTY) fat_index++;

    cell->index = fat_index;
    save_FI = fat_index;

    do {
      fat[save_FI] = fat_index;
      save_FI = fat_index;
      freeblocks--;
      bloc_counter--;
      while (fat[fat_index] != EMPTY && bloc_counter > 0) fat_index++;

    } while (bloc_counter > 0);

    fat[save_FI] = LAST;

    // for (int indexA = 0; indexA < BLOCNUM; indexA++) printf("%x ",fat[indexA]);
    // printf("\n\n\n");

  }
}


// Suppression d'un objet et mise à jour de la table FAT
int supprimer_objet(char* nom)
{
  objet *previous = obj;
  // objet *buffer = NULL;
  objet* object_to_delete = find_object_by_name(nom);

  // MET A JOUR FREEBLOCKS (sinon la fonction de test ne servira a pas grand chose)
  if(test_success(object_to_delete) != YES)
  {
    printf("Suppression impossible : Objet non existant\n");
    return -1;
  }
  else
  {
    unsigned short fat_index = object_to_delete->index;
    unsigned short fat_buffer = 0;

    while (strcmp(previous->next->nom,nom) != 0 && previous != object_to_delete) previous = previous->next;

    if (previous == object_to_delete)
    {
      printf("Suppression impossible : Erreur recherche précédent\n");
      return -1;
    }
    else
    {
      previous->next = object_to_delete->next;
      free(object_to_delete);
    }

    //MAJ de FAT
    do
    {
      fat_buffer = fat[fat_index];
      fat[fat_index] = EMPTY;
      fat_index = fat_buffer;
      freeblocks++;
    } while (fat_index != LAST);

    return 0;
  }
}

// Supprime tous les éléments de la liste chainée d'objets et vide la table FAT
void supprimer_tout(void)
{
  // Supprime les éléments de la liste chainée d'objets
  objet* to_delete = obj->next;
  objet* buffer = NULL;

  while(to_delete != NULL)
  {
    buffer = to_delete->next;
    free(to_delete);
    to_delete = buffer;
  }

  // Vide la liste FAT
  for(int depth = 0 ; depth < BLOCNUM ; depth++)
    {
      if (fat[depth] != EMPTY)
      {
        fat[depth] = EMPTY;
        freeblocks++;
      }
    }
}

/* ------------------------------------------------------------- */

void test_initialiser_fat(void)
{
	unsigned short* buffer = fat;
	initialise_fat();
	int error = BLOCNUM;
	if(buffer != fat)
		{
			error = 0;
			for (size_t depth = 0; depth < BLOCNUM; depth++)
				{
					if (fat[depth] != EMPTY)
						{
							error += 1;
						}
				}
		}
	if (error == 0)
		printf("[Initialise_Fat] : IsOk\n");
	else
		printf("[Initialise_Fat] : %d erreurs\n",error);
}

void test_creer_objet(void)
{
  unsigned short tmp = freeblocks;
  objet* buffer = obj;
  char name[] = "Chameau";
  short data[] = {5,7,8,9,10};

  //Test si il y'a eu variation de freeblocks
  creer_objet(name,10,10,data);
  printf("[Créer objet] Avant : %d , Après : %d\n",tmp,freeblocks);

  //Test si les valeurs qu'on lui a donné ont été enregistré
  buffer = find_object_by_name(name);
  if (buffer == NULL)
    printf("[Créer objet] L'objet n'a pas été crée.\n");
  else if (strcmp(buffer->nom,name) || buffer->taille != 10 || buffer->auteur != 10)
    printf("[Créer objet] L'objet a été mal crée %s:%s %u:%u %u:%u \n",buffer->nom,name,buffer->taille,10,buffer->auteur,10);
  else
    printf("[Créer objet] L'objet a bien été crée\n");

}

void test_supprimer_objet(void)
{
  char name[] = "Chameau";
  short data[] = {5,7,8,9,10};

  creer_objet(name,10,10,data);

  unsigned short tmp = freeblocks;
  supprimer_objet(name);
  if (tmp >= freeblocks)
    printf("[Supprimer objet] Ne marche pas %d:%d\n",tmp,freeblocks);
  else
    printf("[Supprimer objet]Avant : %d , Après : %d\n",tmp,freeblocks);
}

void test_supprimer_tout(void)
{
  char name1[] = "Chameau";
  char name2[] = "Dromadaire";

  initialise_fat();

  unsigned short tmp = freeblocks;
  creer_objet(name1,10,10,NULL);
  creer_objet(name2,20,20,NULL);

  unsigned short tmp2 = freeblocks;

  supprimer_tout();
  //On vérifie qu'il y'a une variation de freeblocks.
  if (tmp > freeblocks  && tmp2 < freeblocks)     // On ne devrait pas plutôt vérifié pour tmp SUPERIEUR ou égal à freeblocks, voire même seulement égal ?
    printf("[Supprimer tout] Avant : %d , Pendant : %d , Après : %d\n",tmp,tmp2,freeblocks);
  else if (tmp < freeblocks && tmp2 < freeblocks)
    printf("[Supprimer tout] creer_objet ne change pas freeblocks\n");
  else if (tmp2 > freeblocks && tmp > freeblocks)
    printf("[Supprimer tout] supprimer tout ne change pas freeblocks\n");
  else
    printf("[Supprimer tout] creer_objet ET suprimmer_tout ne changes pas freeblocks\n");

}
