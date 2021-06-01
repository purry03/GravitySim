#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Text {

public:
	sf::Font m_font;
	sf::Text m_text;
	std::string m_content;
	int m_fontSize;
	sf::Color m_fontColor;
	int m_anchor;
	sf::Vector2f m_position;

	Text(int textSize = 14,std::string string="",sf::Vector2f position = sf::Vector2f(0,0),sf::Color fontColor = sf::Color(255,255,255),std::string fontFile = "Assets/Consolas.ttf") {
		if (!m_font.loadFromFile(fontFile)) {
			std::cout << "Error loading " << fontFile << std::endl;
		}
		else {
			m_text.setFont(m_font);
			m_fontSize = textSize;
			m_text.setCharacterSize(m_fontSize);
			m_content = string;
			m_text.setString(m_content);
			m_fontColor = fontColor;
			m_text.setFillColor(m_fontColor);
			m_anchor = 1;
			m_position = position;
			m_text.setPosition(m_position);
		}
	}

	void setOrigin(int anchor = 0) {
		m_anchor = anchor;
		float x = 0.0f, y = 0.0f;
		switch (m_anchor) {
		case 1: {
			//top left
			//this is the origin by default
		}break;
		case 2: {
			//top right
			x = m_text.getGlobalBounds().width;
		}break;
		case 3: {
			//bottom right
			x = m_text.getGlobalBounds().width;
			y = m_text.getGlobalBounds().height;
		}break;
		case 4: {
			//bottom left
			y = m_text.getGlobalBounds().height;
		}break;
		case 5: {
			//center
			x = m_text.getGlobalBounds().width/2;
			y = m_text.getGlobalBounds().height/2;
		}
		default: {
			//center if no anchor specified
			x = m_text.getGlobalBounds().width / 2;
			y = m_text.getGlobalBounds().height / 2;
		}break;
		}
		m_text.setOrigin(x, y);
	}

	void recalculateOrigin() {
		setOrigin(m_anchor);
	}

	void setText(std::string content = "") {
		m_content = content;
		m_text.setString(m_content);
	}

	void setPosition(sf::Vector2f position = sf::Vector2f(0,0)) {
		m_position = position;
		m_text.setPosition(m_position);
	}
};