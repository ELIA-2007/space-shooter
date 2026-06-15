#include "Player.h"

void Player::initVariables() {
	this->moveSpeed = 2;
	this->shootingCooldownMax = 40;
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

const sf::Vector2f& Player::getSize() const {
	return this->sprite.getGlobalBounds().getSize();
}

void Player::move(const float dirX, const float dirY) {
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

void Player::setPosition(float x, float y) {
	this->sprite.setPosition(x - (this->getSize().x / 2), y - (this->getSize().y / 2));
}

bool Player::canAttack() {
	if (this->shootingCooldown == this->shootingCooldownMax) {
		this->shootingCooldown = 0;
		return true;
	}
	else {
		return false;
	}
}

void Player::updateCooldowns() {
	if (this->shootingCooldown < this->shootingCooldownMax) {
		this->shootingCooldown += 1;
	}
}

void Player::update() {
	this->updateCooldowns();
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}
