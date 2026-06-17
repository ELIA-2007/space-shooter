#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "functions.h"

float mapValue(float a, float b, float A, float B, float x) {
	if (a != b) return A + (B - A) * ((x - a) / (b - a)); else return 0;
}

void vectorScalarProduct(sf::Vector2f* vector, float number) {
	vector->x *= number;
	vector->y *= number;
}

float getVectorModule(sf::Vector2f vector) {
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

void normalizeVector(sf::Vector2f* vector) {
	if (vector->x == 0 or vector->y == 0) return;
	vectorScalarProduct(vector, 1 / getVectorModule(*vector));
}

void drawHitbox(sf::FloatRect bounds, sf::Color color, sf::RenderTarget& target) {
	sf::RectangleShape hitbox;
	hitbox.setPosition(bounds.left, bounds.top);
	hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));

	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(color);
	hitbox.setOutlineThickness(2.0f);

	target.draw(hitbox);
}

void text(const sf::Font& font, const sf::String& textString, unsigned short size, sf::Color color, float x, float y, sf::RenderTarget& target) {
	sf::Text text;

	text.setFont(font);
	text.setString(textString);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(x, y);

	target.draw(text);
}
