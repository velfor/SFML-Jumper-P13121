#include "player.h"
#include "settings.h"
Player::Player() {
	texture.loadFromFile("images/Players/bunny1_ready.png");
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setScale(0.5f, 0.5f);
	pos = sf::Vector2f( WINDOW_WIDTH / 2 - getHitBox().width / 2,
			WINDOW_HEIGHT / 2 - getHitBox().height / 2 );
	sprite.setPosition(pos);
}
void Player::update() {
	acc = sf::Vector2f(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		acc.x = -0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		acc.x = 0.5f;
	}
	speed += acc;
	pos += speed + sf::Vector2f(acc.x * 0.5, acc.y * 0.5);
	if (pos.x < 0 - getHitBox().width / 2) {
		pos.x = WINDOW_WIDTH - getHitBox().width / 2;
	}
	else if (pos.x > WINDOW_WIDTH - getHitBox().width / 2) {
		pos.x = 0 - getHitBox().width / 2;
	}
	sprite.setPosition(pos);
	
}