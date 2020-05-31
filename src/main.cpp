#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "SquareMan");
	
	while (window.isOpen()) {
		
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		window.clear();
		
		// draw here...
		
		window.display();
	}
	
	return EXIT_SUCCESS;
}
