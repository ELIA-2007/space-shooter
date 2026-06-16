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