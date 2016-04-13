all: physics

physics: main.o PhysicsBodyCube.o Vector3d.o
	g++ main.o PhysicsBodyCube.o Vector3d.o -o physics -lGL -lGLU -lglut -lalut -lopenal -lSDL2

main.o: main.cpp
	g++ -c main.cpp -std=c++11

PhysicsBodyCube.o: PhysicsBodyCube.cpp
	g++ -c PhysicsBodyCube.cpp -std=c++11

Vector3d.o: Vector3d.cpp
	g++ -c Vector3d.cpp -std=c++11

clean:
	rm *o physics