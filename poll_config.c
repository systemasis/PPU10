#include "polling.h"

#define NB_STATIONS 5
#define SECONDAIRE_N 0
#define SECONDAIRE_PID_PRIMAIRE 1
#define SECONDAIRE_PROGRAMME 2
#define TRAFIC_I 0
#define TRAFIC_PID_STI 1
#define TRAFIC_DELAI_MIN_REQUETE 2
#define TRAFIC_DELAI_MAX_REQUETE 3
#define TRAFIC_PROGRAMME 4

typedef struct secondaireArgs {
	int n;
	int pid_primaire;
	char *programme;
} SECONDAIREARGS;

typedef struct traficArgs {
	int i;
	int pid_Sti;
	int delai_min_requete;
	int delai_max_requete;
	char *programme;
} TRAFICARGS;

int main (int argc,char *argv[]){
	if (argc < 9) {
		perror("8 à 9 paramètres attendus");
		exit(1);
	}
	if(argc > 10){
		perror("8 à 9 paramètres attendus");
		exit(1);
	}

	char *primaire = argv[1], *secondaire = argv[2], *trafic = argv[3], *string_state = string_idle,
	*prefixe_fichier = NULL; // Retirer cette ligne cause la levée d'une erreur lors de la compilation

	int i, state = IDLE, numero_station = 1, pid, ppid = getpid(), pid_St[NB_STATIONS];
	// On ne convertit pas en int car il faudrait les cast à nouveau en char pour les remettre en argument
	// des exec
	char *n = argv[4], //nombre de station
	*nb_polling = argv[5], *delai_polling = argv[6], *delai_min_requete = argv[7],
	*delai_max_requete = argv[8];

	//TODO DÉGAGE
	// printf("coucou3\n");fflush(stdout);
	//
	// // Initialisation des arguments généraux aux stations secondaires
	// char **sargs;
	// // sargs = malloc(sizeof(SECONDAIREARGS));
	// sargs[SECONDAIRE_PID_PRIMAIRE] = (char *)&pid;
	// sargs[SECONDAIRE_PROGRAMME] = secondaire;
	//
	// //TODO DÉGAGE
	// printf("coucou4\n");fflush(stdout);
	//
	// // Initialisation des arguments généraux aux générateurs de requête
	// char **targs;
	// // targs = malloc(sizeof(TRAFICARGS));
	// targs[TRAFIC_DELAI_MIN_REQUETE] = delai_min_requete;
	// targs[TRAFIC_DELAI_MAX_REQUETE] = delai_max_requete;
	// targs[TRAFIC_PROGRAMME]= trafic;

	//TODO DÉGAGE
	// printf("%s, %s\n", sargs->programme, targs->programme);fflush(stdout);

	if(argc == 10){
		prefixe_fichier = argv[9];
	}

	if(atoi(delai_min_requete) > atoi(delai_max_requete)){
		perror("Le délai minimum ne peut être plus grand que le délai maximum");
		exit(1);
	}
	if(atoi(delai_min_requete) < 0){
		perror("Le délai minimum ne peut être négatif ou nul");
		exit(1);
	}

	for(i= NB_STATIONS - atoi(n); i<NB_STATIONS; i++){
		// Création d'une station secondaire
		if((pid=fork()) == 0){
			execl(secondaire, secondaire, (char*) &i, (char *) &ppid, (char *) NULL);
			perror("Erreur d'execl pour le secondaire");
			exit(1);
		}else{
			pid_St[i] = pid;

			// Création d'un générateur de requête
			if((pid = fork()) == 0){
				// targs[TRAFIC_I]= (char *)&i;
				// targs[TRAFIC_PID_STI] = (char *)&pid_St[i];
				//
				// execv(targs[TRAFIC_PROGRAMME], targs);

				execl(trafic, trafic, (char *) &i, (char *) &pid_St[i], delai_min_requete, delai_max_requete, (char *) NULL);
				perror("Erreur d'execl pour le trafic");
				exit(1);
			}
		}
	}

	printf("Je suis poll_config, mes paramètres sont: primaire=%s, secondaire=%s, trafic=%s, n=%s, nb_polling=%s, delai_polling=%s, delai_min_requete=%s, delai_max_requete=%s", primaire, secondaire, trafic, n, nb_polling, delai_polling, delai_min_requete, delai_max_requete);
	if(argc == 10){
		printf(", prefixe_fichier=%s", prefixe_fichier);
	}
	printf(".\n");

	// Création de la station primaire
	// execl(*primaire, *primaire, nb_polling, delai_polling, n, pid_St[0], pid_St[1], pid_St[2], pid_St[3], pid_St[4], NULL);

	return(EXIT_SUCCESS);
}
