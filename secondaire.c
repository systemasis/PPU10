#include "polling.h"
//station secondaire
int main (int argc,char *argv[]){
	if (argc != 3) {
		fprintf(stderr, "erreur: pas le bo nombre de parametre\n");
		return 1;
    	}
	
	int n =atoi(argv[1]);
	int pid_primaire= atoi(argv[2]);	
	int nb_data_req_rx =0;

	//tabulation
	int tab=((3*n)+1);
	int i=1;	
	for(;i<=tab;i++)printf("\t");
	printf("%d",n);

	switch(state){
		case 1: //idle
			printf(" %s \n",string_state);
			
		break;
		case 3: //w_poll
			printf(" %s Attente\n",string_state);
			
		break;
		case 6: //sd_data
			printf(" %s \n",string_state);
			
		break;
		case 4: //w_ack
			printf(" %s \n",string_state);
			
		break;
	}
	exit(EXIT_SUCCESS);
}
