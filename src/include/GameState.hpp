#ifndef SQUAREMAN_GAMESTATE_HPP
#define SQUAREMAN_GAMESTATE_HPP

#include <SFML/Graphics.hpp>

#include "Maze.hpp"
#include "Squareman.hpp"
#include "Ghost.hpp"

class Game;

class GameState {
public:
	enum State {
		NoCoin, 
		GetReady,
		Playing,
		Lost, 
		Won,
		Count
	};
	
	GameState(Game* game);
	Game* getGame() const;
	
	// three fundamental steps
	virtual void insertCoin() = 0;
	virtual void pressButton() = 0;
	virtual void moveStick(sf::Vector2i direction) = 0;
	
	virtual void update(sf::Time delta) = 0; // update game states
	virtual void draw(sf::RenderWindow& window) = 0; // drawing new content
	
private:
	Game* m_game;
};

class NoCoinState : public GameState {
public:
	NoCoinState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
private:
	sf::Text m_text;
	sf::Sprite m_sprite;
	
	bool m_displayText;
};

class GetReadyState : public GameState {
public:
	GetReadyState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
private:
	sf::Text m_text;
};

class PlayingState : public GameState {
public:
	PlayingState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);

private:
	Squareman m_squareman;
	Ghost m_ghost;
	Maze m_maze;
};

class LostState : public GameState {
public:
	LostState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
private:
	sf::Text m_text;
	sf::Time m_countDown;
	sf::Text m_countDownText;
};

class WonState : public GameState {
public:
	WonState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
private:
	sf::Text m_text;
};

#endif // SQUAREMAN_GAMESTATE_HPP
