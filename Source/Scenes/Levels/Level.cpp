#include "Level.h"
#include <fstream>
#include <filesystem>


Level::Level(std::string name) : Node2D(name) {
	addChild(navMesh);

	addChild(worldLayer);
	addChild(itemLayer);
	addChild(projectileLayer);
	addChild(enemyLayer);
	addChild(playerLayer);
	addChild(uiLayer);

	uiLayer->addChild(itemsHUD);
}

void Level::ready() {
	__super::ready();

	if (currentPlayer != nullptr) {
		currentPlayer->itemsHUD = itemsHUD;
	}


	generateLevel();

	navMesh->size = Vector2D(2000, 2000);
	navMesh->boxSize = tileSize;
	//bake the mesh
	navMesh->bakeMesh();
}

void Level::update(float delta) {
	__super::update(delta);

	if (currentPlayer != nullptr) {

		Vector2D drawPosition = currentPlayer->getGlobalPosition();
		drawPosition = navMesh->globalToMap(drawPosition);
		drawPosition.x *= navMesh->boxSize.x;
		drawPosition.y *= navMesh->boxSize.y;
	}
}

void Level::generateLevel() {

	std::srand(std::time({}));

	int numOfRooms = 0;

	Cell* startingRoom = new Cell();
	startingRoom->spawn = true;
	startingRoom->position = Vector2D(0, 0);

	
	List<Cell*> queue;
	queue.add(startingRoom);

	while (!queue.isEmpty()) {

		Cell* currentRoom = queue.remove(0);
		rooms.add(currentRoom);
		numOfRooms++;



		//randomly start at the starting room again
		if (currentRoom != startingRoom) {
			if (std::rand() % 8 == 1) {
				currentRoom->end = true;
				currentRoom = startingRoom;
			}
		}
		



		//while we don't have enough rooms, keep generating more
		if (numOfRooms < maxRooms) {

			Cell* newRoom = new Cell();

			bool neighborFree = false;
			Vector2D newPos;

			while (!neighborFree) {

				neighborFree = true;
				newPos = Vector2D(0, 0);

				while (newPos == Vector2D(0, 0)) {
					newPos.x = (std::rand() % 3) - 1;

					if (newPos.x == 0) {
						newPos.y = (std::rand() % 3) - 1;
					}
				}

				newPos.x += currentRoom->position.x;
				newPos.y += currentRoom->position.y;

				for (int i = 0; i < rooms.getSize(); i++) {
					if (rooms.get(i)->position == newPos) {
						neighborFree = false;
					}
				}
			}

			newRoom->position = newPos;

			currentRoom->neighbors.add(newRoom);
			newRoom->neighbors.add(currentRoom);

			queue.add(newRoom);
		}
	}
	

	for (int i = 0; i < rooms.getSize(); i++) {

		insertRoom(rooms.get(i));
		std::cout << "next\n";
	}

	std::cout << "finished\n";
}

