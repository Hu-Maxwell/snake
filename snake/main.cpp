#include <iostream>
#include <SFML/Graphics.hpp>
#define EXIT_FAILURE

#include "snake.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(900, 900), "snake");

    Grid grid; 
    sf::Clock clock;
    sf::Keyboard::Key direction = sf::Keyboard::Unknown;

    bool isPlaying = false; 

    while (window.isOpen()) {
        if (isPlaying == false) {
            startScreen(window, isPlaying); 
        }
        else {
            gameScreen(window, isPlaying); 
        }
    }
}