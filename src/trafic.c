#include "polling.h"
#include "header.h"

//traffic
int main (int argc, char **argv){
	if(argc != 5){
		perror("4 paramètres attendus");
		exit(1);
	}

	int i = atoi(argv[1]); //numero de la station secondaire
	int pid_Sti = atoi(argv[2]); // pid de la station secondaire

	// delai minimun et max entre deux requete pour une meme station
	int delai_min_requete = atoi(argv[3]); 	//>0
	int delai_max_requete = atoi(argv[4]);	//>=delai_min_requete

	if(delai_min_requete > delai_max_requete){
		perror("Le délai minimum ne doit pas dépasser le délai maximum");
		exit(1);
	}

	printf("Je suis trafic, mes paramètres sont : i=%i, pid_St%d=%d, delai_min_requete=%d, delai_max_requete=%d.\n", i, i, pid_Sti, delai_min_requete, delai_max_requete);

	sleep(60);

	// switch(state){
	// 	case(7):
	//
	// 	break;
	// }

	return(EXIT_SUCCESS);
}
