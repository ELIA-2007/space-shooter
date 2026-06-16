#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float health;
	float moveSpeed;
	float damage;
	int unsigned shootingCooldown;
	int unsigned shootingCooldownMax;

	//Private functions
	void initVariables();
	void initSprite(sf::Texture* texture, sf::Vector2u windowSize);

public:
	Player(sf::Texture* texture, sf::Vector2u windowSize);
	virtual ~Player();

	//Accessor
	sf::Vector2f direction;
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getSize() const;
	float getDamage();

	//Functions
	void move(sf::Vector2f vector);

	void setPosition(float x, float y);
	bool canAttack();
	void getHit(float damage);
	float getHealth();
	void updateCooldowns();
	void update();
	void render(sf::RenderTarget& target);
};

#endif PLAYER_H