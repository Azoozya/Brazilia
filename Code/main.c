#include "header.h"

int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	//             EXEMPLE
	// char* CHANGE_ME;
	// do {
	// 	CHANGE_ME = malloc(sizeof(char));
	// 	if (test_succes(CHANGE_ME) == YES)
	// 		add_pointer_master((void*)CHANGE_ME ,master);
	// } while(test_succes(CHANGE_ME) != YES);

	initialise_fat(master);
	// objet* bwaa = creer_objet("dromadaire",50,2050,"lama",master);



	delete_down(master);
	return 0;
}
