SOURCES = classifier.c funciones.c

FILE = classifier

ZIPFILE = Archivos_de_prueba.zip

.PHONY: all run unzip build clean 

all: build unzip run

build:
	gcc $(SOURCES) -o $(FILE) -Wall
	
unzip:
	unzip testCases/$(ZIPFILE) -d ./testCases

run:
	./$(FILE)

clean:
	rm $(FILE)
	rm -r clasificacion

