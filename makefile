poll_config: primaire secondaire trafic
	gcc -o poll_config poll_config.c

primaire: primaire.c
	gcc -o primaire primaire.c

secondaire: secondaire.c
	gcc -o secondaire secondaire.c

trafic: trafic.c
	gcc -o trafic trafic.c
