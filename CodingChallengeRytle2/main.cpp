#include <future>
#include <iostream>

#include "Cube.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	/*
	This comment section is intended to show how the implemented
	functions can be called in an asynchronous way with the help of std::async
	
	std::list<Cube*> existingCubes;

	Cube* newCube;
	std::future<Cube*> future = std::async(std::launch::async, &Cube::createCube, &existingCubes, "0", CubeType::BIG);
	newCube = future.get();
	*/

	return 0;
}