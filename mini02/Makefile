all: run

m-ep2: SeR.c
	gcc -ansi -pedantic -Wall -O2 $< -o m-ep1

clean: m-ep2
	rm $<
	rm -rf ./andre.silveira.mauricio.cardoso

run: m-ep2
	./$<

pacote:	
	mkdir andre.silveira.mauricio.cardoso
	cp *.c ./andre.silveira.mauricio.cardoso
	#cp *.txt ./andre.silveira.mauricio.cardoso
	cp Makefile ./andre.silveira.mauricio.cardoso
	#tar -cvf andre.silveira.tar andre.silveira.mauricio.cardoso
    	7z a -r andre.silveira.mauricio.cardoso.7z eps-andre.silveira.mauricio.cardoso
	rm -rf andre.silveira.mauricio.cardoso
