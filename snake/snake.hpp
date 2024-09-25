#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>

class Node {
public:
    Node(int x, int y);
};

class SnakeList {
public:
    SnakeList();
};

class Grid {
public:

    Grid();
    void respawnApple();
    bool checkIfDead();
    void updateSnake();
    void drawGrid(sf::RenderWindow& window);
    void moveSnake(sf::Keyboard::Key input);
};

void startScreen(sf::RenderWindow& window, bool& isPlaying); 
void gameScreen(sf::RenderWindow& window, bool& isPlaying); 


#endif

