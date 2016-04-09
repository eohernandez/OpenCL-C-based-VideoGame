all: flight

flight: main.o Jet.o MatrizR.o Vector3d.o
	g++ main.o Jet.o MatrizR.o Vector3d.o -o flight

main.o: main.cpp
	g++ -c main.cpp

Jet.o: Jet.cpp
	g++ -c Jet.cpp

MatrizR.o: MatrizR.cpp
	g++ -c MatrizR.cpp

Vector3d.o: Vector3d.cpp
	g++ -c Vector3d.cpp

clean:
	rm *o flight
