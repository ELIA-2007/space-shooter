#include "Enemy.h"

float Enemy::getHealth() {
    return this->health;
}

void Enemy::getHit(float damage) {
    this->health -= damage;
}

const sf::FloatRect Enemy::getBounds() const {
    return this->sprite.getGlobalBounds();
}

void Enemy::update() {
}

void Enemy::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}