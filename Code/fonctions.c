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

// Initialisation de la liste chainée FAT et mise à jour du master pointer
unsigned short* initialise_fat(mp* master)
{
  freeblocks = 0;
  unsigned short* fat = NULL;
  do{
      fat = malloc(BLOCNUM*sizeof(unsigned short));
      if (test_succes(fat) == YES)
        add_pointer_master((void*)fat ,master);
    }while(test_succes(fat) != YES);
}

//Création d'une entité objet et mise à jour du FAT et du master pointer
void creer_objet(char* nom, unsigned short auteur,unsigned int taille, short *data, mp* master)
{
  int lama = 0;
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

  if(test_succes(buffer) != YES)
    return -1;
  else
    return 0;
}

void supprimer_tout(mp* master)
{
  // Supprime les éléments de la liste chainée d'objets (mise à jour du master pointer)
  delete_down(master);
  for(int depth = 0 ; depth < BLOCNUM ; depth++)
    {
      freeblocks++;
    }
}
