#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
	    sf::Texture texture;
    sf::Sprite sprite;
public:
    Bullet(float startX, float startY, float dirX, float dirY);
    void update(float x, float y);
    void draw(sf::RenderWindow& i_window);
    sf::FloatRect getBounds() const;

private:
    sf::Vector2f direction;
    sf::Clock frameClock;
    sf::Clock lifetimeTimer;
    bool canHome;
    float speed;
    int currentFrame;
    const int frameWidth;
	bool change;
};

#endif
