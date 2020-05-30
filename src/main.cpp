#include <iostream>
#include <SFML/System.hpp>

int main() {
	
	std::cout << "SquareMan" << std::endl;
	
	sf::Time time = sf::seconds(1.2);
	
	auto timeInSeconds = time.asSeconds();
	
	std::cout << timeInSeconds << std::endl;
	
	return EXIT_SUCCESS;
}
