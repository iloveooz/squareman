#include "GameState.hpp"
#include "Game.hpp"
#include "../maze/Maze.hpp"

GameState::GameState(Game* game) : 
m_game(game) {
	
}

Game* GameState::getGame() const {
	return m_game;
}

template <typename T>
void centerOrigin(T& drawable) {
	sf::FloatRect bound = drawable.getLocalBounds();
	drawable.setOrigin(bound.width / 2, bound.height / 2);
}

// ----- NoCoinState
NoCoinState::NoCoinState(Game* game) : GameState(game) { 
	m_sprite.setTexture(game->getLogo());
	m_sprite.setPosition(20, 50);
	
	m_text.setFont(game->getFont());
	m_text.setString("Insert Coin");
	
	centerOrigin(m_text);
	m_text.setPosition(240, 150);
	
	m_displayText = true;
	
}

void NoCoinState::insertCoin() { 
	getGame()->changeGameState(GameState::GetReady);
}

void NoCoinState::pressButton() { }

void NoCoinState::moveStick(sf::Vector2i direction) { }

void NoCoinState::update(sf::Time delta) { 
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	while (timeBuffer >= sf::seconds(0.5)) {
		m_displayText = !m_displayText;
		timeBuffer -= sf::seconds(1);
	}	
}

void NoCoinState::draw(sf::RenderWindow& window) { 
	window.draw(m_sprite);
	
	if (m_displayText)
		window.draw(m_text);
}

// ----- GetReadyState
GetReadyState::GetReadyState(Game* game, GameState* playingState) : 
GameState(game),
m_playingState(playingState) { 
	m_text.setFont(game->getFont());
	m_text.setString("Press Start when you're ready...");
	m_text.setCharacterSize(14);
	
	centerOrigin(m_text);
	m_text.setPosition(240, 240);
}

void GetReadyState::insertCoin() { }

void GetReadyState::pressButton() { 
	getGame()->changeGameState(GameState::Playing);
}

void GetReadyState::moveStick(sf::Vector2i direction) { 
	if (direction.x == -1) 
		getGame()->changeGameState(GameState::Lost);
	else if (direction.x == 1)
		getGame()->changeGameState(GameState::Won);
}

void GetReadyState::update(sf::Time delta) {
	m_playingState->update(delta);
}

void GetReadyState::draw(sf::RenderWindow& window) { 
	m_playingState->draw(window);
	window.draw(m_text);
}


// ----- PlayingState
PlayingState::PlayingState(Game* game) : 
GameState(game), 
m_maze(game->getTexture()),
m_squareman(nullptr),
m_level(0),
m_liveCount(3),
m_score(0) {
	m_squareman = new Squareman(game->getTexture());
	m_squareman->setMaze(&m_maze);
	m_squareman->setPosition(m_maze.mapCellToPixel(m_maze.getSquaremanPosition()));
	
	resetToZero();
	
	m_camera.setSize(sf::Vector2f(480, 480));
	m_scene.create(480, 480);
	
	m_scoreText.setFont(game->getFont());
	m_scoreText.setCharacterSize(10);
	m_scoreText.setPosition(10, 480);
	// m_scoreText.setString("0 points");
	
	m_levelText.setFont(game->getFont());
	m_levelText.setCharacterSize(10);
	m_levelText.setPosition(160, 480);
	// m_levelText.setString("level x-y");
	
	m_remainingDotsText.setFont(game->getFont());
	m_remainingDotsText.setCharacterSize(10);
	m_remainingDotsText.setPosition(280, 480);
	// m_remainingDotsText.setString("0 dots");
	
	for (auto& liveSprite : m_liveSprite) {
		liveSprite.setTexture(game->getTexture());
		liveSprite.setTextureRect(sf::IntRect(122, 0, 20, 20));
	}
	
	m_liveSprite[0].setPosition(sf::Vector2f(415, 480));
	m_liveSprite[1].setPosition(sf::Vector2f(435, 480));
	m_liveSprite[2].setPosition(sf::Vector2f(455, 480));
}

