#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "header/drawmap.h"
#include "header/global.h"

void draw_map(const std::array<bool, 5>& i_swamp, sf::RenderWindow& i_window, unsigned char i_level)
{
	sf::Sprite sprite;

	sf::Texture texture;
	if(i_level >= 1) {
		texture.loadFromFile("D:/test3/img/Map-2.png");
	}
	else {
		texture.loadFromFile("D:/test3/img/Map-1.png");
	}
	sprite.setTexture(texture);
	sf::RectangleShape darkOverlay(sf::Vector2f(i_window.getSize()));
	darkOverlay.setFillColor(sf::Color(0, 0, 0, 150));
	for (unsigned char a = 0; a < MAP_HEIGHT; a++)
	{
		if (a == floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 1)
		{
			sprite.setTextureRect(sf::IntRect(4 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}
		else if (a == 1 + floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 3)
		{
			sprite.setTextureRect(sf::IntRect(5 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}
		else if (a == 2 + floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 2)
		{
			sprite.setTextureRect(sf::IntRect(6 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}
		else if (a == 3 + floor(0.5f * MAP_HEIGHT))
		{
			sprite.setTextureRect(sf::IntRect(7 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}
		else if (a == MAP_HEIGHT - 4)
		{
			sprite.setTextureRect(sf::IntRect(8 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(3 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		}

		for (unsigned char b = 0; b < MAP_WIDTH; b++)
		{
			sprite.setPosition(static_cast<float>(CELL_SIZE * b), static_cast<float>(CELL_SIZE * a));

			if (0 == a)
			{
				if (0 == b % 3)
				{
					sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
				}
				else
				{
					sprite.setTextureRect(sf::IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
				}
			}
			else if (1 == a)
			{
				if (0 == b % 3)
				{
					sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
				}
				else
				{
					sprite.setTextureRect(sf::IntRect(3 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
				}
			}

			i_window.draw(sprite);
		}
	}
	if(i_level >= 1) {
		i_window.draw(darkOverlay);
	}
	sprite.setTextureRect(sf::IntRect(9 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));

	for (unsigned char a = 0; a < i_swamp.size(); a++)
	{
		if (1 == i_swamp[a])
		{
			sprite.setPosition(3 * CELL_SIZE * (0.5f + a), CELL_SIZE);

			i_window.draw(sprite);
		}
	}
}