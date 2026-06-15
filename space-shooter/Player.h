#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float moveSpeed;
	int unsigned shootingCooldown;
	int unsigned shootingCooldownMax;

	//Private functions
	void initVariables();
	void initSprite(sf::Texture* texture, sf::Vector2u windowSize);

public:
	Player(sf::Texture* texture, sf::Vector2u windowSize);
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::Vector2f& getSize() const;

	//Functions
	void move(const float dirX, const float dirY);

	void setPosition(float x, float y);
	bool canAttack();
	void updateCooldowns();
	void update();
	void render(sf::RenderTarget& target);
};

#endif PLAYER_H