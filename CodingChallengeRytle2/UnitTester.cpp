#include <gtest/gtest.h>
#include <iostream>

#include "Cube.h"

TEST(CubeTest, createCubeTest)
{
	std::cout << "Testcase createCubeTest start.";
	std::list<Cube*> existingCubes;
	Cube* cube = nullptr;

	std::cout << "TestStep: 1";
	std::cout << "Creating a big cube with ID 0";
	cube = Cube::createCube(&existingCubes, "0", CubeType::BIG);

	EXPECT_EQ(existingCubes.size(), 1);

	std::cout << "TestStep: 2";
	std::cout << "Creating a big cube with same ID";
	cube = Cube::createCube(&existingCubes, "0", CubeType::BIG);

	EXPECT_EQ(existingCubes.size(), 1);

	std::cout << "TestStep: 3";
	std::cout << "Creating a small cube with ID 1";
	cube = Cube::createCube(&existingCubes, "1", CubeType::SMALL, "0");

	EXPECT_EQ(existingCubes.size(), 2);

	std::cout << "Testcase createCubeTest end.";
}

TEST(CubeTest, createMultipleCubesTest)
{
	std::cout << "Testcase createMultipleCubesTest start.";
	std::list<Cube*> existingCubes;
	Cube* cube = nullptr;

	std::cout << "TestStep: 1";
	std::cout << "Creating a big cube with ID 0 and multiple childcubes";
	std::vector<std::string> children = {"1", "2"};
	cube = Cube::createCube(&existingCubes, "0", CubeType::BIG, "", children);

	int a = 1;
	a = 0;

	EXPECT_EQ(existingCubes.size(), 3);

	std::cout << "Testcase createMultipleCubesTest end.";
}

TEST(CubeTest, deleteCubeTest)
{
	std::cout << "Testcase deleteCubeTest start.";
	std::list<Cube*> existingCubes;
	std::list<Cube*> deletedCubes;

	Cube::createCube(&existingCubes, "0", CubeType::BIG);
	Cube::createCube(&existingCubes, "1", CubeType::SMALL, "0");

	std::cout << "TestStep: 1";
	std::cout << "Deleting a big cube with ID 0";
	deletedCubes = Cube::deleteCube(&existingCubes, "0", false);

	EXPECT_EQ(deletedCubes.size(), 1);
	EXPECT_EQ(existingCubes.size(), 1);

	std::cout << "TestStep: 2";
	std::cout << "Checking whether the remaining small cube has no owner anymore";
	bool bOk = false;
	for (Cube* cube : existingCubes)
	{
		if (cube->getId() == "1")
		{
			if (cube->getOwnerId().length() == 0)
			{
				bOk = true;
			}
		}
	}

	EXPECT_TRUE(bOk);

	std::cout << "TestStep: 3";
	std::cout << "Deleting the remaining small cube";
	deletedCubes = Cube::deleteCube(&existingCubes, "1", false);

	EXPECT_EQ(deletedCubes.size(), 1);
	EXPECT_EQ(existingCubes.size(), 0);

	std::cout << "Testcase deleteCubeTest end.";
}

TEST(CubeTest, deleteMultipleCubesTest)
{
	std::cout << "Testcase deleteMultipleCubesTest start.";
	std::list<Cube*> existingCubes;
	std::list<Cube*> deletedCubes;

	std::vector<std::string> children = {"1","2"};
	Cube::createCube(&existingCubes, "0", CubeType::BIG, "", children);
	Cube::createCube(&existingCubes, "3", CubeType::BIG);
	Cube::createCube(&existingCubes, "4", CubeType::SMALL, "3");
	Cube::createCube(&existingCubes, "5", CubeType::SMALL, "3");

	std::cout << "TestStep: 1";
	std::cout << "Deleting a big cube with ID 0 and with deleteChildren TRUE";
	deletedCubes = Cube::deleteCube(&existingCubes, "0", true);

	EXPECT_EQ(deletedCubes.size(), 3);
	EXPECT_EQ(existingCubes.size(), 3);

	std::cout << "TestStep: 1";
	std::cout << "Deleting a big cube with ID 0 and with deleteChildren FALSE";
	deletedCubes = Cube::deleteCube(&existingCubes, "3", false);

	EXPECT_EQ(deletedCubes.size(), 1);
	EXPECT_EQ(existingCubes.size(), 2);

	std::cout << "Testcase deleteMultipleCubesTest end.";
}