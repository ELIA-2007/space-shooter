#ifndef ASTEROID_H
#define ASTEROID_H

#include "Enemy.h"

class Asteroid : public Enemy{
private:
	float spawnX;
	float spawnY;
	float targetX;
	float targetY;
	int rotationAngle;
	unsigned int rotationSpeed;
	float size;
	sf::Vector2f velocity;


	//Private functions
	void initVariables();
	void initSprite(sf::Texture* texture, sf::Vector2u windowSize);
	void initMovement();



public:
	Asteroid(sf::Texture* texture, sf::Vector2u windowSize);
	virtual ~Asteroid();

	void update();
	
};

#endif