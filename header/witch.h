#ifndef WITCH_HPP
#define WITCH_HPP

#include <SFML\Graphics.hpp>
#include <vector>
#include "bullet.h"

class Witch
{
public:
	Witch();
	void update(unsigned char level);
	void draw(sf::RenderWindow& window,unsigned char level);
	

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	int currentframe;
	bool comfirm;
	float frameTime;
};

#endif