all: flight

flight: main.o Jet.o MatrizR.o Vector3d.o
	g++ main.o Jet.o MatrizR.o Vector3d.o -o flight -lGL -lGLU -lglut -lalut -lopenal -lSDL2

main.o: main.cpp
	g++ -c main.cpp -std=c++11

Jet.o: Jet.cpp
	g++ -c Jet.cpp -std=c++11

MatrizR.o: MatrizR.cpp
	g++ -c MatrizR.cpp -std=c++11

Vector3d.o: Vector3d.cpp
	g++ -c Vector3d.cpp -std=c++11

clean:
	rm *o flight
