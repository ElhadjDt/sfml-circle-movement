#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>

// Function to detect collision between two circles
bool detectCollision(sf::CircleShape& circle1, sf::CircleShape& circle2);

// Returns a random color
sf::Color randomColor();

// Circle class definition
class Circle {
public:
    sf::CircleShape shape;

    Circle();
    Circle(float x, float y);

    void moveRight(sf::Vector2u& windowSize);
    void moveLeft(sf::Vector2u& windowSize);
    void moveUp(sf::Vector2u& windowSize);
    void moveDown(sf::Vector2u& windowSize);
    void increaseSize(sf::Vector2u& windowSize);
    void decreaseSize();
    bool isInWindow(sf::Vector2u& windowSize);
};

// Circle2 class definition for random circle
class Circle2 : public Circle {
public:
    sf::CircleShape randomCircle;

    Circle2();
    void setRandomPosition(sf::Vector2u windowSize);
};

#endif // CIRCLE_HPP
