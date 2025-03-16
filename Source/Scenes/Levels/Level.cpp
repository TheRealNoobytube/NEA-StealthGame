#include "Level.h"


Level::Level(std::string name) : Node2D(name) {
	addChild(navMesh);

	addChild(worldLayer);
	addChild(itemLayer);
	addChild(enemyLayer);
	addChild(playerLayer);
	addChild(projectileLayer);
	addChild(uiLayer);
	
	uiLayer->addChild(itemsHUD);
	uiLayer->addChild(healthBar);
	uiLayer->addChild(evasionBar);

	addChild(chaseTimer);
	addChild(evasionTimer);

	addChild(gameOverScreen);

}

void Level::ready() {
	__super::ready();

	if (currentPlayer != nullptr) {
		currentPlayer->itemsHUD = itemsHUD;
		healthBar->background.setTexture(getSceneTree()->getBasePath() + "../Assets/HealthBar/HealthBarBG.png");
		healthBar->progress.setTexture(getSceneTree()->getBasePath() + "../Assets/HealthBar/HealthBar.png");

		healthBar->position = Vector2D(3, 3);
		healthBar->setMin(0);
		healthBar->setMax(currentPlayer->health->getMaxHealth());
		healthBar->setSize(Vector2D(112, 16));

		currentPlayer->health->death.connect([this](float a) { onGameOver(); });
	}


	evasionBar->ignoreRenderOffset = true;
	evasionBar->setTexture(getSceneTree()->getBasePath() + "../Assets/EvasionBar/EvasionBar.png");
	evasionBar->setHFrames(3);
	evasionBar->position.x = getSceneTree()->getViewportSize().x - (evasionBar->getTexture()->getDimensions().x / evasionBar->getHFrames());


	generateLevel();

	navMesh->size = Vector2D(2000, 2000);
	navMesh->boxSize = tileSize;
	//navMesh->boxSize.x /= 2;
	//navMesh->boxSize.y /= 2;

	//navMesh->drawMap = true;
	//bake the mesh
	navMesh->bakeMesh();


	chaseTimer->setLength(5);
	chaseTimer->timeout.connect([this]() {

		evasionBar->frame = 1;

		for (int i = 0; i < enemyLayer->getChildCount(); i++) {
			Enemy* enemy = reinterpret_cast<Enemy*>(enemyLayer->getChild(i));
			enemy->lostPlayer();
			chaseStarted = false;
		}

		});
	chaseTimer->loop = false;

}


void Level::startChase() {
	if (chaseStarted) {
		return;
	}


	evasionBar->frame = 2;

	chaseStarted = true;

	for (int i = 0; i < enemyLayer->getChildCount(); i++) {
		Enemy* enemy = reinterpret_cast<Enemy*>(enemyLayer->getChild(i));
		enemy->foundPlayer();
	}
}

void Level::update(float delta) {
	__super::update(delta);

	if (currentPlayer != nullptr) {

		Vector2D drawPosition = currentPlayer->getGlobalPosition();
		drawPosition = navMesh->globalToMap(drawPosition);
		drawPosition.x *= navMesh->boxSize.x;
		drawPosition.y *= navMesh->boxSize.y;

		healthBar->setValue(currentPlayer->health->getHealth());
	}

	
	if (!chaseStarted) {

		evasionBar->frame = 0;

		for (int i = 0; i < enemyLayer->getChildCount(); i++) {
			Enemy* enemy = reinterpret_cast<Enemy*>(enemyLayer->getChild(i));
			
			if (enemy->currentState == Enemy::NOTICE || enemy->currentState == Enemy::ALERT) {
				evasionBar->frame = 1;
			}
		}
	}

}


void Level::onGameOver() {
	gameOverScreen->gameOver();
	chaseTimer->stop();
	itemsHUD->hideHUD();
	healthBar->visible = false;
	evasionBar->visible = false;

	for (int i = 0; i < enemyLayer->getChildCount(); i++) {
		Enemy* enemy = reinterpret_cast<Enemy*>(enemyLayer->getChild(i));
		enemy->disableAI = true;
		enemy->endPursuit();
	}

}