PlayingState::~PlayingState() {
	delete m_squareman;
	
	for (Ghost* ghost : m_ghosts)
		delete ghost;
}

void PlayingState::loadNextLevel() {
	m_maze.loadLevel("large-level-debug");
	
	m_level++;
	
	int mapLevel = m_level % 3;
	int speedLevel = std::floor(m_level / 3);
	
	if (mapLevel == 0) 
		m_maze.loadLevel("small");
	else if (mapLevel == 1)
		m_maze.loadLevel("medium");
	else if (mapLevel == 2)
		m_maze.loadLevel("large");
		
	// destroy previous characters
	for (Ghost* ghost : m_ghosts)
		delete ghost;
	m_ghosts.clear();
	
	// create new characters
	for (auto ghostPosition : m_maze.getGhostPositions()) {
		Ghost* ghost = new Ghost(getGame()->getTexture(), m_squareman);
		ghost->setMaze(&m_maze);
		ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));
		m_ghosts.push_back(ghost);
	}
	
	// change speed according to the new level
	float speed = 100 + (speedLevel * 50);
	
	m_squareman->setSpeed(speed + 25);
	
	for (auto& ghost : m_ghosts)
		ghost->setSpeed(speed);
	
	moveCharactersToInitialPosition();
	
	// updating level text
	m_levelText.setString("level " + std::to_string(speedLevel) + " - " + std::to_string(mapLevel + 1));
}

void PlayingState::moveCharactersToInitialPosition() {
	m_squareman->setPosition(m_maze.mapCellToPixel(m_maze.getSquaremanPosition()));
	
	auto ghostPositions = m_maze.getGhostPositions();
	
	for (unsigned int i = 0; i < m_ghosts.size(); i++) {
		m_ghosts[i]->setPosition(m_maze.mapCellToPixel(ghostPositions[i]));
	}
	updateCameraPosition();
}

void PlayingState::updateCameraPosition() {
	m_camera.setCenter(m_squareman->getPosition());
	
	if (m_camera.getCenter().x < 240) 
		m_camera.setCenter(240, m_camera.getCenter().y);
	
	if (m_camera.getCenter().y < 240) 
		m_camera.setCenter(m_camera.getCenter().x, 240);
		
	if (m_camera.getCenter().x > m_maze.getSize().x * 32 - 240)
		m_camera.setCenter(m_maze.getSize().x * 32 - 240, m_camera.getCenter().y);
		
	if (m_camera.getCenter().y > m_maze.getSize().y * 32 - 240)
		m_camera.setCenter(m_camera.getCenter().x, m_maze.getSize().y * 32 - 240);
}

void PlayingState::insertCoin() { 
	m_squareman->die();
}

void PlayingState::pressButton() { 
	// m_ghost.setWeak(sf::seconds(1));
}

void PlayingState::moveStick(sf::Vector2i direction) {
	m_squareman->setDirection(direction);
}

void PlayingState::resetToZero() {
	resetLiveCount();
	m_level = 0;
	resetCurrentLevel();
	m_score = 0;
}

void PlayingState::resetCurrentLevel() {
	m_level--;
	loadNextLevel();
}

void PlayingState::resetLiveCount() {
	m_liveCount = 3;
}

