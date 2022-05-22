#include "game.h"

Game::Game() : 
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
	game_over_screen(GAME_OVER_IMAGE_FILENAME),
	score_text(IMAGES_FOLDER + "kenvector_future.ttf", 48, 20,20, sf::Color::White)
{
	//в самом низу экрана шириной на весь экран
	Platform* p1 = new Platform(0, WINDOW_HEIGHT - 55.f, 
								WINDOW_WIDTH, 55.f);
	platform_sprites.push_back(p1);
	//выше 1-ой и на 1/2 экрана шириной
	Platform* p2 = new Platform(WINDOW_WIDTH/4, 
		WINDOW_HEIGHT*3/4 , WINDOW_WIDTH/4, 55.f);
	platform_sprites.push_back(p2);
	Platform* p3 = new Platform(WINDOW_WIDTH *2 / 3,
		WINDOW_HEIGHT / 2, WINDOW_WIDTH / 4, 55.f);
	platform_sprites.push_back(p3);
	window.setVerticalSyncEnabled(true);
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		// Пользователь нажал на «крестик» и хочет закрыть окно?
		if (event.type == sf::Event::Closed)
			// тогда закрываем его
			window.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
			//двигаем игрока на 1 пиксель вниз
			player.setPositionIncY();
			//если есть пересечение с платформой
			for (auto iter = platform_sprites.begin(); iter != platform_sprites.end(); iter++) {
				if (player.getHitBox().intersects((*iter)->getHitBox())) {
					//то прыжок
					player.jump();
				}
			}
			//двигаем игрока на 1 пиксель вверх
			player.setPositionIncY();
		}
	}
}
void Game::update() {
	switch (game_state) {
	case GameState::INTRO:
		break;
	case GameState::PLAY:
	{
		player.update();
		//смерть игрока
		if (player.getPosition().y > WINDOW_HEIGHT) {
			game_state = GameState::GAME_OVER;
		}
		for (auto iter = platform_sprites.begin();
			iter != platform_sprites.end(); iter++) {
			(*iter)->update();
		}
		//движение всех платформ вниз если игрок допрыгал до верха
		if (player.getPosition().y <= WINDOW_HEIGHT / 3.f) {
			for (auto iter = platform_sprites.begin();
				iter != platform_sprites.end(); iter++) {
				if (player.getPosition().y > 0) {
					(*iter)->setPosition((*iter)->getPosition().x,
						(*iter)->getPosition().y + 15.f);
				}
				else
				{
					(*iter)->setPosition((*iter)->getPosition().x,
						(*iter)->getPosition().y + 45.f);
				}
				//платформы, которые опустились ниже 5/4 высоты экрана 
				//помечаем на удаление
				if ((*iter)->getPosition().y > 5 * WINDOW_HEIGHT / 4) {
					(*iter)->setDel();
					score++;
				}
			}
		}
		//удаляем ненужные платформы
		platform_sprites.remove_if([](Platform* p) {
			return p->getDel(); });
		//спавн глвых платформ
		while (platform_sprites.size() < PLATFORMS_QTY) {
			int len = rand() % 151 + 100;
			int new_x = rand() % (static_cast<int>(
				WINDOW_WIDTH - len));
			int new_y = rand() % static_cast<int>(player.getPosition().y) - 250;
			Platform* p = new Platform(new_x, new_y, len, 55.f);
			platform_sprites.push_back(p);
		}
		//обновляем счет
		score_text.update(score);
		break;
	}
	case GameState::GAME_OVER:
		break;
	}
}
void Game::draw() {
	window.clear(BACKGROUND_COLOR);
	switch (game_state) {
	case GameState::INTRO:
		break;
	case GameState::PLAY:
		player.draw(window);
		for (auto iter = platform_sprites.begin();
			iter != platform_sprites.end(); iter++) {
			(*iter)->draw(window);
		}
		score_text.draw(window);
		break;
	case GameState::GAME_OVER:
		game_over_screen.draw(window);
		break;
	}
	window.display();
}
void Game::check_collisions() {
	if (player.getSpeed().y > 0) {
		for (auto iter = platform_sprites.begin();
			iter != platform_sprites.end(); iter++) {
			if (player.getHitBox().intersects((*iter)->getHitBox())) {
					player.resetSpeed();
					sf::Vector2f platform_pos = (*iter)->getPosition();
					sf::Vector2f player_new_pos =
						sf::Vector2f(player.getPosition().x,
							platform_pos.y - player.getHitBox().height);
					player.setPosition(player_new_pos);
				
			}
		}
	}
}

