#include <SFML/Graphics.hpp>
#include "header/witch.h"
#include "header/global.h"
#include "iostream"
Witch::Witch() : comfirm(false)
{
	frameTime = 1.0f / 60.0f;
}
void Witch::draw(sf::RenderWindow& i_window, unsigned char i_level)
{
	
	if(i_level <= 1 && !comfirm){
		texture.loadFromFile("D:/test3/img/witch_indle.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(21,36,21,36));
		float x = 4;
		float y = 0;
		sprite.setOrigin(CELL_SIZE/2.0f,CELL_SIZE/2.0f);
		sprite.setScale(1.0f,1.0f);
		sprite.setPosition(x,y);
		comfirm = true;
	}
	else if(i_level >= 2 && !comfirm){
		texture.loadFromFile("D:/test3/img/witch.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0,0,48,48));
		float x = 0;
		float y = 0;
		sprite.setOrigin(CELL_SIZE/2.0f,CELL_SIZE/2.0f);
		sprite.setScale(1.0f,1.0f);
		sprite.setPosition(x,y);
		comfirm = true;
	}
	i_window.draw(sprite);
}
void Witch::update(unsigned char i_level)
{
	if(i_level <=1){
		int numheight = 216/36;
		if (clock.getElapsedTime().asSeconds() >= 0.3f) {
			currentframe = (currentframe + 1) % numheight;
			int down = currentframe * 36; 
			sprite.setTextureRect(sf::IntRect(0, down, 21, 36)); 
			clock.restart();
		}
	}
	else if(i_level >=2){
		int numheight = 240/48;
		if (clock.getElapsedTime().asSeconds() >= 0.3f) {
			currentframe = (currentframe + 1) % numheight;
			int down = currentframe * 48; 
			sprite.setTextureRect(sf::IntRect(0, down, 48, 48)); 
			clock.restart();
		}
	}
}
