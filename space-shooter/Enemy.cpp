#include "Enemy.h"

float Enemy::getHealth() {
    return this->health;
}

float Enemy::getDamage() {
    return this->damage;
}

void Enemy::getHit(float damage) {
    this->health -= damage;
}

const sf::FloatRect Enemy::getBounds() const {
    return this->sprite.getGlobalBounds();
}

void Enemy::update(float dt) {
}

void Enemy::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}