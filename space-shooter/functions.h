#ifndef FUNCTIONS_H
#define FUNCTIONS_H

float mapValue(float a, float b, float A, float B, float x);

void vectorScalarProduct(sf::Vector2f* vector, float number);
float getVectorModule(sf::Vector2f vector);
void normalizeVector(sf::Vector2f* vector);

#endif