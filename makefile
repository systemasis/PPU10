poll_config: primaire secondaire trafic
	mkdir -p bin
	gcc -o bin/poll_config src/poll_config.c

primaire: src/primaire.c
	mkdir -p bin
	gcc -o bin/primaire src/primaire.c

secondaire: src/secondaire.c
	mkdir -p bin
	gcc -o bin/secondaire src/secondaire.c

trafic: src/trafic.c
	mkdir -p bin
	gcc -o bin/trafic src/trafic.c
