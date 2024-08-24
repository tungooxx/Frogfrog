#include "header/bullet.h"
#include "header/global.h"
#include <cmath>
#include <iostream>

Bullet::Bullet(float startX, float startY, float dirX, float dirY) : speed(1.0f), canHome(false), currentFrame(0), frameWidth(16), change(false){
	sprite.setPosition(startX, startY);
	sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameWidth));
    float mag = std::sqrt(std::pow((startX - dirX), 2) + std::pow((startY - dirY), 2));
    direction = sf::Vector2f(dirX / mag, dirY / mag);
    lifetimeTimer.restart();
}
void Bullet::update(float x, float y) {
	int numFrames;
	if(change == true){
		numFrames = 64 / 16; 
	}
	else{
		numFrames = 95 / 14;
	}
	float frameTime = 0.4f;
	sprite.move(direction * speed);
	if (frameClock.getElapsedTime().asSeconds() >= frameTime) {
		currentFrame = (currentFrame + 1) % numFrames;
		int left = currentFrame * frameWidth;
		if(change == true){
			sprite.setTextureRect(sf::IntRect(left, 0, 16, 16)); 
		}
		else{
			sprite.setTextureRect(sf::IntRect(left, 0, 14, 14));
		}
		if(currentFrame == 0 && !canHome){
		sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameWidth));
		change = true;
		sf::Vector2f bulletPos = sprite.getPosition();
        float dirX = x - bulletPos.x;
        float dirY = y - bulletPos.y;
        float mag = std::sqrt(std::pow(dirX, 2) + std::pow(dirY, 2));
        direction = sf::Vector2f(dirX / mag, dirY / mag);
        sprite.move(direction * 0.5f); 
        canHome = true;
		}
		frameClock.restart();
	}


}

void Bullet::draw(sf::RenderWindow& i_window) {
	if(change == true){
	texture.loadFromFile("D:/test3/img/bullet.png");
	sprite.setTexture(texture);
	}
	else{
	texture.loadFromFile("D:/test3/img/first_stage.png");
	sprite.setTexture(texture);
	}
    i_window.draw(sprite);
}

sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}