void Level::insertRoom(Cell* room) {

	std::string prefabDirectory = getSceneTree()->getBasePath() + "../Prefabs";
	List<std::string> validPrefabs;

	std::string selectedPrefab = "";
	
	for (const auto& entry : std::filesystem::directory_iterator(prefabDirectory)) {
		std::string path = entry.path().string();
		std::string name = path.substr(prefabDirectory.length() + 1, path.length());


		if (name.substr(0, 5) == "start") {
			if (room->spawn) {

				std::cout << "start\n";
				validPrefabs.add(name);
				continue;
			}
		}

		else if (name.substr(0, 4) == "exit") {
			if (!exitCreated) {
				if (room->end) {
					validPrefabs.add(name);
					exitCreated = true;
					continue;
				}
			}
		}


		else {
			if (!room->spawn && !room->end) {
				validPrefabs.add(name);
			}
		}
		
	}


	while (selectedPrefab.empty()) {
		for (int i = 0; i < validPrefabs.getSize(); i++) {

			std::cout <<  validPrefabs.getSize() << " valid prefab size\n";
			std::cout << validPrefabs.get(i) << "\n";

			if (std::rand() % validPrefabs.getSize() == 0) {
				selectedPrefab = prefabDirectory + "/" + validPrefabs.get(i);
				break;
			}
		}
	}


	std::ifstream prefab(selectedPrefab);
	
	std::string roomInfo;
	bool startDrawingLevel = false;

	Vector2D roomPos = room->position;
	roomPos.x *= roomSize.x;
	roomPos.y *= roomSize.y - (2 * tileSize.y);

	int layer = roomPos.y;

	while (std::getline(prefab, roomInfo)) {

		if (roomInfo[0] == '.') {
			startDrawingLevel = true;
			roomInfo = roomInfo.substr(1);
		}

		if (startDrawingLevel) {

			std::cout << roomInfo << "\n";
			int pos = roomPos.x;

			for (int i = 0; i < roomInfo.size(); i++) {
				
				bool skipTile = false;

				for (int j = 0; j < room->neighbors.getSize(); j++) {


					float lowerX = roomPos.y + floor(roomSize.y / 2) - tileSize.y * 2;
					float upperX = roomPos.y + floor(roomSize.y / 2) ;
					float lowerY = roomPos.x + floor(roomSize.x / 2) - tileSize.x;
					float upperY = roomPos.x + floor(roomSize.x / 2) + tileSize.x;

					if (room->neighbors.get(j)->position.x < room->position.x) {
						if (pos == roomPos.x) {
							if (layer >= lowerX && layer <= upperX) {
								skipTile = true;
							}
						}
					}
					else if (room->neighbors.get(j)->position.x > room->position.x) {
						if (pos == roomPos.x + roomSize.x) {
							if (layer >= lowerX && layer <= upperX) {
								skipTile = true;
							}
						}
					}
					else if(room->neighbors.get(j)->position.y < room->position.y) {
						if (layer == roomPos.y) {
							if (pos >= lowerY && pos <= upperY) {
								skipTile = true;
							}
						}
					}
					else if (room->neighbors.get(j)->position.y > room->position.y) {
						if (layer == roomPos.y + roomSize.y - tileSize.y * 2) {
							if (pos >= lowerY && pos <= upperY) {
								skipTile = true;
							}
						}
					}
				}


				char tile = roomInfo[i];
				Vector2D tilePosition = Vector2D(pos + roomsOffset.x, layer + roomsOffset.y);
				Vector2D halfTileSize = Vector2D(tileSize.x / 2, tileSize.y / 2);

				bool overrideTile = false;

				if (!skipTile) {
					if (tile == 'w') {
						CollisionBody* body = new CollisionBody();
						body->position = tilePosition;
						worldLayer->addChild(body);

						CollisionRect* rect = new CollisionRect();
						rect->setSize(tileSize);
						body->addChild(rect);

						createTile(0, tilePosition);
						overrideTile = true;
					}

					else if (tile == 's') {
						if (room->spawn) {
							currentPlayer->position = tilePosition;
							currentPlayer->position.x += halfTileSize.x;
							currentPlayer->position.y += halfTileSize.y;
						}

					}

					else if (tile == 'e') {
						Enemy* enemy = new Enemy();
						enemy->position = tilePosition;
						enemy->position.x += halfTileSize.x;
						enemy->position.y += halfTileSize.y;
						enemyLayer->addChild(enemy);

					}
					else if (tile == 'g') {
						Pistol* pistol = new Pistol();
						pistol->position = tilePosition;
						pistol->position.x += halfTileSize.x;
						pistol->position.y += halfTileSize.y;
						itemLayer->addChild(pistol);

					}
				}

				if (!overrideTile) {
					createTile(1, tilePosition);
				}
				
				pos += tileSize.x;
				
			}

			layer += tileSize.y;


		}


		
	}


	prefab.close();
}

void Level::createTile(int tileID, Vector2D position) {
	Sprite* sprite = new Sprite();
	sprite->position = position;
	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Tiles/Tileset.png");
	sprite->setHFrames(tilesetWidth);
	sprite->setVFrames(tilesetHeight);
	sprite->frame = tileID;
	worldLayer->addChild(sprite);
}