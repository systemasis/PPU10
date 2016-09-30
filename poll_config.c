#include "polling.h"

int main (int argc,char *argv[]){
	if (argc < 9) {
		perror("8 à 9 paramètres attendus");
		exit(1);
	}
	if(argc > 10){
		perror("8 à 9 paramètres attendus");
		exit(1);
	}

	char *primaire = argv[1], *secondaire = argv[2], *trafic = argv[3], *string_state = string_idle;
	char *prefixe_fichier = NULL; // Retirer cette ligne cause la levée d'une erreur lors de la compilation

	int n = atoi(argv[4]), //nombre de station
	nb_polling = atoi(argv[5]), delai_polling = atoi(argv[6]),
	delai_min_requete = atoi(argv[7]), delai_max_requete = atoi(argv[8]),
	state = IDLE, numero_station = 1, pid;
	if(argc == 10){
		prefixe_fichier = argv[9];
	}

	if(delai_min_requete > delai_max_requete){
		perror("Le délai minimum ne peut être plus grand que le délai maximum");
		exit(1);
	}
	if(delai_min_requete < 0){
		perror("Le délai minimum ne peut être négatif ou nul");
		exit(1);
	}

	if((pid=fork()) == 0){
		//printf("%s\n",secondaire);
		// execl(secondaire,numero_station,pid,NULL);
		// perror(secondaire);
		exit(1);
	}
	else{
		for(numero_station = numero_station + 1; numero_station <= n; numero_station++){
			if((pid=fork()) == 0){
				//execl(secondaire,numero_station,pid,NULL);
				//perror(secondaire);
				exit(1);
			}
			//execl(primaire,nb_polling,delai_polling,n,);
		}
	}

	printf("Je suis poll_config, mes paramètres sont: primaire=%s, secondaire=%s, trafic=%s, n=%d, nb_polling=%d, delai_polling=%d, delai_min_requete=%d, delai_max_requete=%d", primaire, secondaire, trafic, n, nb_polling, delai_polling, delai_min_requete, delai_max_requete);
	if(argc == 10){
		printf(", prefixe_fichier=%s", prefixe_fichier);
	}
	printf(".\n");

	return(EXIT_SUCCESS);
}
