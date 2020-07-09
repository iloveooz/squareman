#ifndef SQUAREMAN_MAZE_HPP
#define SQUAREMAN_MAZE_HPP

#include <vector>
#include <cmath>
#include <cassert>

#include <SFML/Graphics.hpp>

class Maze : public sf::Drawable {
public:
	Maze(sf::Texture& texture);
	// load maze data by using this method
	void loadLevel(const std::string& name);
	
	sf::Vector2i getSquaremanPosition() const;
	std::vector<sf::Vector2i> getGhostPositions() const;
	
	// helpers (inline = faster) 
	inline std::size_t positionToIndex(sf::Vector2i position) const;
	inline sf::Vector2i indexToPosition(std::size_t index) const;
	
	// sf::Vector2i squaremanPosition = m_maze.getSquaremanPosition();
	sf::Vector2i mapPixelToCell(sf::Vector2f pixel) const;
	sf::Vector2f mapCellToPixel(sf::Vector2i cell) const;
	
	bool isWall(sf::Vector2i position) const;
	bool isSuperDot(sf::Vector2i position) const;
	bool isBonus(sf::Vector2i position) const;
	
	void pickObject(sf::Vector2i position);	
	
	sf::Vector2i getSize() const;
	
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
	sf::Texture& m_texture;
};

#endif // SQUAREMAN_MAZE_HPP
 
