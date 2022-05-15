#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f acc;
	sf::Vector2f speed{ 0.f, 0.f };
	sf::Vector2f pos;
	bool isJump = false;
public:
	Player();
	void update();
	void draw(sf::RenderWindow& window) { window.draw(sprite); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	sf::Vector2f getAcc() { return acc; }
	sf::Vector2f getSpeed() { return speed; }
	sf::Vector2f getPosition() { return pos; }
	void setPosition(sf::Vector2f fpos) { pos = fpos; }
	void setPosition(float x, float y) { pos.x = x; pos.y = y; }
	void setVerticalPosition(float y) { pos.y = y; }
	void resetVerticalSpeed() { speed.y = 0; }
	void resetIsJump() { isJump = false; }
};
