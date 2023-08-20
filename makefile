SOURCES = classifier.c funciones.c

FILE = classifier

ZIPFILE = Archivos_de_prueba.zip

.PHONY: all run unzip build clean 

all: build unzip run

build:
	gcc $(SOURCES) -o $(FILE) -ggdb3 -Wall
	
unzip:
	unzip testCases/$(ZIPFILE) -d ./testCases

run:
	./$(FILE)

clean:
	rm $(FILE)
	rm -r clasificacion

all_gen: build_g run_g clean_g

build_g:
	g++ generator.cpp -o generator -Wall

run_g: 
	./generator

clean_g:
	rm generator