#pragma once

#include "SFML/Graphics.hpp"

class Planet {

public:

	sf::CircleShape m_shape;
	float m_radius;
	sf::Color m_color;
	float m_mass;
	bool m_isPassive;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;

	Planet(float radius, sf::Color color = sf::Color(255, 255, 255), float mass = 1.0f,bool isPassive = false , sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f speed = sf::Vector2f(0.0f, 0.0f)) {
		m_radius = radius;
		m_color = color;
		m_mass = mass;
		m_isPassive = isPassive;
		m_position = position;
		m_speed = speed;
		m_shape = sf::CircleShape(m_radius);
		m_shape.setOrigin(m_radius, m_radius);
		m_shape.setFillColor(m_color);
		m_shape.setPosition(m_position);
	}

	void applyForce(sf::Vector2f force, float multiplier, float deltaTime) {
		//Acceleration = Force/Mass
		sf::Vector2f acceleration = sf::Vector2f(force / m_mass);
		//Now increase speed by the amount of acceleration
		
		sf::Vector2f newSpeed;
		newSpeed.x = m_speed.x + (acceleration.x * multiplier * deltaTime);
		newSpeed.y = m_speed.y + (acceleration.y *  multiplier* deltaTime);

		this->m_speed = newSpeed;
	}

	void updatePosition(float deltaTime) {
		if (!m_isPassive) {
			this->m_position = m_position + (m_speed * deltaTime);
			m_shape.setPosition(m_position);
		}
	}
};