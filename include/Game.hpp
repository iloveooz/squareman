#ifndef SQUAREMAN_GAME_HPP
#define SQUAREMAN_GAME_HPP

#include <array>

#include <SFML/Graphics.hpp>
#include "../include/GameState.hpp"

class Game {
public:
	Game();
	~Game();
	
	void run();
	
	sf::Font& getFont();
	sf::Texture& getLogo();
	sf::Texture& getTexture();
	
	void changeGameState(GameState::State gameState);

private:
	sf::RenderWindow m_window;
	GameState* m_currentState;
	std::array <GameState*, GameState::Count> m_gameStates;
	
	sf::Font m_font;
	sf::Texture m_logo;
	sf::Texture m_texture;
};

#endif // SQUAREMAN_GAME_HPP
