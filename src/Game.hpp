#ifndef SQUAREMAN_GAME_HPP
#define SQUAREMAN_GAME_HPP

#include <array>

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class Game {
public:
	Game();
	~Game();
	
	void run();
	
	void changeGameState(GameState::State gameState);

private:
	sf::RenderWindow m_window;
	GameState* m_currentState;
	std::array <GameState*, GameState::Count> m_gameStates;
};

#endif // SQUAREMAN_GAME_HPP
