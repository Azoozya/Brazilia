#include "header.h"

int main(int argc,char* argv[])
{




	return 0;
}

void momo(void)
{
		mp* master = create_master_pointer();
		// initialise_fat(master);
		obj = NULL;

		char* name_Lamantin = "Lamantin";
		unsigned short auteur_Lamantin = 10;
		unsigned int taille_Lamantin = 255;
		short data_Lamantin = 25;


		creer_objet(name_Lamantin, auteur_Lamantin, taille_Lamantin, &data_Lamantin, master);
		creer_objet(name_Lamantin, auteur_Lamantin, taille_Lamantin, &data_Lamantin, master);

		delete_down(master);
}
