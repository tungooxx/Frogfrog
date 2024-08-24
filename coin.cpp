#include "header/coin.h"
#include "header/global.h"

Coin::Coin() : collected(false) {
    texture.loadFromFile("D:/test3/img/res/JumpingShiningCoin.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(8, 8, 8, 8));
    collected = false;
}

void Coin::update() {
    int numFrames = 272 / 8;
    float frameTime = 1.0f / 30.0f;
    if (clock.getElapsedTime().asMilliseconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames;
        int left = currentFrame * 8;
        sprite.setTextureRect(sf::IntRect(left, 8, 8, 8));
        clock.restart();
    }
}

void Coin::spawn(const sf::RenderWindow& i_window, int index) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)) + index);
    int x = std::rand() % ((CELL_SIZE * MAP_WIDTH) - static_cast<int>(sprite.getGlobalBounds().width));
    int y = std::rand() % ((FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT - 16) - static_cast<int>(sprite.getGlobalBounds().height));
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

void Coin::collect() {
    collected = true;
}

void Coin::draw(sf::RenderWindow& i_window) const {
    if (!collected) {
        i_window.draw(sprite);
    }
}

bool Coin::collecting() const {
    return collected;
}

sf::FloatRect Coin::getBounds() const {
    return sprite.getGlobalBounds();
}
