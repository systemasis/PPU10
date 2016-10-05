#include "polling.h"
#include "header.h"

//station secondaire
int main (int argc,char *argv[]){
	if (argc != 3) {
		perror("2 paramètres nécessaires");
		exit(1);
	}

	int n = atoi(argv[1]), pid_primaire = atoi(argv[2]),
	nb_data_req_rx =0, tab=((3*n)), i;
	char *prefixe_fichier;

	if(getenv("PREFIXE") != NULL){
		prefixe_fichier = malloc(4+sizeof(getenv("PREFIXE")));
		snprintf(prefixe_fichier, sizeof(prefixe_fichier), "%s", getenv("PREFIXE"));
		sprintf(prefixe_fichier + strlen(prefixe_fichier), "_St");
		sprintf(prefixe_fichier + strlen(prefixe_fichier), "%s", argv[1]);
		stdout = fopen(prefixe_fichier, "w+");
	}

	printf("Je suis secondaire%d, mes paramètres sont : n=%d, pid_primaire=%d.\n", n, n, pid_primaire);

	// for(i=0;i<=tab;i++)
	// 	printf("\t");
	//
	// printf("%d",n);


	// switch(state){
	// 	case 1: //idle
	// 		printf(" %s \n",string_state);
	//
	// 	break;
	// 	case 3: //w_poll
	// 		printf(" %s Attente\n",string_state);
	//
	// 	break;
	// 	case 6: //sd_data
	// 		printf(" %s \n",string_state);
	//
	// 	break;
	// 	case 4: //w_ack
	// 		printf(" %s \n",string_state);
	//
	// 	break;
	// }
	return(EXIT_SUCCESS);
}
