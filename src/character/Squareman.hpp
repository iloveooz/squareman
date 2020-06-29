#ifndef SQUAREMAN_SQUAREMAN_HPP
#define SQUAREMAN_SQUAREMAN_HPP

#include "Character.hpp"
#include "../animator/Animator.hpp"

class Squareman : public Character {
public: 
	Squareman(sf::Texture& texture);

	void die();
	
	bool isDying() const;
	bool isDead() const;
	
	void update(sf::Time delta);
	
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	bool m_isDying;
	bool m_isDead;
	
	sf::Sprite m_visual;
	
	Animator m_runAnimator;
	Animator m_dieAnimator;
};

#endif // SQUAREMAN_SQUAREMAN_HPP
