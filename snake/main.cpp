#include <iostream>
#include <SFML/Graphics.hpp>

#include "snake.hpp"

// TODO: 
// add start screen -> game -> freeze when die -> click -> start screen but different text   
// make an animation where all the blocks in the snake turn into a different color when dying 
// don't allow snake to move in opp direction of current one

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
    std::pair<int, int> changeDir; 
    std::pair<int, int> applePos; 

    Grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                arr[j][i] = "empty"; 
            }
        }

        applePos.first = 6; 
        applePos.second = 4; 
        arr[applePos.first][applePos.second] = "apple";

        changeDir.first = 0;
        changeDir.second = 0; 
    }

    void respawnApple() {
        srand((unsigned)time(NULL));
        arr[applePos.first][applePos.second] = "empty";

        while (true) {
            bool appleIsFree = true; 
            applePos.first = rand() % 9;
            applePos.second = rand() % 9;

            Node* cur = snake.head;
            while (cur != nullptr) {
                if (cur->position == applePos) {
                    appleIsFree = false; 
                    break;
                }
                cur = cur->next; 
            }

            if (appleIsFree) {
                break;
            }
        }

        arr[applePos.first][applePos.second] = "apple";

    }
    void checkIfDead() {
        // if snake is out of bounds
        std::pair<int, int> snakeHeadPos = snake.head->position;

        if (snakeHeadPos.first < 0 || snakeHeadPos.second < 0 || snakeHeadPos.first > 9 || snakeHeadPos.second > 9) {
            std::cout << "dead"; 
        }

        // if snake's head is in itself
        Node* cur = snake.head->next; 
        while (cur != nullptr) {
            if (cur->position == snakeHeadPos) {

                // says dead each time apple is eaten
                if (snake.head == snake.tail) {
                    if (snakeHeadPos != snake.tail->position) {
                        std::cout << "dead";
                    }
                }
                else {
                    if (snakeHeadPos != snake.head->next->position) {
                        std::cout << "dead";
                    }
                }
            }
            cur = cur->next; 
        }

    }

     void updateSnake() {
        // clears all snake elements
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (arr[j][i] == "snake" || arr[j][i] == "snakeHead") {
                    arr[j][i] = "empty";
                }
            }
        }

        // calculates snake's new head location
        int newHeadX = snake.head->position.first + changeDir.first;
        int newHeadY = snake.head->position.second + changeDir.second;
        
        std::pair<int, int> snakeHeadCoords(newHeadX, newHeadY);

        if (snakeHeadCoords == applePos) {
            if (snake.head == snake.tail) {
                // sets 
                Node* newTail = new Node(snake.head->position.first, snake.head->position.second);

                snake.head->position = snakeHeadCoords; 

                newTail->prev = snake.head; 
                snake.head->next = newTail; 
                snake.tail = newTail; 
            } else {
                // sets new tail
                Node* newTail = new Node(snake.tail->position.first, snake.tail->position.second); 
                newTail->prev = snake.tail->prev; 
                newTail->next = nullptr; // prolly can use copy assignment operator here
                newTail->prev->next = newTail; 

                // sets new head 
                snake.tail->position = snakeHeadCoords; 
                snake.tail->prev = nullptr; 
                snake.tail->next = snake.head; 
                snake.head->prev = snake.tail;

                // updates head and tail pointer
                snake.head = snake.tail; 
                snake.tail = newTail; 
            }
            respawnApple(); 
        }
        // if single node
        if (snake.head == snake.tail) {
            snake.head->position.first = newHeadX; 
            snake.head->position.second = newHeadY; 
        } else { // if more than one node
            // sets new head 
            snake.tail->position = snakeHeadCoords;


            // sets new tail
            Node* newTail = snake.tail->prev;
            newTail->next = nullptr;

            // sets new head
            snake.tail->prev = nullptr;
            snake.tail->next = snake.head;
            snake.head->prev = snake.tail;
         
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
            arr[snake.head->position.first][snake.head->position.second] = "snakeHead";

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
                else if (arr[j][i] == "snakeHead") {
                    square.setFillColor(sf::Color::Green);
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

        std::pair<int, int> oldDir = changeDir; 
        
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

        if (changeDir.first != 0) {
            if ((changeDir.first + oldDir.first) == 0) {
                changeDir = oldDir;
            }
        } 
        if (changeDir.second != 0) {
            if ((changeDir.second + oldDir.second) == 0) {
                changeDir = oldDir; 
            }
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
            grid.checkIfDead();
            grid.updateSnake(); 
        }

        grid.drawGrid(window);
        window.display();
    }
}