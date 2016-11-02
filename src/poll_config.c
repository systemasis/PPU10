#include "polling.h"
#include "header.h"

int main (int argc,char *argv[]){
	if (argc < 9) {
		error("8 à 9 paramètres attendus");
	}
	if(argc > 10){
		error("8 à 9 paramètres attendus");
	}

	char *primaire = argv[1], *secondaire = argv[2], *trafic = argv[3], *string_state = string_idle;

	int i, state = IDLE, numero_station = 1, pid;
	// On ne convertit pas en int car il faudrait les cast à nouveau en char pour les remettre en argument
	// des exec
	char *n = argv[4], //nombre de station
		*nb_polling = argv[5], *delai_polling = argv[6], *delai_min_requete = argv[7],
		*delai_max_requete = argv[8], iStr[10], ppid[10], pid_St[MAX_ST+1][10];
	char *my_env[2] = {NULL, NULL}; // Retirer cette ligne cause la levée d'une erreur lors de la compilation

	// Injecte le pid dans une chaîne de caractères pour l'utiliser avec l'exec
	snprintf(ppid, sizeof(ppid), "%d", getpid());

	if(argc == 10){
		i=0;

		while(argv[9][i] != 0){
			i++;
		}// S'assure de la taille du prefixe à donner au nom du fichier
		i++;

		my_env[0] = malloc(8+i);
		my_env[1] = malloc(8+sizeof(i));
		my_env[2] = NULL;
		snprintf(my_env[0], 8+i, "PREFIXE=%s", argv[9]);
		snprintf(my_env[1], 7+sizeof(i), "LENGTH=%d", i);
	}else{
		my_env[0] = NULL; // Écrire my_env = NULL lance un SEG_FAULT même si le programme ne passe pas par le else. J'aime le C.
	}

	if(atoi(delai_min_requete) > atoi(delai_max_requete)){
		error("Le délai minimum ne peut être plus grand que le délai maximum");
	}
	if(atoi(delai_min_requete) < 0){
		error("Le délai minimum ne peut être négatif ou nul");
	}

	for(i=1; i <= min(atoi(n), MAX_ST+1); i++){
		sprintf(iStr+0, "%d", i);

		// Création d'une station secondaire
		if((pid=fork()) == 0){
			execle(secondaire, secondaire, iStr, ppid, (char *) 0, my_env);
			error("Erreur d'execle pour le secondaire");
			exit(1);
		}else{
			sprintf(pid_St[i], "%d", pid);

			// Création d'un générateur de requête
			if((pid = fork()) == 0){
				execle(trafic, trafic, iStr, pid_St[i], delai_min_requete, delai_max_requete, (char *) NULL, my_env);
				error("Erreur d'execle pour le trafic");
			}
		}
	}

	for(;i <= MAX_ST+1; i++){
		pid_St[i][0] = 0;
	}

	// Création de la station primaire
	execle(primaire, primaire, nb_polling, delai_polling, n, pid_St[1], pid_St[2], pid_St[3], pid_St[4], pid_St[5], (char *) NULL, my_env);
	error("Erreur d'execle pour le primaire");
}
