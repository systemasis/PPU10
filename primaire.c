#include "polling.h"

int main (int argc,char **argv){
	if(argc < 4){
		perror("Au moins 3 paramètres attendus");
		exit(1);
	}

	int nb_polling = atoi(argv[1]), delai_poll = atoi(argv[2]),
	n = atoi(argv[3]), nb_req_rx = 0, i;

	printf("Je suis primaire, mes paramètres sont : nb_polling=%d, delai_poll=%d, n=%d", nb_polling, delai_poll, n);

	for(i=4; i<argc;i++){
		printf(", pid_St%d=%d", i, atoi(argv[i]));
	}

	printf(".\n");

	sleep(60);

	// for(i=0;i<=n;i++){
	// 	switch(state){
	// 		case 2: //w__req
	// 			printf("Prim %s st%d %ds \n",string_state,i,delai_poll);
	//
	//
	// 		break;
	// 		case 5: // bc_data
	// 			printf("Prim %s st%d \n",string_state,i);
	//
	// 		break;
	// 	}
	// }

	return(EXIT_SUCCESS);
}
