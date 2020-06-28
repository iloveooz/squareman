#include "include/Maze.hpp"
#include "include/Dot.hpp"

Maze::Maze() : m_mazeSize(0, 0) {
	
}

void Maze::loadLevel(const std::string& name) {
	sf::Image levelData;
	
	if (!levelData.loadFromFile("assets/levels/" + name + ".png")) 
		throw std::runtime_error("Error! Failed to load level(" + name + ")");
	
	// maze size is an image size, getSize returns vector using unsigned integer
	m_mazeSize = sf::Vector2i(levelData.getSize());
	
	if (m_mazeSize.x < 15 && m_mazeSize.y < 15) 
		throw std::runtime_error("The loaded level is too small (min 15 cells large)");
	
	// loading maze data
	for (unsigned int y = 0; y < m_mazeSize.y; y++) {
		for (unsigned int x = 0; x < m_mazeSize.x; x++) {
			sf::Color cellData = levelData.getPixel(x, y);
			
			if (cellData == sf::Color::Black) {
				m_mazeData.push_back(Wall);
			} 
			else if (cellData == sf::Color::White) {
				m_mazeData.push_back(Dot);
			}
			else if (cellData == sf::Color::Green) {
				m_mazeData.push_back(SuperDot);
			}
			else if (cellData == sf::Color::Blue) {
				m_squaremanPosition = sf::Vector2i(x, y); // squareman position is
				m_mazeData.push_back(Empty); // dot in cell already eaten
			}
			else if (cellData == sf::Color::Red) {
				m_ghostPositions.push_back(sf::Vector2i(x, y)); // ghost position is
				m_mazeData.push_back(Empty); // initial position one of the ghosts
			}
			else {
				m_mazeData.push_back(Empty);
			}
		}
	}
	
	m_renderTexture.create(32 * m_mazeSize.x, 32 * m_mazeSize.y);
	m_renderTexture.clear(sf::Color::Black);
	
	// draw something ...
	
	m_renderTexture.display(); 
	
	for (unsigned int i = 0; i < m_mazeData.size(); i++) {
		sf::Vector2i position = indexToPosition(i);
		
		if (m_mazeData[i] == Wall) {
			sf::RectangleShape wall;
			wall.setSize(sf::Vector2f(32, 32));
			wall.setFillColor(sf::Color::Blue);
			wall.setPosition(32 * position.x, 32 * position.y);
	
			m_renderTexture.draw(wall);
		}
	}
}
	
void Maze::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sf::Sprite(m_renderTexture.getTexture()), states);
	
	static sf::CircleShape dot = getDot();
	static sf::CircleShape superDot = getSuperDot();
	
	for (unsigned int i = 0; i < m_mazeData.size(); i++) {
		sf::Vector2i position = indexToPosition(i);
		
		if (m_mazeData[i] == Dot) {
			dot.setPosition(32 * position.x + 16, 32 * position.y + 16); // 16 for center of the cell 
			target.draw(dot, states);
		}
		else if (m_mazeData[i] == SuperDot) {
			superDot.setPosition(32 * position.x + 16, 32 * position.y + 16);
			target.draw(dot, states);
		}
	}
}

sf::Vector2i Maze::getSquaremanPosition() const {
	return m_squaremanPosition;
}

std::vector<sf::Vector2i> Maze::getGhostPositions() const {
	return m_ghostPositions;
}

std::size_t Maze::positionToIndex(sf::Vector2i position) const {
	return position.y * m_mazeSize.x + position.x;
}

sf::Vector2i Maze::indexToPosition(std::size_t index) const {
	sf::Vector2i position;
	
	position.x = index % m_mazeSize.x;
	position.y = index / m_mazeSize.x;
	
	return position;
}