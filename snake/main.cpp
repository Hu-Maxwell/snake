#include <iostream>
#include <SFML/Graphics.hpp>


#include "snake.hpp"

class Grid {
public:

    bool isEmpty;
    bool isSnake;
    bool isApple;

    Grid() {
        isEmpty = true; 
    }

    void fillStart(Grid (&arr)[9][9]) {
        // puts snake and apple where they are
        arr[2][5].isSnake = true; 
        arr[6][5].isApple = true; 
    }


    void drawGrid() {
        // assume 900 is width and height
        // black screen, with very thin white lines for each one 
        
        for (int i = 0; i < 9; i++) {
            sf::RectangleShape(sf::Vector2f(1, 1));
            // or use line func
        }
    }
}; 


int main()
{
    Grid arr[9][9]; 

    sf::RenderWindow window(sf::VideoMode(900, 900), "snake");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display(); 

    }
   
}