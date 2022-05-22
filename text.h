#pragma once
#include "SFML/Graphics.hpp"
class TextObject {
private:
	sf::Font font;
	sf::Text text;
public:
	TextObject(std::string file_name, int size, float x, float y,
		sf::Color color) {
		font.loadFromFile(file_name);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(x, y);
	}
	void update(std::string str) { text.setString(str); }
	void update(size_t x) { text.setString(std::to_string(x)); }
	void draw(sf::RenderWindow& window) { window.draw(text); }
};