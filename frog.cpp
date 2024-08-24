#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "header/frog.h"
#include "header/global.h"
#include "header/ultil.h"

Frog::Frog() : god(false), blink_distance(50.0f), blink_direction(0.0f, 0.0f)
{
	reset();
}
bool Frog::get_dead() const
{
	return dead;
}
bool Frog::get_god() const
{
	return god;
}



bool Frog::update_swamp(std::array<bool, 5>& i_swamp)
{
	if (CELL_SIZE >= y)
	{
		if (floor(0.75f * CELL_SIZE) <= x % (3 * CELL_SIZE) && floor(2.25f * CELL_SIZE) >= x % (3 * CELL_SIZE))
		{
			unsigned char swamp_spot = static_cast<unsigned char>(floor(x / static_cast<float>(3 * CELL_SIZE)));

			if (0 == i_swamp[swamp_spot])
			{
				i_swamp[swamp_spot] = 1;

				return 1;
			}
			else
			{
				set_dead();
			}
		}
		else
		{
			set_dead();
		}
	}

	return 0;
}

unsigned short Frog::get_y() const
{
	return y;
}
unsigned short Frog::get_x() const
{
	return x;
}

void Frog::draw(sf::RenderWindow& i_window)
{
	if (0 == dead)
	{
		texture.loadFromFile("D:/test2/img/Frog.png");
	}
	else
	{
		texture.loadFromFile("D:/test2/img/FrogDeath.png");
	}

	sprite.setPosition(x, y);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(CELL_SIZE * current_frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

	i_window.draw(sprite);
}

void Frog::move(char i_value)
{
	x = clamp(static_cast<int>(i_value) + x, 0, CELL_SIZE * (MAP_WIDTH - 1));
}

void Frog::reset()
{
	dead = 0;
	god = false;
	x = static_cast<short>(CELL_SIZE * floor(0.5f * MAP_WIDTH));

	animation_timer = 0;
	current_frame = 1;
	direction = 1;

	y = CELL_SIZE * (MAP_HEIGHT - 1);

	control_keys[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	control_keys[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	control_keys[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	control_keys[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}



void Frog::set_dead()
{
	if(god) return;
	if (0 == dead)
	{
		dead = 1;

		animation_timer = 0;
		current_frame = 0;
	}
}

void Frog::update()
{
	if (0 == dead)
	{
		bool moved = 0;

		if (0 == control_keys[0] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			blink_direction = sf::Vector2f(1.0f, 0.0f);
			moved = 1;

			x = std::min(CELL_SIZE + x, CELL_SIZE * (MAP_WIDTH - 1));

			direction = 0;
		}
		else if (0 == control_keys[1] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			blink_direction = sf::Vector2f(0.0f, -1.0f);
			moved = 1;

			y = std::max(y - CELL_SIZE, 0);

			direction = 1;
		}
		else if (0 == control_keys[2] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			blink_direction = sf::Vector2f(-1.0f, 0.0f);
			moved = 1;

			x = std::max(x - CELL_SIZE, 0);

			direction = 2;
		}
		else if (0 == control_keys[3] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			blink_direction = sf::Vector2f(0.0f, 1.0f);
			moved = 1;

			y = std::min(CELL_SIZE + y, CELL_SIZE * (MAP_HEIGHT - 1));

			direction = 3;
		}

		control_keys[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		control_keys[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		control_keys[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		control_keys[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		if (1 == moved)
		{
			animation_timer = FROG_ANIMATION_SPEED;
			current_frame = 0;
		}

		if (0 == animation_timer)
		{
			current_frame = 1;
		}
		else
		{
			animation_timer--;
		}
	}
	else if (y < CELL_SIZE * floor(0.5f * MAP_HEIGHT))
	{
		if (0 == animation_timer)
		{
			animation_timer = FROG_ANIMATION_SPEED;
			current_frame = std::min(3, 1 + current_frame);
		}
		else
		{
			animation_timer--;
		}
	}
}

sf::FloatRect Frog::get_rect() const
{
	return sf::FloatRect(x, y, CELL_SIZE, CELL_SIZE);
}

void Frog::blink() {

	x = clamp(static_cast<int>(x + blink_direction.x * CELL_SIZE*2), 0, CELL_SIZE * (MAP_WIDTH - 1));
	y = clamp(static_cast<int>(y + blink_direction.y * CELL_SIZE*2), 0, CELL_SIZE * (MAP_HEIGHT - 1));
}
void Frog::set_god(bool value){
	god = value;
}