#include "polling.h"

int main (int argc,char *argv[]){
	if (argc != 5) {
		fprintf(stderr, "erreur: pas le bo nombre de parametre\n");
		return 1;
    	}
	char *primaire	      = argv[1];
	char *secondaire      = argv[2];
	char *trafic	      = argv[3];
	int n	 	      = atoi(argv[4]); //nombre de station
	//int nb_polling      = atoi(argv[5]);
	//int delai_polling     = atoi(argv[6]);
	/*int delai_min_requete = atoi(argv[7]);
	int delai_max_requete = atoi(argv[8]);
	*/
	state = IDLE;
	string_state = string_idle; 
	int pid=fork();
	int numero_station=1;
	if(pid==0){
		//printf("%s\n",secondaire);
		/*execl(secondaire,numero_station,pid,NULL);
		perror(secondaire);
		exit(EXIT_FAILURE);*/
	}
	else{	
		
		for(numero_station=numero_station+1;numero_station<=n;numero_station++){
			pid=fork();
			if(pid==0){
				//execl(secondaire,numero_station,pid,NULL);
				//perror(secondaire);
				//exit(EXIT_FAILURE);
			}
			//execl(primaire,nb_polling,delai_polling,n,);
		}
		
		
	}
	exit(EXIT_SUCCESS);
}
