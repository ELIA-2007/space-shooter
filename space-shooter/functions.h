#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

float mapValue(float a, float b, float A, float B, float x);

void vectorScalarProduct(sf::Vector2f* vector, float number);
float getVectorModule(sf::Vector2f vector);
void normalizeVector(sf::Vector2f* vector);

void drawHitbox(sf::FloatRect bounds, sf::Color color, sf::RenderTarget& target);

void text(const sf::Font& font, const sf::String& textString, unsigned short size, sf::Color color, float x, float y, sf::RenderTarget& target);

#endif