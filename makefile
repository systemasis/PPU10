poll_config: primaire secondaire trafic
	mkdir -p bin
	gcc -o poll_config src/poll_config.c

primaire: src/primaire.c
	mkdir -p bin
	gcc -o primaire src/primaire.c

secondaire: src/secondaire.c
	mkdir -p bin
	gcc -o secondaire src/secondaire.c

trafic: src/trafic.c
	mkdir -p bin
	gcc -o trafic src/trafic.c
