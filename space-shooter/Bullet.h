#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Bullet {
private:
	sf::Sprite sprite;

	sf::Vector2f direction;
	float moveSpeed;

public:
	Bullet(sf::Texture* texture, sf::Vector2u windowSize, float posX, float posY, float dirX, float dirY, float move_speed);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	void initSprite(sf::Texture* texture, sf::Vector2u windowSize);
	void update(float dt);
	void render(sf::RenderTarget* target);
};

#endif // !BULLET_H