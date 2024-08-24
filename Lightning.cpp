#include "header/Lightning.h"

Lightning::Lightning(const sf::Vector2f& start, const sf::Vector2f& end)
    : start(start), end(end), progress(0.0f), speed(0.1f), complete(false) {
    lightning.setPrimitiveType(sf::LinesStrip);
    lightning.append(sf::Vertex(start, sf::Color::White));
    lightning.append(sf::Vertex(start, sf::Color::White));
}

void Lightning::update() {
    if (complete) return;

    progress += speed;
    if (progress >= 1.0f) {
        progress = 1.0f;
        complete = true;
    }

    sf::Vector2f currentPos = start + (end - start) * progress;
    lightning[1].position = currentPos;
}

void Lightning::draw(sf::RenderWindow& window) {
    if (complete) return;
    window.draw(lightning);
}

bool Lightning::isComplete() const {
    return complete;
}
