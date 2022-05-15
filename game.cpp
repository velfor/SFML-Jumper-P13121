#include "game.h"
#include "settings.h"
Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
	window.setFramerateLimit(FPS);
	size_t desktop_width = sf::VideoMode::getDesktopMode().width;
	window.setPosition(sf::Vector2i((desktop_width - WINDOW_WIDTH)/2, 0));
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
}
void Game::draw() {
	window.clear();
	player.draw(window);
	window.display();
}
void Game::check_collisions() {

}