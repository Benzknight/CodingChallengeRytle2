#include <iostream>

#include "Cube.h"

Cube::Cube()
{

}

bool Cube::addChildCube(Cube* child)
{
	for (Cube* cube : m_childCubes)
	{
		if (cube->getId() == child->getId())
		{
			std::cerr << "Cube already exists as child. Cube will not be added";
			return false;
		}
	}

	m_childCubes.push_back(child);

	return true;
}

Cube* Cube::createCube(std::list<Cube*>*cubes, std::string id, CubeType type, std::string ownerId, std::vector<std::string> childIds)
{
	Cube* newCube = new Cube();

	newCube->setId(id);
	newCube->setCubeType(type);

	if (ownerId.length() == 0 && type != CubeType::SMALL)
	{
		if (cubes->size() == 0)
		{
			cubes->push_back(newCube);

			if (childIds.size() > 0)
			{
				for (std::string childId : childIds)
				{
					createCube(cubes, childId, CubeType::SMALL, id);
				}
			}

			return newCube;
		}

		for (Cube* cube : *cubes)
		{
			if (cube->getId() == newCube->getId())
			{
				return NULL;
			}
			else
			{
				cubes->push_back(newCube);

				if (childIds.size() > 0)
				{
					for (std::string childId : childIds)
					{
						createCube(cubes, childId, CubeType::SMALL, id);
					}
				}

				return newCube;
			}
		}
	}
	else
	{
		newCube->setOwnerId(ownerId);

		for (Cube* cube : *cubes)
		{
			if (cube->getId() == ownerId)
			{
				bool bOk = cube->addChildCube(newCube);

				if (!bOk)
				{
					return NULL;
				}
				else
				{
					cubes->push_back(newCube);
					return newCube;
				}
			}
		}
	}
}

std::list<Cube*> Cube::deleteCube(std::list<Cube*>*cubes, std::string id, bool deleteChilds)
{
	std::list<Cube*> deletedCubes;

	//Get cube which is supposed to be deleted for easier access later on
	Cube* cubeToDelete = new Cube();
	for (Cube* cube : *cubes)
	{
		if (cube->getId() == id)
		{
			cubeToDelete = cube;
		}
	}

	if (deleteChilds && cubeToDelete->getType() == CubeType::SMALL)
	{
		std::cerr << "Cannot delete one small cube from another small cube!";
		return deletedCubes;
	}
	else if (deleteChilds && cubeToDelete->getType() == CubeType::BIG)
	{
		for (Cube* childCube : cubeToDelete->getChildren())
		{
			cubes->remove(childCube);

			deletedCubes.push_back(childCube);
		}

		cubes->remove(cubeToDelete);

		deletedCubes.push_back(cubeToDelete);

		return deletedCubes;
	}
	else if (!deleteChilds && cubeToDelete->getType() == CubeType::SMALL)
	{
		for (Cube* cube : *cubes)
		{
			if (cube->getId() == cubeToDelete->getOwnerId())
			{
				cube->getChildren().remove(cubeToDelete);
			}
		}

		cubes->remove(cubeToDelete);

		deletedCubes.push_back(cubeToDelete);

		return deletedCubes;
	}
	else if (!deleteChilds && cubeToDelete->getType() == CubeType::BIG)
	{
		cubes->remove(cubeToDelete);

		deletedCubes.push_back(cubeToDelete);

		for (Cube* cube : *cubes)
		{
			if (cube->getOwnerId() == cubeToDelete->getId())
			{
				cube->setOwnerId("");
			}
		}

		return deletedCubes;
	}
}