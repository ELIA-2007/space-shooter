#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	float moveSpeed;
	float health;
	float damage;

private:

public:
	virtual float getHealth();
	virtual float getDamage();
	virtual void getHit(float damage);
	virtual const sf::FloatRect getBounds() const;

	virtual void update(float dt);
	virtual void render(sf::RenderTarget& target);
};

#endif