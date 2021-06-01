#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

float getDistance(sf::Vector2f point1, sf::Vector2f point2);

sf::Vector2f getNormlizedVector(sf::Vector2f srcPoint, sf::Vector2f destPoint);

float getVectorMagnitude(sf::Vector2f vector);

float getVectorAngle(sf::Vector2f vector);