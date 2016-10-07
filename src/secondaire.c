#include "polling.h"
#include "header.h"

void invitationEmission();
void printState();
void receptionDonnee();
void requeteEmission();
void receptionAcquittement();

int n = 0, pid_primaire = 0, tab=0, nb_data_req_rx = 0;

//station secondaire
int main (int argc,char *argv[]){
	if (argc != 3) {
		perror("2 paramètres nécessaires");
		exit(1);
	}

	int i=0;
	char *prefixe_fichier;

	n = atoi(argv[1]);
	pid_primaire = atoi(argv[2]);
	tab=(3*n);

	if(getenv("PREFIXE") != NULL){
		prefixe_fichier = malloc(4+sizeof(getenv("PREFIXE")));
		snprintf(prefixe_fichier, sizeof(prefixe_fichier), "%s", getenv("PREFIXE"));
		sprintf(prefixe_fichier + strlen(prefixe_fichier), "_St");
		sprintf(prefixe_fichier + strlen(prefixe_fichier), "%s", argv[1]);
		stdout = fopen(prefixe_fichier, "w+");
	}

    state = IDLE;
    string_state = string_idle;

    // TODO DEGAGE
    // printf("SECONDAIRE state = %d et string_state = %s\n", state, string_state);

	// printf("Je suis secondaire%d, mes paramètres sont : n=%d, pid_primaire=%d.\n", n, n, pid_primaire);


	//
	// printf("%d",n);


	for EVER{
		switch(state){
			case IDLE:
				printState();
				printf("\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				pause();
			break;
			case W_POLL:
				printState();
				printf("Attente\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				signal(POLL_RX, invitationEmission);
				pause();
			break;
			case SD_DATA:
				printState();
				printf("\n");
				signal(DATA_RX, receptionDonnee);

				pause();
			break;
			case W_ACK:
				printState();
				printf("\n");
				signal(DATA_RX, receptionDonnee);
				signal(ACK_RX, receptionAcquittement);
				pause();
			break;
		}
	}

	return(EXIT_SUCCESS);
}

void invitationEmission(){
	printState();
	printf("Poll_Rx\n");
	state = SD_DATA;
	string_state = string_sd_data;
}

void printState(){
	int i;

	for(i=0;i<=tab;i++)
		printf("\t");

	printf("St%d %s", n, string_state);
}

void receptionAcquittement(){
	printState();
	printf(" Ack_Rx %d\n", nb_data_req_rx);
	if(nb_data_req_rx > 0){
		nb_data_req_rx--;
	}
	if(nb_data_req_rx == 0){
		state = IDLE;
		string_state = string_idle;
	}else{
		state = W_POLL;
		string_state = string_w_poll;
	}
}

void receptionDonnee(int sig){
	printState();
	printf(" Data_rx\n");
}

void requeteEmission(){
	printState();
	printf(" Data_Req_Rx %d\n", nb_data_req_rx);
	if(state == IDLE){
		state = W_POLL;
		string_state = string_w_poll;
	}
	nb_data_req_rx++;
}
