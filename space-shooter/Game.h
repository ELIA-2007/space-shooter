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
	
	sf::Clock deltaClock;
	sf::Time dtTime;
	float dt;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Debug
	bool debug;
	unsigned short f1KeyCooldown;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font> fonts;

	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	float spawnRate = 3;
	float spawning = spawnRate;

	//Player
	Player* player;
	Asteroid* asteroid;

	//Private functions
	void initWindow();
	void initTextures();
	void initFonts();

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