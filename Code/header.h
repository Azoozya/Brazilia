#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define BLOCSIZE 512
#define BLOCNUM 1024
#define NAMELEN 256
#define ERROR 63336
#define NONE 36663
#define YES 333
#define NO 4444
#define MAX_TRY 100
#define EMPTY 0xFFFF
#define LAST 0xFFFE

/* master_pointer */
typedef struct mp mp;
struct mp
{
  void* pointer;
  mp* previous;
  mp* next;
};


typedef struct objet objet;
struct objet
{
char nom[NAMELEN];
unsigned int taille;
unsigned short auteur;
unsigned short index;
objet* next;
objet* previous;
};

objet* obj;  // Pointe vers la 1ère valeur de la liste chainée d'objet
char volume[BLOCSIZE * BLOCNUM];
unsigned short* fat;
unsigned short freeblocks;

/* fonctions */
typedef struct REPLACE_ME REPLACE_ME;
struct REPLACE_ME
{
    REPLACE_ME* previous;
    REPLACE_ME* next;
};

/* master_pointer */
mp* create_master_pointer(void);
int add_pointer_master(void* pointer,mp* master);
objet* reach_last_cell_obj(objet* head);
mp* reach_last_cell_mp(mp* head);
void delete_down(mp* head);

/* fonctions */
int test_success(void* name);
void my_strncpy(char* src,char* dst,int size);

void initialise_fat(void);
void creer_objet(char* nom, unsigned short auteur,unsigned int taille, short *data, mp* master);
objet* find_object_by_name(char* name);
int lire_objet(objet* o,char **data);
int supprimer_objet(char* nom);
void supprimer_tout(void);

/** POUR LES PLUS RAPIDES ..................** BONUS ** BONUS ** BONUS **
\brief Cette fonction permet :
De lire le contenu d'un objet et de le copier dans une structure de données allouée dynamiquement
Attention à la taille !!!!!!!!!!!!!!
\param nom nom de l'objet
\return -1 si erreur, 0 sinon.
*/


/* main (devrait être vide) */

/* test */
void momo(void);
void test_initialiser_fat(void);
void test_creer_objet(void);
void test_supprimer_objet(void);
void test_supprimer_tout(void);
