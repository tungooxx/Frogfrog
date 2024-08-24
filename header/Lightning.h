#ifndef LIGHTNING_H
#define LIGHTNING_H

#include <SFML/Graphics.hpp>

class Lightning {
public:
    Lightning(const sf::Vector2f& start, const sf::Vector2f& end);
    void update();
    void draw(sf::RenderWindow& window);
    bool isComplete() const;

private:
    sf::VertexArray lightning;
    sf::Vector2f start;
    sf::Vector2f end;
    float progress;
    float speed;
    bool complete;
};

#endif // LIGHTNING_H