void PlayingState::update(sf::Time delta) { 
	m_squareman->update(delta);
	
	for (Ghost* ghost : m_ghosts)
		ghost->update(delta);
		
	sf::Vector2f pixelPosition = m_squareman->getPosition();
	sf::Vector2f offset(std::fmod(pixelPosition.x, 32), fmod(pixelPosition.y, 32));
	
	offset -= sf::Vector2f(16, 16);
	
	if (offset.x <= 2 && offset.x >= -2 && offset.y <= 2 && offset.y >= -2) {
		sf::Vector2i cellPosition = m_maze.mapPixelToCell(pixelPosition);
		
		if (m_maze.isDot(cellPosition)) {
			m_score += 5;
		}
		else if (m_maze.isSuperDot(cellPosition)) {
			for (Ghost* ghost : m_ghosts) {
				ghost->setWeak(sf::seconds(5));
				m_score += 25;
			}
		}
		else if (m_maze.isBonus(cellPosition)) {
			m_score += 500;
		}
		
		m_maze.pickObject(cellPosition);
	}
	
	for (Ghost* ghost : m_ghosts) {
		if (ghost->getCollisionBox().intersects(m_squareman->getCollisionBox())) {
			if (ghost->isWeak()) {
				// the ghost dies
				m_ghosts.erase(std::find(m_ghosts.begin(), m_ghosts.end(), ghost));
				m_score += 100;
			} else {
				// squareman dies
				m_squareman->die();
			}
		}
	}
	
	if (m_squareman->isDead()) {
		m_squareman->reset();
		m_liveCount--;
		
		if (m_liveCount == 0) {
			getGame()->changeGameState(GameState::Lost);
		} else {
			moveCharactersToInitialPosition();
		}
	}
	
	if (m_maze.getRemainingDots() == 0) {
		getGame()->changeGameState(GameState::Won);
	}

	updateCameraPosition();
	
	// updating score text
	m_scoreText.setString(std::to_string(m_score) + " points");
	m_remainingDotsText.setString(std::to_string(m_maze.getRemainingDots()) + " dots");
}

void PlayingState::draw(sf::RenderWindow& window) {
	m_scene.clear();
	m_scene.setView(m_camera);
	
	m_scene.draw(m_maze);
	m_scene.draw(*m_squareman);
	
	for (Ghost* ghost : m_ghosts)
		m_scene.draw(*ghost);
	m_scene.display();
	
	window.draw(sf::Sprite(m_scene.getTexture()));
	
	window.draw(m_scoreText);
	window.draw(m_levelText);
	window.draw(m_remainingDotsText);
	
	for (unsigned int i = 0; i < m_liveCount; i++) {
		window.draw(m_liveSprite[i]);
	}
}


// ----- LostState
LostState::LostState(Game* game, GameState* playingState) : 
GameState(game),
m_playingState(static_cast<PlayingState*>(playingState)) { 
	m_text.setFont(game->getFont());
	m_text.setString("You LOST!");
	m_text.setCharacterSize(42);
	centerOrigin(m_text);
	m_text.setPosition(240, 120);
	
	m_countDownText.setFont(game->getFont());
	m_countDownText.setCharacterSize(12);
	centerOrigin(m_countDownText);
	m_countDownText.setPosition(240, 240);
	
}

void LostState::insertCoin() {
	m_playingState->resetCurrentLevel();
	m_playingState->resetLiveCount();
	
	getGame()->changeGameState(GameState::GetReady);
}

void LostState::pressButton() { }

void LostState::moveStick(sf::Vector2i direction) { }

void LostState::update(sf::Time delta) { 
	m_countDown += delta;
	
	if (m_countDown.asSeconds() >= 10) {
		m_playingState->resetToZero();
		getGame()->changeGameState(GameState::NoCoin);
	}
		
	m_countDownText.setString("Insert a coin to continue... " + std::to_string(10 - static_cast<int>(m_countDown.asSeconds())));
}

void LostState::draw(sf::RenderWindow& window) { 
	window.draw(m_text);
	window.draw(m_countDownText);
}


// ----- WonState
WonState::WonState(Game* game, GameState* playingState) : 
GameState(game),
m_playingState(static_cast<PlayingState*>(playingState)) { 
	m_text.setFont(game->getFont());
	m_text.setString("You WON!");
	m_text.setCharacterSize(42);
	centerOrigin(m_text);
	m_text.setPosition(240, 120);
}

void WonState::insertCoin() { }

void WonState::pressButton() { }

void WonState::moveStick(sf::Vector2i direction) { }

void WonState::update(sf::Time delta) { 
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	if (timeBuffer.asSeconds() > 5) {
		m_playingState->loadNextLevel();
		getGame()->changeGameState(GameState::GetReady);
	}
}

void WonState::draw(sf::RenderWindow& window) { 
	window.draw(m_text);
}
