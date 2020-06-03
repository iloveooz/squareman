#ifndef SQUAREMAN_SQUAREMAN_HPP
#define SQUAREMAN_SQUAREMAN_HPP

#include "Character.hpp"

class Squareman : public Character {
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite m_visual;
};

#endif // SQUAREMAN_SQUAREMAN_HPP
