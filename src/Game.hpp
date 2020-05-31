#ifndef SQUAREMAN_GAME_HPP
#define SQUAREMAN_GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	
	void run();
	void insertCoin();
	void pressButton();

	void moveStick(sf::Vector2i direction);

private:
	sf::RenderWindow m_window;
};

#endif // SQUAREMAN_GAME_HPP
