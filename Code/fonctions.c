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

// Initialisation de la table FAT et de obj (obj sera la t�te de la liste et agira en tant que telle et rien d'autre (absence de donn�es))
void initialise_fat(void)
{
  if (fat == NULL)
  {
    fat = (unsigned short*)smalloc(sizeof(short) * BLOCNUM);
    freeblocks = 0;
    for (short index = 0; index < BLOCNUM; index++)
    {
      fat[index] = EMPTY;
      freeblocks++;
    }
  }
  if (volume == NULL)
  {
	volume = (char**)smalloc(sizeof(char*) * BLOCNUM);
	/*for(int index = 0; index < BLOCNUM; index++)
	   *(volume+index) = (char*)smalloc(sizeof(char) * BLOCSIZE);*/
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


//Cr�ation d'une entit� objet et mise � jour de la table FAT
void creer_objet(char* nom, unsigned short auteur,unsigned int taille, char* data)
{
  int nbr_blocs = 0;
  if ((taille/BLOCSIZE)%BLOCSIZE == 0) nbr_blocs = taille/BLOCSIZE;
  else nbr_blocs = (taille/BLOCSIZE) + 1;
  //Si taille n'est pas un multiple de BLOCSIZE, alors un bloc en plus est n�cessaire pour stocker l'excedent de donn�es
	
  objet* name_test = find_object_by_name(nom);

  if (name_test != NULL) printf("Cr�ation d'objet impossible : nom d�j� donn� � un objet\n");
  else if (fat == NULL) printf("Cr�ation d'objet impossible : FAT non initialis�e\n"); //Pour v�rifier que FAT a bien �t� initialis�e
  else if (nbr_blocs > freeblocks) printf("Cr�ation d'objet impossible : Pas suffisament d'espace libre dans FAT\n");
  else
  {
    objet* previous = NULL;
    if (obj != NULL) previous = obj;

    //cr�ation de l'objet
    objet* cell = NULL;
    char name_of_cell[NAMELEN] = "\0";
    cell = smalloc(sizeof(objet));

    for (int name_index = 0; name_index < NAMELEN; name_index++) name_of_cell[name_index] = *(nom + name_index);

    my_strncpy(name_of_cell, cell->nom, NAMELEN);
    cell->taille = taille;
    cell->auteur = auteur;
    cell->next = NULL;
    if (obj == NULL) obj = cell;
    else 
    {
	while (previous->next != NULL) previous = previous->next;
	previous->next = cell;
    }
    
    //Mise � jour de FAT et VOLUME
    int bloc_counter = nbr_blocs;
    int fat_index = 0;
    int vol = 0;
    int vol_index = 0;
    int save_FI = 0;  //save_FI pour save_fat_index

    while (fat[fat_index] != EMPTY) fat_index++;

    cell->index = fat_index;
    save_FI = fat_index;

    do {
      fat[save_FI] = fat_index;
	    
      vol = vol_index*BLOCSIZE;
      *(volume+save_FI) = (char*)smalloc(sizeof(char) * BLOCSIZE);
      my_strncpy((data+vol), *(volume+save_FI), BLOCSIZE);
      vol_index++;
	    
      save_FI = fat_index;
      freeblocks--;
      bloc_counter--;
      while (fat[fat_index] != EMPTY && bloc_counter > 0) fat_index++;

    } while (bloc_counter > 0);

    fat[save_FI] = LAST;
       vol = vol_index*BLOCSIZE;
      *(volume+save_FI) = (char*)smalloc(sizeof(char) * BLOCSIZE);
      my_strncpy((data+vol), *(volume+save_FI), BLOCSIZE);
        
  }
}


// Suppression d'un objet et mise � jour de la table FAT et de VOLUME
int supprimer_objet(char* nom)
{
  objet *previous = obj;
  objet* object_to_delete = find_object_by_name(nom);

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
      printf("Suppression impossible : Erreur recherche pr�c�dent\n");
      return -1;
    }
    else
    {
      previous->next = object_to_delete->next;
      free(object_to_delete);
    }

    //MAJ de FAT et VOLUME
    do
    {
      fat_buffer = fat[fat_index];
      fat[fat_index] = EMPTY;
      free(*(volume+fat_index));
      fat_index = fat_buffer;
      freeblocks++;
    } while (fat_index != LAST);

    return 0;
  }
}

// Supprime tous les �l�ments de la liste chain�e d'objets et vide la table FAT
void supprimer_tout(void)
{
  // Suppression des �l�ments de la liste chain�e d'objets
  objet* to_delete = obj->next;
  objet* buffer = NULL;

  while(to_delete != NULL)
  {
    buffer = to_delete->next;
    free(to_delete);
    to_delete = buffer;
  }

  // Vidange de la liste FAT
  for(int depth = 0 ; depth < BLOCNUM ; depth++)
    {
      if (fat[depth] != EMPTY)
      {
        fat[depth] = EMPTY;
	free(*(volume + depth));
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
  char *data = malloc(sizeof(char) * 300);
	for (int data_index = 0; data_index < 300; data_index++) data[data_index] = 'A';

  //Test si il y'a eu variation de freeblocks
  creer_objet(name,10,10,data);
  printf("[Cr�er objet] Avant : %d , Apr�s : %d\n",tmp,freeblocks);

  //Test si les valeurs qu'on lui a donn� ont �t� enregistr�es
  buffer = find_object_by_name(name);
  if (buffer == NULL)
    printf("[Cr�er objet] L'objet n'a pas �t� cr�e.\n");
  else if (strcmp(buffer->nom,name) || buffer->taille != 10 || buffer->auteur != 10)
    printf("[Cr�er objet] L'objet a �t� mal cr�e %s:%s %u:%u %u:%u \n",buffer->nom,name,buffer->taille,10,buffer->auteur,10);
  else
    printf("[Cr�er objet] L'objet a bien �t� cr�e\n");
  supprimer_tout();
}

void test_supprimer_objet(void)
{
  char name[] = "Bonjout";
  char data[] = {5,7,8,9,10};

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
  char name1[] = "Lama";
  char name2[] = "Dromadaire";
  char data1[] = {1,2,3,4,6};
  char data2[] = {5,7,8,9,10};


  initialise_fat();

  unsigned short tmp = freeblocks;
  creer_objet(name1,10,10,data1);
  creer_objet(name2,20,20,data2);


  unsigned short tmp2 = freeblocks;

  supprimer_tout();
  
  //On v�rifie qu'il y'a une variation de freeblocks.
  if (tmp == freeblocks  && tmp2 < freeblocks)
    printf("[Supprimer tout] Avant : %d , Pendant : %d , Après : %d\n",tmp,tmp2,freeblocks);
  else if (tmp < tmp2 && tmp2 < freeblocks)
    printf("[Supprimer tout] creer_objet ne change pas freeblocks\n");
  else if (tmp2 >= freeblocks && tmp > freeblocks)
    printf("[Supprimer tout] supprimer_tout ne change pas freeblocks\n");
  else
    printf("[Supprimer tout] creer_objet ET suprimmer_tout ne changes pas freeblocks\n");

}
