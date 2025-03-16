#pragma once

#include "Source/HUD/ItemsHUD.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Pathfinding/NavigationMesh.h"
#include "Source/Nodes/Camera/Camera.h"
#include "Source/Weapons/Pistol/Pistol.h"
#include "Source/Nodes/Rectangle/Rectangle.h"
#include "Source/Items/Ration/Ration.h"
#include "Source/UI/ProgressBar/ProgressBar.h"
#include "Source/Scenes/GameOverScreen.h"
#include <fstream>
#include <filesystem>

class Player;
class Enemy;

class Level : public Node2D {
private:

	struct Cell {

		enum RoomType {
			SPAWN,
			MID,
			DEADEND,
			EXIT
		};

		Color color = Color(0, 255, 200, 100);

		RoomType type = MID;

		Vector2D position;

		List<Cell*> neighbors;


		bool isNeighborTo(Vector2D position) {

			if (this->position.x + 1 == position.x || this->position.x - 1 == position.x) {
				if (this->position.y == position.y) {
					return true;
				}
			}

			if (this->position.y + 1 == position.y || this->position.y - 1 == position.y) {
				if (this->position.x == position.x) {
					return true;
				}
			}

			return false;
		}

	};


	const int tilesetWidth = 2;
	const int tilesetHeight= 2;

	int maxRooms = 5;
	int minEndRooms = 2;

	List<Cell*> rooms;
	List<Cell*> endRooms;

	Vector2D roomsOffset = Vector2D(1000, 1000);

	Vector2D tileSize = Vector2D(10, 10);
	Vector2D roomDimensions = Vector2D(20, 20);

	Vector2D roomSize = Vector2D(tileSize.x * roomDimensions.x , tileSize.y * roomDimensions.y);

	bool exitCreated = false;

	void insertRoom(Cell* room);

	void createTile(int tileID, Vector2D position);

	Cell* determineNeighbor(Vector2D neighborPos, int numOfRooms);

public:
	Level(std::string name = "Level");

	bool chaseStarted = false;

	TimerNode* chaseTimer = new TimerNode();
	TimerNode* evasionTimer = new TimerNode();

	enum AggressionLevel {
		NORMAL,
		EVASION,
		CAUTION
	};

	AggressionLevel aggressionLevel = NORMAL;


	NavigationMesh* navMesh = new NavigationMesh();
	Player* currentPlayer = nullptr;

	GameOverScreen* gameOverScreen = new GameOverScreen();

	ItemsHUD* itemsHUD = new ItemsHUD();
	ProgressBar* healthBar = new ProgressBar();
	Sprite* evasionBar = new Sprite();


	Node2D* itemLayer = new Node2D();
	Node2D* worldLayer = new Node2D();
	Node2D* projectileLayer = new Node2D();
	Node2D* playerLayer = new Node2D();
	Node2D* enemyLayer = new Node2D();
	Node* uiLayer = new Node();

	

	void ready() override;
	void update(float delta) override;

	void generateLevel();
	void startChase();

	virtual void onGameOver();
};

#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"