#include "game.h"
#include "settings.h"
Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
	p1{ new Platform(0, WINDOW_HEIGHT - 50.f, WINDOW_WIDTH, 50.f) },
	p2{ new Platform(0,WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH / 3, 50.f) },
	p3{ new Platform(WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT / 3, WINDOW_WIDTH / 3, 50.f) }
{
	window.setFramerateLimit(FPS);
	size_t desktop_width = sf::VideoMode::getDesktopMode().width;
	window.setPosition(sf::Vector2i((desktop_width - WINDOW_WIDTH)/2, 0));
	platforms.push_back(p1);
	platforms.push_back(p2);
	platforms.push_back(p3);
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void  Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
	}
}
void Game::update() {
	player.update();
	for (auto it = platforms.begin(); it != platforms.end(); it++) {
		(*it)->update();
	}
}
void Game::draw() {
	window.clear();
	player.draw(window);
	for (auto it = platforms.begin(); it != platforms.end(); it++) {
		(*it)->draw(window);
	}
	window.display();
}
void Game::check_collisions() {
	if (player.getSpeed().y > 0) {
		for (auto it = platforms.begin(); it != platforms.end(); it++) {
			if (player.getHitBox().intersects((*it)->getHitBox())) {
				player.resetVerticalSpeed();
				player.setVerticalPosition((*it)->getPosition().y - player.getHitBox().height);
				player.resetIsJump();
			}
		}
	}
}