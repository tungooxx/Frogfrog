#ifndef BOLT_H
#define BOLT_H

#include <SFML/Graphics.hpp>

class Bolt {
public:
    Bolt();
    void Spark(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
    // Other member functions and variables
private:
    // Private member variables
};

#endif // BOLT_H
