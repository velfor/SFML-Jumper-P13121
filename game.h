#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "platform.h"
#include <list>

class Game {
public:
	enum class GameState {INTRO, PLAY, GAME_OVER};
	Game();
	void play();
private:
	sf::RenderWindow window;
	GameState game_state = GameState::PLAY;
	Player player;
	std::list<Platform*> platforms;
	Platform* p1;
	Platform* p2;
	Platform* p3;
	void check_events();
	void update();
	void draw();
	void check_collisions();
};