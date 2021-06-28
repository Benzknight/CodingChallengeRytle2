#pragma once

#include <string>
#include <list>
#include <vector>

enum class CubeType {
	SMALL,
	BIG
};

class Cube {
public:
	Cube();

	void setId(std::string id) { m_uniqueId = id; }
	void setOwnerId(std::string ownerId) { m_ownerId = ownerId; }
	void setCubeType(CubeType type) { m_type = type; }

	std::string getId() { return m_uniqueId; }
	std::string getOwnerId() { return m_ownerId; }
	CubeType getType() { return m_type; }
	std::list<Cube*> getChildren() { return m_childCubes; }

	bool addChildCube(Cube* child);

	//Functionsignature changed from assigned task in regards to the ownerId beeing standard NULL to ""
	//Changed the array of strings for childIds to std::vector for easier handling
	static Cube* createCube(std::list<Cube*>* cubes, std::string id, CubeType type, std::string ownerId = "", std::vector<std::string> childIds = {});
	static std::list<Cube*> deleteCube(std::list<Cube*>*cubes, std::string id, bool deleteChilds);

private:
	std::string m_uniqueId;
	std::string m_ownerId = "";
	CubeType m_type;
	std::list<Cube*> m_childCubes;
};
