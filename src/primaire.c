#include "polling.h"
#include "header.h"

void arriverData();
void printIni(int valeur);

int nb_data_req_rx = 0;

int main (int argc,char **argv){
	if(argc < 4){
		perror("Au moins 3 paramètres attendus");
		exit(1);
	}

	int nb_polling = atoi(argv[1]), delai_poll = atoi(argv[2]),
		n = atoi(argv[3]), i, j, compteur, p, nombre_pid=0,
		tab_secondaire[MAX_ST];
	char *prefixe_fichier;

	for(i=0;i<5;i++){
		if(argv[4+i][0] != 0)
			nombre_pid++;
	}

	for(i=0;i<nombre_pid;i++){
		tab_secondaire[i]=atoi(argv[4+i]);
	}

	if(getenv("PREFIXE") != NULL){
		prefixe_fichier = malloc(4+sizeof(getenv("PREFIXE")));
		snprintf(prefixe_fichier, sizeof(prefixe_fichier), "%s", getenv("PREFIXE"));
		sprintf(prefixe_fichier + strlen(prefixe_fichier), "_prim");
		stdout = fopen(prefixe_fichier, "w+");
	}

	fprintf(stdout, "Je suis primaire, mes paramètres sont : nb_polling=%d, delai_poll=%d, n=%d", nb_polling, delai_poll, n);

	for(i=4; i<argc;i++){
		fprintf(stdout, ", pid_St%d=%d", i, atoi(argv[i]));
	}
	fprintf(stdout, ".\n");

	fflush(stdout);

	state=W_REQ;
	string_state=string_w_req;
	for (i=0; i<nb_polling;i++){
		//parcourt le tableau des pid secondaire
		for(j=0;j<nombre_pid;j++){
			kill(tab_secondaire[j], POLL_TX);
			switch(state){
				fflush(stdout);
				case W_REQ:
					printIni(j);
					fprintf(stdout," %ds\n",delai_poll);
					signal(DATA_RX,arriverData);
					sleep(delai_poll);//permet d attendre delai_poll secondes
					// signal(DATA_RX,SIG_IGN);
					if(nb_data_req_rx==1){
						printIni(j);
						fprintf(stdout," Data_RX\n");
						state=BC_DATA;
						string_state = string_bc_data;
					}else{
						printIni(j);
						fprintf(stdout," N_Data\n");
					}
				break;
				case BC_DATA:
					printIni(j);
					fprintf(stdout,"\n");

					for(p=0;p<nombre_pid;p++){
						if(p != j){
							kill(tab_secondaire[p], ACK_TX);
						}
					}

					kill(tab_secondaire[j], ACK_TX);
					state=W_REQ;
					string_state=string_w_req;
					nb_data_req_rx = 0;
				break;

			}//switch des etats

			// }//sign bien envoyer a chaque station secondaire
			// else{
			// 	perror("probleme a l'envoie du signal POLL_TX");
			// 	exit(1);
			// }
		}
	}

	return(EXIT_SUCCESS);
}


void arriverData(){
	nb_data_req_rx = 1;
}
void printIni(int valeur ){
	fprintf(stdout,"Prim %s St%d", string_state, valeur+1);
}
