#include "Ghost.hpp"

Ghost::Ghost(sf::Texture& texture, Squareman* squareman) : 
m_visual(texture), 
m_isWeak(false), 
m_weaknessDuration(sf::Time::Zero),
m_squareman(squareman) {
	setOrigin(20, 20);
	
	// set animtaion data
	m_strongAnimator.addFrame(sf::IntRect(40, 32, 40, 40));
	// m_strongAnimator.addFrame(sf::IntRect(80, 32, 40, 40));
	
	m_weakAnimator.addFrame(sf::IntRect(40, 72, 40, 40));
	// m_weakAnimator.addFrame(sf::IntRect(80, 72, 40, 40));
	
	m_strongAnimator.play(sf::seconds(0.25), true);
	m_weakAnimator.play(sf::seconds(1), true);
}

void Ghost::setWeak(sf::Time duration) {
	m_isWeak = true;
	m_weaknessDuration = duration;
}

bool Ghost::isWeak() const {
	return m_isWeak;
}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(m_visual, states);
}

void Ghost::update(sf::Time delta) {
	if (m_isWeak) {
		m_weaknessDuration -= delta;
		
		// when weakness duration expires ghost returns to the strong state
		if (m_weaknessDuration <= sf::Time::Zero) {
			m_isWeak = false;
			m_strongAnimator.play(sf::seconds(0.25), true);
		}
	}
	
	if (!m_isWeak) {
		m_strongAnimator.update(delta);
		m_strongAnimator.animate(m_visual);
	} else {
		m_weakAnimator.update(delta);
		m_weakAnimator.animate(m_visual);
	}
	
	Character::update(delta);
}

void Ghost::changeDirection() {
	static sf::Vector2i directions[4] = {
		sf::Vector2i(1, 0),
		sf::Vector2i(0, 1),
		sf::Vector2i(-1, 0),
		sf::Vector2i(0, -1)
	};
	
	std::map<float, sf::Vector2i> directionProb;
	
	sf::Vector2f distance = m_squareman->getPosition() - getPosition();
	
	float targetAngle = std::atan2(distance.x, distance.y) * (180.0 / 3.14159);
	
	for (auto direction : directions) {
		float directionAngle = std::atan2(direction.x, direction.y) * (180.0 / 3.14159);
		
		float diff = 180 - std::abs(std::abs(directionAngle - targetAngle) - 180);
		
		directionProb[diff] = direction;
	}
	
	Character::setDirection(directionProb.begin()->second);
	
	auto iterator = directionProb.begin();
	
	do {
		setDirection(iterator->second);
		iterator++;
	} 
	while (!willMove());
}
