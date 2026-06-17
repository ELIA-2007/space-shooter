#include "Player.h"
#include "functions.h"

void Player::initVariables() {
	this->health = 10.f;
	this->moveSpeed = 300.f;
	this->damage = 1.f;
	this->shootingCooldownMax = 0.2f;
	this->shootingCooldown = this->shootingCooldownMax;

}


void Player::initSprite(sf::Texture* texture, sf::Vector2u windowSize) {
	this->sprite.setTexture(*texture);

	float scale = (static_cast<float>(windowSize.x) / 1024.f) * 0.1f;
	this->sprite.scale(scale, scale);
}

Player::Player(sf::Texture* texture, sf::Vector2u windowSize) {
	this->initVariables();
	this->initSprite(texture, windowSize);
}

Player::~Player() {

}

const sf::Vector2f& Player::getPos() const {
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const {
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Player::getSize() const {
	return this->sprite.getGlobalBounds().getSize();
}

float Player::getDamage() {
	return this->damage;
}

void Player::move(sf::Vector2f vector, float dt) {
	vectorScalarProduct(&vector, this->moveSpeed * dt);
	this->sprite.move(vector);
}

void Player::setPosition(float x, float y) {
	this->sprite.setPosition(x - (this->getSize().x / 2), y - (this->getSize().y / 2));
}

bool Player::canAttack() {
	if (this->shootingCooldown >= this->shootingCooldownMax) {
		this->shootingCooldown -= this->shootingCooldownMax;
		return true;
	}
	else {
		return false;
	}
}

void Player::getHit(float damage) {
	this->health -= static_cast<int>(damage);
}

float Player::getHealth() {
	return this->health;
}

void Player::updateCooldowns(float dt) {
	if (this->shootingCooldown < this->shootingCooldownMax) {
		this->shootingCooldown += dt;
	}
}

void Player::update(float dt) {
	this->updateCooldowns(dt);
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}
