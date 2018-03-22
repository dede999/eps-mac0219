all: run

m-ep1: m-ep.c
	gcc -ansi -pedantic -Wall -O2 $< -o m-ep1

clean: m-ep1
	rm $<
	rm -rf ./andre.silveira

run: m-ep1
	./$<

pacote:	
	mkdir andre.silveira
	cp *.c ./andre.silveira
	cp *.txt ./andre.silveira
	cp Makefile ./andre.silveira
	tar -cvf andre.silveira.tar andre.silveira
	rm -rf andre.silveira