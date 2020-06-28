#ifndef SQUAREMAN_BONUS_HPP
#define SQUAREMAN_BONUS_HPP

#include <SFML/Graphics.hpp>

class Bonus : public sf::Drawable, public sf::Transformable {
public:
	enum Fruit {
		Banana,
		Apple,
		Cherry
	};
	
	Bonus(sf::Texture& texture);
	void setFruit(Fruit fruit);
	
private:
	sf::Sprite m_visual;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SQUAREMAN_BONUS_HPP
