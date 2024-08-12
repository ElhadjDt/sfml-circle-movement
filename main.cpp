#include <SFML/Graphics.hpp>
#include <ctime>

// Function to detect collision between two circles
// Returns true if there is a collision between the two circles
bool detectCollision(sf::CircleShape& circle1, sf::CircleShape& circle2) {
    sf::Vector2f position1 = circle1.getPosition(); // Get the top-left position of the bounding box of circle1
    sf::Vector2f position2 = circle2.getPosition(); // Get the top-left position of the bounding box of circle2
    position1.x += circle1.getRadius(); // Adjust to center position
    position1.y += circle1.getRadius(); // Adjust to center position
    position2.x += circle2.getRadius(); // Adjust to center position
    position2.y += circle2.getRadius(); // Adjust to center position

    // Check if distance between the centers is less than the sum of the radii
    if (sqrt(pow((position1.x - position2.x), 2) + pow((position1.y - position2.y), 2)) < (circle1.getRadius() + circle2.getRadius())) {
        return true;
    }
    return false;
}

// Returns a random color
sf::Color randomColor() {
    srand((unsigned int)time(NULL));
    switch (rand() % 6) {
    case 0: return sf::Color::Blue;
    case 1: return sf::Color::Green;
    case 2: return sf::Color::Magenta;
    case 3: return sf::Color::Red;
    case 4: return sf::Color::White;
    case 5: return sf::Color::Yellow;
    }
    return sf::Color::Black; // Default color in case of an error
}

// Circle class definition
class Circle {
public:
    sf::CircleShape shape;

    // Constructors
    Circle() {}
    Circle(float x, float y) {
        shape.setRadius(15);
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(x, y);
    }

    // Move the circle to the right
    void moveRight(sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        position.x += 10;
        if (position.x < 0 || position.x > windowSize.x - shape.getRadius() * 2) return;
        shape.setPosition(position);
    }

    // Move the circle to the left
    void moveLeft(sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        position.x -= 10;
        if (position.x < 0 || position.x > windowSize.x - shape.getRadius() * 2) return;
        shape.setPosition(position);
    }

    // Move the circle up
    void moveUp(sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        position.y -= 10;
        if (position.y < 0 || position.y > windowSize.y - shape.getRadius() * 2) return;
        shape.setPosition(position);
    }

    // Move the circle down
    void moveDown(sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        position.y += 10;
        if (position.y < 0 || position.y > windowSize.y - shape.getRadius() * 2) return;
        shape.setPosition(position);
    }

    // Increase the size of the circle
    void increaseSize(sf::Vector2u& windowSize) {
        sf::CircleShape temp;
        temp.setRadius(shape.getRadius() * 1.2);
        temp.setPosition(shape.getPosition());
        sf::Vector2f position = temp.getPosition();
        if (position.x < 0 || position.x > windowSize.x - temp.getRadius() * 2 || position.y < 0 || position.y > windowSize.y - temp.getRadius() * 2) return;
        shape.setRadius(shape.getRadius() * 1.2);
    }

    // Decrease the size of the circle
    void decreaseSize() {
        shape.setRadius(shape.getRadius() / 1.2);
    }

    // Check if the circle is within the window
    bool isInWindow(sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        return !(position.x < 0 || position.x > windowSize.x - shape.getRadius() * 2 || position.y < 0 || position.y > windowSize.y - shape.getRadius() * 2);
    }
};

// Circle2 class definition for random circle
class Circle2 : public Circle {
public:
    sf::CircleShape randomCircle;

    // Constructor
    Circle2() {
        randomCircle.setRadius(10);
        randomCircle.setFillColor(sf::Color::Red);
    }

    // Set random position for the random circle
    void setRandomPosition(sf::Vector2u windowSize) {
        sf::Vector2f randomPosition;
        srand((unsigned int)time(NULL));
        do {
            randomPosition.x = rand() % (windowSize.x + 1);
            randomPosition.y = rand() % (windowSize.y + 1);
            randomCircle.setPosition(randomPosition);
        } while (detectCollision(randomCircle, shape) && !isInWindow(windowSize));
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Movement");
    sf::Vector2u windowSize = window.getSize();

    Circle* movingCircle = new Circle(0, 0);
    Circle2* staticCircle = new Circle2();
    staticCircle->setRandomPosition(windowSize);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f position;
                    position.x = event.mouseButton.x;
                    position.y = event.mouseButton.y;
                    if ((position.x < 0 || position.x + movingCircle->shape.getRadius() * 2 > windowSize.x - movingCircle->shape.getRadius() * 2) ||
                        (position.y < 0 || position.y + movingCircle->shape.getRadius() * 2 > windowSize.y - movingCircle->shape.getRadius() * 2)) continue;
                    movingCircle->shape.setPosition(position);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) movingCircle->moveLeft(windowSize);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movingCircle->moveRight(windowSize);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) movingCircle->moveUp(windowSize);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) movingCircle->moveDown(windowSize);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movingCircle->increaseSize(windowSize);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movingCircle->decreaseSize();
        }

        while (detectCollision(movingCircle->shape, staticCircle->randomCircle)) {
            movingCircle->increaseSize(windowSize);
            staticCircle->setRandomPosition(windowSize);
            staticCircle->randomCircle.setFillColor(randomColor());
        }

        window.clear(sf::Color::Black);
        window.draw(movingCircle->shape);
        window.draw(staticCircle->randomCircle);
        window.display();
    }

    delete movingCircle;
    delete staticCircle;

    return 0;
}
