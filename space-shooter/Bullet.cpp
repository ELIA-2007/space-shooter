#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2u windowSize, float posX, float posY, float dirX, float dirY, float move_speed) {
	this->sprite.setPosition(posX - this->sprite.getGlobalBounds().getSize().x, posY - this->sprite.getGlobalBounds().getSize().y);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->moveSpeed = move_speed;
	this->initSprite(texture, windowSize);
}

Bullet::~Bullet() {

}

const sf::FloatRect Bullet::getBounds() const {
	return this->sprite.getGlobalBounds();
}

void Bullet::initSprite(sf::Texture* texture, sf::Vector2u windowSize) {
	this->sprite.setTexture(*texture);
	float scale = (static_cast<float>(windowSize.x) / 1024.f) * 2.8f;
	this->sprite.scale(scale, scale);

	sf::FloatRect limits = this->sprite.getLocalBounds();
	this->sprite.setOrigin(limits.width / 2.0f, limits.height / 2.0f); //Origine al centro
}

void Bullet::update() {
	//Move
	this->sprite.move(this->moveSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}