poll_config: primaire secondaire trafic
	gcc -o poll_config src/poll_config.c

primaire: src/primaire.c
	gcc -o primaire src/primaire.c

secondaire: src/secondaire.c
	gcc -o secondaire src/secondaire.c

trafic: src/trafic.c
	gcc -o trafic src/trafic.c
