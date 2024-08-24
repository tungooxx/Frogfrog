#include "header/Letter.h"

Letter::Letter(const std::string& textstr, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
    : text(textstr, font, characterSize) {
    text.setPosition(position);
    text.setFillColor(sf::Color::Transparent); // Hide the text, we'll draw it with lightning
}

void Letter::draw(sf::RenderWindow& window) {
    for (auto& lightning : lightnings) {
        lightning.draw(window);
    }
    window.draw(text); // Optionally draw the text as well, or just the lightning
}

void Letter::addLightningStrike(const sf::Vector2f& start, const sf::Vector2f& end) {
    lightnings.emplace_back(start, end);
}

void Letter::updateLightning() {
    for (auto& lightning : lightnings) {
        lightning.update();
    }
    lightnings.erase(std::remove_if(lightnings.begin(), lightnings.end(), [](const Lightning& l) {
        return l.isComplete();
    }), lightnings.end());
}
