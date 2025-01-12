#include "Level.h"

Level::Level(std::string name) : Node2D(name) {

}

void Level::ready() {
	__super::ready();

	//bake the mesh
	navMesh.bakeMesh();
}