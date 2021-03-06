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
	int delai = 0;

	if(delai_min_requete > delai_max_requete){
		perror("Le délai minimum ne doit pas dépasser le délai maximum");
		exit(1);
	}
	srand(i);
	for EVER{
		delai = rand()%(delai_max_requete - delai_min_requete)+delai_min_requete;
		sleep(delai);
		kill(pid_Sti, DATA_REQ_TX);
	}

	return(EXIT_SUCCESS);
}
