#ifndef SQUAREMAN_GHOST_HPP
#define SQUAREMAN_GHOST_HPP

#include "Character.hpp"
#include "Squareman.hpp"

class Ghost : public Character {
public:
	Ghost(sf::Texture& texture);

	enum State {
		Strong,
		Weak
	};

	void setWeak(sf::Time duration);
	bool isWeak() const;
		
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	bool m_isWeak;
	
	sf::Time m_weaknessDuration;
	sf::Sprite m_visual;
};


#endif // SQUAREMAN_GHOST_HPP
