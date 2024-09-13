#include <iostream>
#include <SFML/Graphics.hpp>

#include "snake.hpp"

// TODO: 

// snake eating apple

// apple respawning in random location
// then add checks so apple does not spawn in snake

// then add functionality for snake length increasing for one each apple eaten

// make the snake's head different colored

// if snake's head = any snake part, it dies

// add start screen -> game -> freeze when die -> click -> start screen but different text   

class Node {
public: 
    std::pair<int, int> position;
    Node* next; 
    Node* prev;

    Node(int x, int y) {
        position.first = x;
        position.second = y;
        next = nullptr; 
        prev = nullptr;
    }
};

class SnakeList {
public: 
    Node* head;
    Node* tail; 

    SnakeList() {        
        Node* temp = new Node(2, 4); 
        head = temp; 
        tail = temp; 
    }
};

class Grid {
public:
    SnakeList snake; 
    std::string arr[9][9];
    std::string direction; 
    std::pair <int, int> changeDir; 

    Grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                arr[j][i] = "empty"; 
            }
        }

        arr[6][4] = "apple";

        changeDir.first = 0;
        changeDir.second = 0; 
    }

    void updateSnake() {
        // clears all snake elements
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (arr[j][i] == "snake") {
                    arr[j][i] = "empty";
                }
            }
        }

        // calculates snake's new head location
        int newHeadX = snake.head->position.first + changeDir.first;
        int newHeadY = snake.head->position.second + changeDir.second;

        // if single node
        if (snake.head == snake.tail) {
            snake.head->position.first = newHeadX; 
            snake.head->position.second = newHeadY; 
        } else { // if more than one node
            // moves snake's tail in front of snake's head
            snake.tail->position.first = newHeadX;
            snake.tail->position.second = newHeadY;

            // sets new tail
            Node* newTail = snake.tail->prev;
            if (newTail != nullptr) { // maybe line not needed?
                newTail->next = nullptr;
            }

            // sets new head
            snake.tail->prev = nullptr;
            snake.tail->next = snake.head;
            if (snake.head != nullptr) {
                snake.head->prev = snake.tail;
            }

            // updates head and tail pointer 
            snake.head = snake.tail;
            snake.tail = newTail;
        }

        // copies the current list of coordinates of the snake onto arr
        Node* cur = snake.head;
        while (cur != nullptr) {
            int x = cur->position.first;
            int y = cur->position.second;

            arr[x][y] = "snake";

            cur = cur->next;
        }
    }

    void drawGrid(sf::RenderWindow& window) {
        // initalzing box size 
        sf::Vector2u size = window.getSize();
        unsigned int sideLen = size.x;
        float boxLen = sideLen / 9.0f; 

        // drawing the entire grid 
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

    void moveSnake(sf::Keyboard::Key input) {
        Node* cur = snake.head; 
        
        if (input == sf::Keyboard::W) {
            changeDir.first = 0;
            changeDir.second = -1;
        }
        else if (input == sf::Keyboard::A) {
            changeDir.first = -1;
            changeDir.second = 0;
        }
        else if (input == sf::Keyboard::S) {
            changeDir.first = 0;
            changeDir.second = 1;
        }
        else if (input == sf::Keyboard::D) {
            changeDir.first = 1;
            changeDir.second = 0;
        }
    }
}; 

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 900), "snake");

    Grid grid; 
    sf::Clock clock;
    sf::Keyboard::Key direction = sf::Keyboard::Unknown;

    while (window.isOpen()) {
        window.clear();

        sf::Time time = clock.getElapsedTime();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::S ||
                    event.key.code == sf::Keyboard::D) {

                    direction = event.key.code;

                    grid.moveSnake(direction);
                }
            }
        }

        if (time.asSeconds() > .18f) {
            clock.restart();
            grid.updateSnake(); 
        }

        grid.drawGrid(window);
        window.display();
    }
}