#ifndef SQUAREMAN_SQUAREMAN_HPP
#define SQUAREMAN_SQUAREMAN_HPP

#include "Character.hpp"

class Squareman : public Character {
public: 
	Squareman(sf::Texture& texture);

	void die();
	bool isDead() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	bool m_isDead;
	sf::Sprite m_visual;
};

#endif // SQUAREMAN_SQUAREMAN_HPP
