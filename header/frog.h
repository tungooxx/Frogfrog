#ifndef FROG_H
#define FROG_H

#include <SFML\Graphics.hpp>
#include <array> 
#include <chrono>
#include <cmath>
class Frog

{
		bool dead;
		short x;
		bool god;
		unsigned char animation_timer;

		unsigned char current_frame;
		//Current direction
		unsigned char direction;

		unsigned short y;

		std::array<bool, 4> control_keys;
		//spread sprite
		sf::Sprite sprite;
		//texture
		sf::Texture texture;

public:
	Frog();
	void blink();
	bool get_dead() const;
	bool get_god() const;
	bool update_swamp(std::array<bool,5>& i_swamp);
	unsigned short get_y() const;
	unsigned short get_x() const;
	void draw(sf::RenderWindow& i_window);
	void move(char i_value);
	void reset();
	void set_dead();
	void set_god(bool value);
	void update();
	sf::FloatRect get_rect() const;

private:
	float blink_distance;
	sf::Vector2f blink_direction;

};

#endif