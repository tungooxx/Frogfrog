#ifndef CARMANAGER_H
#define CARMANAGER_H
#include "car.h"

class CarsManager
{
	std::vector<Car> cars;
public:
	CarsManager(unsigned char i_level);

	void draw(sf::RenderWindow& i_window);
	void generate_level(unsigned char i_level);
	void update(Frog& i_frog);
	void god(Frog& i_frog);
};
#endif