void Level::generateLevel() {

	std::srand(std::time({}));

	while (rooms.getSize() < maxRooms || endRooms.getSize() < minEndRooms) {

		std::cout << "\n\nRESTARTING\n\n";

		rooms.clear();
		endRooms.clear();

		Cell* startingRoom = new Cell();
		startingRoom->type = Cell::SPAWN;
		startingRoom->position = Vector2D(0, 0);
		startingRoom->color = Color(0, 255, 0, 100);

		int numOfRooms = 1;
		List<Cell*> queue;
		queue.add(startingRoom);

		while (!queue.isEmpty()) {

			Cell* currentRoom = queue.remove(0);
			bool addRoom = true;

			for (int i = 0; i < rooms.getSize(); i++) {
				if (rooms.get(i)->position == currentRoom->position) {
					currentRoom = rooms.get(i);
					addRoom = false;
					break;
				}
			}

			if (addRoom) {
				rooms.add(currentRoom);
			}
			else {
				numOfRooms--;
			}

			

			bool neighborCreated = false;

			for (int i = -1; i < 2; i += 2) {
				std::cout << numOfRooms << "\n";
				Cell* neighbor = determineNeighbor(Vector2D(currentRoom->position.x + i, currentRoom->position.y), numOfRooms);
				if (neighbor != nullptr) {
					std::cout << "\n\n NEIGHBOR POS: " << neighbor->position.x << "  " << neighbor->position.y << "\n";
					std::cout << "\n\n CURRENT POS: " << currentRoom->position.x << "  " << currentRoom->position.y << "\n\n\n";

					neighborCreated = true;
					currentRoom->neighbors.add(neighbor);
					neighbor->neighbors.add(currentRoom);
					queue.add(neighbor);
					numOfRooms++;
				}
			}

			for (int i = -1; i < 2; i += 2) {
				std::cout << numOfRooms << "\n";
				Cell* neighbor = determineNeighbor(Vector2D(currentRoom->position.x, currentRoom->position.y + i), numOfRooms);
				if (neighbor != nullptr) {

					std::cout << "\n\n NEIGHBOR POS: " << neighbor->position.x << "  " << neighbor->position.y << "\n";
					std::cout << "\n\n CURRENT POS: " << currentRoom->position.x << "  " << currentRoom->position.y << "\n\n\n";

					neighborCreated = true;
					currentRoom->neighbors.add(neighbor);
					neighbor->neighbors.add(currentRoom);
					queue.add(neighbor);
					numOfRooms++;
				}
			}

			if (!neighborCreated) {
				currentRoom->type = Cell::DEADEND;
				endRooms.add(currentRoom);

				std::cout << ">>>>>>>>dead end created\n";
			}
		}
	}


	endRooms.get(endRooms.getSize() - 1)->type = Cell::EXIT;

	for (int i = 0; i < rooms.getSize(); i++) {
		insertRoom(rooms.get(i));
	}

	rooms.clear();
	endRooms.clear();

}



Level::Cell* Level::determineNeighbor(Vector2D neighborPos,  int numOfRooms) {

	Cell* neighborRoom = new Cell();
	neighborRoom->position = neighborPos;


	bool giveUp = false;

	int numOfNeighbors = 0;

	for (int i = 0; i < rooms.getSize(); i++) {
		if (rooms.get(i)->position == neighborRoom->position) {
			giveUp = true;

			std::cout << ">>>>room taken\n";
			break;
		}

		if (rooms.get(i)->isNeighborTo(neighborRoom->position)) {
			numOfNeighbors++;
		}
	}

	if (numOfNeighbors > 1) {
		std::cout << ">>>>too many neighbors\n";
		giveUp = true;
	}

	else if (numOfRooms > maxRooms) {
		std::cout << ">>>>too many rooms\n";
		giveUp = true;
	}

	else if (std::rand() % 2 == 0) {
		std::cout << ">>>>just felt like it\n";
		giveUp = true;
	}


	if (giveUp) {
		delete neighborRoom;
		return nullptr;
	}
		
	return neighborRoom;
}





