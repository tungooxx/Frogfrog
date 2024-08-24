#ifndef COIN_H
#define COIN_H
#include <SFML\Graphics.hpp>
#include <vector>
class Coin
{
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Coin();
	void update();
	void draw(sf::RenderWindow& i_window) const;
	void spawn(const sf::RenderWindow& i_window, int index);
	void collect();
	sf::FloatRect getBounds() const;
	bool collecting() const;
private:
	bool collected;
	sf::Clock clock;
	int currentFrame;
};

#endif