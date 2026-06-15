#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Asteroid {
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float spawnX;
	float spawnY;
	float targetX;
	float targetY;
	float moveSpeed;
	int rotationAngle;
	unsigned int rotationSpeed;
	float size;
	float health;
	sf::Vector2f velocity;


	//Private functions
	void initVariables();
	void initSprite(sf::Texture* texture, sf::Vector2u windowSize);
	void initMovement();



public:
	Asteroid(sf::Texture* texture, sf::Vector2u windowSize);
	virtual ~Asteroid();

	//Accessor
	void getHit(float damage);
	bool Destroyed();
	const sf::FloatRect getBounds() const;



	void update();
	void render(sf::RenderTarget& target);



};

#endif