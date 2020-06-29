#include "Animator.hpp"

// animator is not palying anything when constructed
Animator::Animator() : 
m_currentFrame(0), 
m_isPlaying(false), 
m_duration(sf::Time::Zero), 
m_loop(false) {}

void Animator::addFrame(sf::IntRect frame) {
	m_frames.push_back(frame);
}

// we have to play the animation 
void Animator::play(sf::Time duration, bool loop) {
	m_isPlaying = true;
	m_duration = duration;
	m_loop = loop;
}

bool Animator::isPlaying() const {
	return m_isPlaying;
}

void Animator::update(sf::Time delta) {
	if (!isPlaying())
		return;
	
	// time buffer increments by elapsed time
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	// compute a duration of one frame 
	// animation duration divided by the number of frames to play 
	sf::Time frameDuration = m_duration / static_cast<float>(m_frames.size());
	
	// if elapsed time is greater then one frame duration 
	while (timeBuffer > frameDuration) {
		m_currentFrame++; // current frame index is increments, and we decrement the time buffer by the frame duration
		
		if (m_currentFrame == m_frames.size()) {
			if (!m_loop) {
				m_isPlaying = false;
			}
			m_currentFrame = 0;
		}
		timeBuffer -= frameDuration;
	}
	
}

// update the texture rectangle with the sprite
void Animator::animate(sf::Sprite& sprite) {
	sprite.setTextureRect(m_frames[m_currentFrame]);
}