void Level::insertRoom(Cell* room) {

	//Decide what prefab to use for this room

	std::string prefabDirectory = getSceneTree()->getBasePath() + "../Prefabs";
	List<std::string> validPrefabs;

	std::string selectedPrefab = "";
	
	for (const auto& entry : std::filesystem::directory_iterator(prefabDirectory)) {
		std::string path = entry.path().string();
		std::string name = path.substr(prefabDirectory.length() + 1, path.length());

		if (name.substr(0, 5) == "start") {
			if (room->type == Cell::SPAWN) {
				std::cout << "start\n";
				validPrefabs.add(name);
				continue;
			}
		}

		else if (name.substr(0, 4) == "exit") {
			if (room->type == Cell::EXIT) {
				validPrefabs.add(name);
				exitCreated = true;
				continue;
			}
		}


		else {
			if (room->type == Cell::MID || room->type == Cell::DEADEND) {
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


	//draw the prefab into the world

	Enemy* enemies[10];

	std::ifstream prefab(selectedPrefab);
	
	std::string roomInfo;
	bool startDrawingLevel = false;
	bool startAddingPatrolPoints = false;

	Vector2D halfTileSize = Vector2D(tileSize.x / 2, tileSize.y / 2);
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
						if (room->type == Cell::SPAWN) {
							currentPlayer->position = tilePosition;
							currentPlayer->position.x += halfTileSize.x;
							currentPlayer->position.y += halfTileSize.y;
						}

					}

					else if (tile == 'e') {
						Enemy* enemy = new Enemy();
						enemy->position = tilePosition;
						enemy->position.x += halfTileSize.x;
						//enemy->position.y += halfTileSize.y;
						enemyLayer->addChild(enemy);

						if (i - 1 < roomInfo.length()) {
							int enemyID = roomInfo[i + 1] - '0';
							if (enemyID >= 0) {
								enemies[enemyID] = enemy;
								i++;
							}
						}
					}

					else if (tile == 'i') {

						if (room->type == Cell::DEADEND) {
							Ration* ration = new Ration();
							ration->position = tilePosition;
							ration->position.x += halfTileSize.x;
							ration->position.y += halfTileSize.y;
							itemLayer->addChild(ration);

						}
					}

					else if (tile == 'g') {
						Pistol* pistol = new Pistol();
						pistol->position = tilePosition;
						pistol->position.x += halfTileSize.x;
						pistol->position.y += halfTileSize.y;
						itemLayer->addChild(pistol);

					}

					else if (tile == '.') {
						overrideTile = true;
						startDrawingLevel = false;
						startAddingPatrolPoints = true;
					}
				}

				if (!overrideTile) {
					createTile(1, tilePosition);
				}
				
				pos += tileSize.x;
				
			}

			layer += tileSize.y;
		}



		//add enemy patrol points

		if (startAddingPatrolPoints) {
			if (std::isdigit(roomInfo[0])) {

				Enemy* enemy = enemies[roomInfo[0] - '0'];

				if (enemy == nullptr) {
					std::cout << "incorrect enemy id at line:   " << roomInfo << "\n";
					continue;
				}

				List<std::string> positions;

				bool recordingPosition = false;

				for (int i = 0; i < roomInfo.length(); i++) {

					if (recordingPosition) {

						if (roomInfo[i] == ')') {
							recordingPosition = false;
						} 
						else{
							positions.get(positions.getSize() - 1) += roomInfo[i];
						}
					}

					if (roomInfo[i] == '(') {
						recordingPosition = true;
						positions.add(std::string());
					}
				}


				for (int i = 0; i < positions.getSize(); i++) {
					int commaPoint = positions.get(i).find(',') + 1;

					Vector2D patrolPoint;

					patrolPoint.x = roomPos.x + roomsOffset.x;
					patrolPoint.x += (std::stoi( positions.get(i).substr(0, commaPoint) ) - 1 ) * tileSize.x;

					patrolPoint.y = roomPos.y + roomsOffset.y;
					patrolPoint.y += (std::stoi( positions.get(i).substr(commaPoint, positions.get(i).length()) ) - 1) * tileSize.y;
				

					std::cout << "yeag so " << patrolPoint.x << "  " << patrolPoint.y << "\n";

					enemy->patrolPoints.add(patrolPoint);

				}
			}
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

