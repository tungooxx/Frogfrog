#ifndef DRAWMAP_H
#define DRAWMAP_H
#include <SFML\Graphics.hpp>
#include <array> 
#include <chrono>
#include <cmath>
void draw_map(const std::array<bool, 5>& i_swamp, sf::RenderWindow& i_window, unsigned char i_level);
#endif