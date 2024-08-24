#ifndef BOSS_HPP
#define BOSS_HPP

#include <SFML\Graphics.hpp>
#include <vector>
#include "bullet.h"

class Boss
{
public:
	Boss();
	void update(float fx, float fy);
	void draw(sf::RenderWindow& window, float fx, float fy);
	std::vector<Bullet>& getBullets();
	void resetbullets(){
		bullets.clear();
	};

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<Bullet> bullets;
	float shootTimer;
	float ShootInterval;
	void shoot(float fx, float fy);
};

#endif