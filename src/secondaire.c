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

	printf("Je suis secondaire%d, mes paramètres sont : n=%d, pid_primaire=%d.\n", n, n, pid_primaire);

	sleep(60);

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
