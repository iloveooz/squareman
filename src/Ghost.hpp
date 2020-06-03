#ifndef SQUAREMAN_GHOST_HPP
#define SQUAREMAN_GHOST_HPP

#include "Character.hpp"

class Ghost : public Character {
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // SQUAREMAN_GHOST_HPP
