#include "Squareman.hpp"

Squareman::Squareman(sf::Texture& texture) : m_visual(texture), m_isDead(false) {
	setOrigin(20, 20);	
}

void Squareman::die() {
	m_isDead = true;
}

bool Squareman::isDead() const {
	return m_isDead;
}

void Squareman::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	if (!m_isDead) {
		target.draw(m_visual, states);
	}
}
