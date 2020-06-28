#ifndef SQUAREMAN_MAZE_HPP
#define SQUAREMAN_MAZE_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Maze : public sf::Drawable {
public:
	Maze();
	// load maze data by using this method
	void loadLevel(const std::string& name);
	
	sf::Vector2i getSquaremanPosition() const;
	std::vector<sf::Vector2i> getGhostPositions() const;
	
	// helpers (inline = faster) 
	inline std::size_t positionToIndex(sf::Vector2i position) const;
	inline sf::Vector2i indexToPosition(std::size_t index) const;
	
private:
	enum cellData {
		Empty,
		Wall,
		Dot, 
		SuperDot,
		Bonus
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Vector2i m_mazeSize;
	std::vector<cellData> m_mazeData;
	
	sf::Vector2i m_squaremanPosition;
	std::vector<sf::Vector2i> m_ghostPositions;
	
	sf::RenderTexture m_renderTexture;
};

#endif // SQUAREMAN_MAZE_HPP
 