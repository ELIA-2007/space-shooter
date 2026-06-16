#ifndef GAME_H
#define GAME_H

#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "functions.h"

class Game {
private:
	//Window
	sf::RenderWindow* window;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	unsigned int spawnRate = 1000;
	unsigned int spawning = spawnRate;

	//Player
	Player* player;
	Asteroid* asteroid;

	//Private functions
	void initWindow();
	void initTextures();

	void initPlayer();

public:
	Game();

	virtual ~Game();

	//Functions
	void run();


	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateAsteroids();
	void spawnEnemies();
	void update();
	void render();

};

#endif