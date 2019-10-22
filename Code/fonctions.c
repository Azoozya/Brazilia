#include "header.h"

int test_succes(void* name)
{
  if(name == NULL)
    return NO;
  else
    return YES;
}

//Nom de la fonction suffisament explicite
void my_strncpy(char* src,char* dst,int size)
{
  for(int rank = 0 ; rank < size ; rank++ )
    {
      dst[rank] = src[rank];
    }
}

// Initialisation de la table FAT et mise à jour du master pointer
void initialise_fat(void)
{
  freeblocks = 0;
}

//Création d'une entité objet et mise à jour du FAT et du master pointer
void creer_objet(char* nom, unsigned short auteur,unsigned int taille, short *data, mp* master)
{
  objet* previous = NULL;
  int success = 0;
  objet* cell;
  do {
  	cell = malloc(sizeof(objet));
  	if (test_succes(cell) == YES)
  		success = add_pointer_master((void*)cell ,master);
  } while(test_succes(cell) != YES);



  // cell->nom = nom;
  cell->taille = taille;
  cell->auteur = auteur;
  cell->next = NULL;
  // MET A JOUR FREEBLOCKS (sinon la fonction de test ne servira a pas grand chose)

  previous = reach_last_cell_obj(obj);
  cell->previous = previous;
  //Si il n'ya pas de previous , quand c'est le 1er objet que l'on crée.
  // previous->next = cell;

  if (success != YES)
    printf("Création d'objet impossible\n");

  if (success == YES)
  {
    int nbr_blocs = (taille/BLOCSIZE) + 1;
    int fat_index = 0;
    while ((fat[fat_index] != EMPTY) && (fat_index < BLOCNUM))
      fat_index++;

    if (fat_index < BLOCNUM)
      {
      // C GRAVE CHIANT BOUDEL DE MIERDA !!!
        cell->index = fat_index;
      }
   }
}

// Permet de trouver un objet qui porte tel nom
objet* find_object_by_name(char* name)
{
  objet* to_return = obj;

  while (to_return->nom != name && to_return != NULL)
    {
      to_return = to_return->next;
    }
  return to_return;
}

// Suppression d'un objet et mise à jour de la table FAT
int supprimer_objet(char* nom)
{
  objet* buffer = find_object_by_name(nom);
  // MET A JOUR FREEBLOCKS (sinon la fonction de test ne servira a pas grand chose)
  if(test_succes(buffer) != YES)
    return -1;
  else
    return 0;
}

void supprimer_tout(void)
{
  // Supprime les éléments de la liste chainée d'objets (mise à jour du master pointer)
  for(int depth = 0 ; depth < BLOCNUM ; depth++)
    {
      freeblocks++;
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
  mp* master = create_master_pointer();

  //Test si il y'a eu variation de freeblocks
  creer_objet(name,10,10,data,master);
  printf("[Créer objet] Avant : %d , Après : %d\n",tmp,freeblocks);

  //Test si les valeurs qu'on lui a donné ont été enregistré
  buffer = find_object_by_name(name);
  if (buffer == obj && buffer->nom != name)
    printf("[Créer objet] L'objet n'a pas été crée.\n");
  else
    printf("[Créer objet] name = %s : Chameau , auteur = %d : 10 , taille = %d : 10\n",buffer->nom,buffer->taille,buffer->index);

  delete_down(master);
}

void test_supprimer_objet(void)
{
  char name[] = "Chameau";
  short data[] = {5,7,8,9,10};

  mp* master = create_master_pointer();
  creer_objet(name,10,10,data,master);

  unsigned short tmp = freeblocks;
  supprimer_objet(name);

  printf("[Supprimer objet] Avant : %d , Après : %d\n",tmp,freeblocks);
  delete_down(master);
}

void test_supprimer_tout(void)
{
  char name1[] = "Chameau";
  char name2[] = "Dromadaire";

  mp* master = create_master_pointer();
  initialise_fat();

  unsigned short tmp = freeblocks;
  creer_objet(name1,10,10,NULL,master);
  creer_objet(name2,20,20,NULL,master);

  unsigned short tmp2 = freeblocks;

  supprimer_tout();
  //On vérifie qu'il y'a une variation de freeblocks.
  printf("[Supprimer tout] Avant : %d , Pendant : %d , Après : %d\n",tmp,tmp2,freeblocks);
}
