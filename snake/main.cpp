#include <iostream>
#include <SFML/Graphics.hpp>

#include "snake.hpp"

// TODO: 


// implement snake moving around 
// snake eating apple

// apple respawning in random location
// then add checks so apple does not spawn in snake

// then add functionality for snake length increasing for one each apple eaten

// make the snake's head different colored

// if snake's head = any snake part, it dies

// add start screen -> game -> freeze when die -> click -> start screen but different text   


class Grid {
public:
    std::string arr[9][9];

    Grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                arr[i][j] = "empty"; 
            }
        }

        arr[2][4] = "snake"; 
        arr[6][4] = "apple";
    }


    void drawGrid(sf::RenderWindow& window) {

        sf::Vector2u size = window.getSize();
        unsigned int sideLen = size.x;
        float boxLen = sideLen / 9.0f; 

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sf::RectangleShape square(sf::Vector2f(boxLen, boxLen)); 
                square.setPosition(boxLen * j, boxLen * i); 

                if (arr[j][i] == "empty") {
                    square.setFillColor(sf::Color::Transparent);
                    square.setOutlineThickness(1.f); 
                }
                else if (arr[j][i] == "snake") {
                    square.setFillColor(sf::Color::Red);
                }
                else if (arr[j][i] == "apple") {
                    square.setFillColor(sf::Color::Blue);
                }

                window.draw(square);

            }
        }
    }

    void moveSnake(sf::RenderWindow& window) {

    }
}; 


int main() {
    sf::RenderWindow window(sf::VideoMode(900, 900), "snake");
    window.setFramerateLimit(10); 

    Grid grid; 

    while (window.isOpen()) {
        window.clear();



        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                std::cout << "W"; 
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                std::cout << "A";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                std::cout << "S";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                std::cout << "D";
            }

        }


        // when key pressed change direction

        grid.drawGrid(window); 
        window.display(); 
    }
   
}