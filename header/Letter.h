#ifndef LETTER_H
#define LETTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Lightning.h"

class Letter {
public:
    Letter(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void addLightningStrike(const sf::Vector2f& start, const sf::Vector2f& end);
    void updateLightning();

private:
    sf::Text text;
    std::vector<Lightning> lightnings;
};

#endif // LETTER_H
