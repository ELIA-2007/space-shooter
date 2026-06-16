#include "Asteroid.h"
#include <iostream>
#include <random>
#include "functions.h"

void Asteroid::initVariables() {
	//Random number generator
	static std::random_device rd;
	static std::mt19937 gen(rd());
	//X Spawn
	std::uniform_int_distribution<> xRange(0, 1000);
	this->spawnX = xRange(gen);

	//Y Spawn
	this->spawnY = 0;

	//X Target
	this->targetX = xRange(gen);

	//Y Target
	this->targetY = 1200;

	//Rotation speed;
	std::uniform_real_distribution<> rotationRange(1.5f, 3.5f);
	this->rotationSpeed = rotationRange(gen);

	//Rotation angle
	std::uniform_int_distribution<> angle(0, 1);
	this->rotationAngle = (angle(gen) == 1) ? 1 : -1; // Se distr(gen) è 1 restituisce 1, altrimenti restituisce -1

	//Size
	std::uniform_real_distribution<> sizeRange(5.f, 18.f);
	this->size = sizeRange(gen);

	//MoveSpeed
	this->moveSpeed = mapValue(5.f, 18.f, 2.f, 0.2f, this->size);

	//Health
	this->health = mapValue(5.f, 18.f, 1.f, 15.f, this->size);

	//Damage
	this->damage = mapValue(5.f, 18.f, 1.f, 5.f, this->size);
}


void Asteroid::initSprite(sf::Texture* texture, sf::Vector2u windowSize) {
	this->sprite.setTexture(*texture);
	float scale = (static_cast<float>(windowSize.x) / 1024.f) * this->size;
	this->sprite.scale(scale, scale);

	sf::FloatRect limits = this->sprite.getLocalBounds();
	this->sprite.setOrigin(limits.width / 2.0f, limits.height / 2.0f); //Origine al centro
}

void Asteroid::initMovement() {
	this->sprite.setPosition(this->spawnX, this->spawnY);
	float dx = targetX - spawnX;
	float dy = targetY - spawnY;

	float distance = std::sqrt((dx * dx) + (dy * dy));
	this->velocity.x = (dx / distance) * this->moveSpeed;
	this->velocity.y = (dy / distance) * this->moveSpeed;
}

Asteroid::Asteroid(sf::Texture* texture, sf::Vector2u windowSize) {
	this->initVariables();
	this->initSprite(texture, windowSize);
	this->initMovement();
}

Asteroid::~Asteroid() {

}

void Asteroid::update() {
	this->sprite.rotate(this->rotationAngle * rotationSpeed);
	this->sprite.move(this->velocity.x, this->velocity.y);
}