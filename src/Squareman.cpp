#include "include/Squareman.hpp"

Squareman::Squareman(sf::Texture& texture) : m_visual(texture), m_isDying(false), m_isDead(false) {
	setOrigin(20, 20);	
	
	// set animation data, we can take this information from the sprite sheet
	m_runAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
	m_runAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
	
	m_dieAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(0, 112, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(40, 112, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(80, 112, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(120, 112, 40, 40));
	m_dieAnimator.addFrame(sf::IntRect(160, 112, 40, 40));
	
	// run animation using play, четверти секунды хватит для отображения именно двух кадров, and we loop it
	m_runAnimator.play(sf::seconds(0.25), true);
}

void Squareman::die() {
	if (!m_isDying) {
		m_dieAnimator.play(sf::seconds(1), false);
		m_isDying = true;
	}
}

bool Squareman::isDying() const {
	return m_isDying;
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

void Squareman::update(sf::Time delta) {
	if (!m_isDead && !m_isDying) {
		m_runAnimator.update(delta);
		m_runAnimator.animate(m_visual);
	} else {
		m_dieAnimator.update(delta);
		m_dieAnimator.animate(m_visual);
		
		if (!m_dieAnimator.isPlaying()) { // squareman is definitly dead
			m_isDying = false;
			m_isDead = true;
		}
	}
}
