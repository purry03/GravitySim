#include <cmath>
#include <SFML/System/Vector2.hpp>

float getDistance(sf::Vector2f point1, sf::Vector2f point2) {
	float distance = sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
	return distance;
}


float getVectorMagnitude(sf::Vector2f vector) {
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

sf::Vector2f getNormlizedVector(sf::Vector2f srcPoint, sf::Vector2f destPoint) {
	sf::Vector2f direction = sf::Vector2f(srcPoint - destPoint);

	float mag = getVectorMagnitude(direction);
	sf::Vector2f normalizedVector = direction / mag;

	return normalizedVector;
}


float getVectorAngle(sf::Vector2f vector) {
	return atan2(vector.y, vector.x)* 57.2958;
}