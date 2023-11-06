all: app

app: main.cpp Archivos.cpp Menu.cpp Operaciones.cpp Funciones.h 
	g++ -fopenmp main.cpp Archivos.cpp Menu.cpp Operaciones.cpp Funciones.h -o app

clean:
	rm -f app
