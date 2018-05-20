all: pthreads openmp

multMatPth: pth.c
	gcc -ansi -pedantic -Wall -O2 -pthread $< -o $@

multMatOpenMp: SeR.c
	gcc -ansi -pedantic -Wall -O2 -pthread $< -o $@

#clean: m-ep2 pacote
#	rm m-ep2
#	rm -rf ./andre.silveira.mauricio.cardoso

runpthreads: multMatPth
	./$< < matrizes.txt

runopenmp: multMatOpenMp
	./$< < matrizes.txt

pacote:
	mkdir andre.silveira.mauricio.cardoso
	cp *.c ./andre.silveira.mauricio.cardoso
	cp *.txt ./andre.silveira.mauricio.cardoso
	cp Makefile ./andre.silveira.mauricio.cardoso
	#tar-cvfandre.silveira.tarandre.silveira.mauricio.cardoso
	zip andre.silveira.mauricio.cardoso.zip andre.silveira.mauricio.cardoso/*
	rm -rf andre.silveira.mauricio.cardoso
