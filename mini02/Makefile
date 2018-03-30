all: run

m-ep2: SeR.c
	gcc -ansi -pedantic -Wall -O2 -pthread $< -o m-ep2

clean: m-ep2 pacote
	rm m-ep2
	rm -rf ./andre.silveira.mauricio.cardoso

run: m-ep2
	./$< 2 3

pacote:
	mkdir andre.silveira.mauricio.cardoso
	cp *.c ./andre.silveira.mauricio.cardoso
	#cp*.txt./andre.silveira.mauricio.cardoso
	cp Makefile ./andre.silveira.mauricio.cardoso
	#tar-cvfandre.silveira.tarandre.silveira.mauricio.cardoso
	zip andre.silveira.mauricio.cardoso.zip *
	rm -rf andre.silveira.mauricio.cardoso