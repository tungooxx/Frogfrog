#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include "header/car.h"
#include "header/frog.h"
#include "header/carmanager.h"
#include "header/drawmap.h"
#include "header/drawtext.h"
#include "header/global.h"
#include "header/log.h"
#include "header/turtle.h"
#include "header/rivermanager.h"
#include "header/boss.h"
#include "header/bullet.h"
#include "header/gamestate.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "header/coin.h"
#include "header/witch.h"
int main() {

	State gamestate = State::intro;

	bool next_level = 0;
	bool is_paused = false;
	unsigned char level = 2;

	unsigned short timer = TIMER_INITIAL_DURATION;
	unsigned short timer_duration = TIMER_INITIAL_DURATION;

	std::array<bool, 5> swamp = {0};

	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, SCREEN_RESIZE * (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)), "Frogger", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	std::vector<Bullet> bullets;

	CarsManager cars_manager(level);

	Witch witch;

	Frog frog;
	Coin coin;
	std::vector<Coin> coins;
	for(int i = 0;i<5;i++){
		coin.spawn(window,i);
		coins.push_back(coin);
	}
	int conir = 0;

	Boss boss;
	RiverManager river_manager(level);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("D:/test2/img/Metal.ogg");
	sf::Sound sound;
	sound.setBuffer(buffer);

	sf::Texture BG;
	BG.loadFromFile("D:/test2/img/mainmenu.jpg");
	sf::Sprite SP;
	SP.setTexture(BG);

	sf::Texture BG2;
	BG2.loadFromFile("D:/test3/img/mainmenu2.jpeg");
	sf::Sprite SP2;
	SP2.setTexture(BG2);

	//Video
	std::vector<sf::Texture> frames;
	for (int i = 1; i < 2; i++) {
		sf::Texture texture;
		std::string filename = "D:/test3/intro/frame_" + std::to_string(i) + ".jpg";
		if (texture.loadFromFile(filename)) {
			frames.push_back(texture);
		}
	}
	sf::Sprite introsprite;
	int frameIndex = 0;
	sf::Clock clock;
	float frameTime = 1.0f / 60.0f;

	bool playing = true;
	bool changemm = false;
	previous_time = std::chrono::steady_clock::now();
	std::string inputbuffer;
	while (1 == window.isOpen())
	{
		sf::Event event;


		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;
		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;
			while (1 == window.pollEvent(event))
			{

				switch (event.type)
				{

				case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::MouseButtonPressed: {
					if (gamestate == State::menu) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							changemm = true;
						}
					}
					break;
					}
				case sf::Event::TextEntered: {
					if(std::isprint(event.text.unicode))
					{
						inputbuffer += static_cast<char>(event.text.unicode);
						if(inputbuffer.size() >= 3 &&  inputbuffer.substr(inputbuffer.size()-3) == "god")
						{
							frog.set_god(true);
						}
					}
					break;
				}

				case sf::Event::KeyPressed:
					if (gamestate == State::menu)
					{
						if(event.key.code == sf::Keyboard::M) {
							if(playing) {
								sound.stop();
								playing = false;
							}
							else {
								sound.play();
								playing = true;
							}
						}
						if(event.key.code == sf::Keyboard::P) {
							sound.stop();
							playing = false;
							frameIndex = 0;
							gamestate = State::intro;
						}

						if (event.key.code == sf::Keyboard::Return)
						{
							gamestate = State::play;

						}
					}
					else if (gamestate == State::intro)
					{
						if (event.key.code == sf::Keyboard::Return)
						{
							gamestate = State::menu;
						}
					}
					else if(gamestate == State::play)
					{
						if(event.key.code == sf::Keyboard::F1) {
							is_paused = !is_paused;
						}
						if(event.key.code == sf::Keyboard::M) {
							if(playing) {
								sound.stop();
								playing = false;
							}
							else {
								sound.play();
								playing = true;
							}
						}
						if(event.key.code == sf::Keyboard::P) {
							sound.stop();
							playing = false;
							frameIndex = 0;
							gamestate = State::intro;
						}
						if (event.key.code == sf::Keyboard::B) {
							frog.blink();
						}
					}
					break;
				}
			}

			if (gamestate == State::play) {
				if(!is_paused) {

					if (1 == next_level)
					{
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						{
							next_level = 0;
						}
					}
					else
					{
						if (0 == frog.get_dead())
						{
							if (0 == timer)
							{
								frog.set_dead();
							}
							else
							{
								timer--;
							}
						}
						for(auto& coin : coins){
							coin.update();
						}
						frog.update();
						if(level >= 1) {
							boss.update(frog.get_x(), frog.get_y());
						}
						witch.update(level);
						cars_manager.update(frog);
						river_manager.update(frog);
					}

					if (1 == frog.get_dead())
					{
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						{
							coins.clear();

							for(int i = 0;i<5;i++){
								coin.spawn(window,i);
								coins.push_back(coin);
							}

							timer = TIMER_INITIAL_DURATION;
							timer_duration = TIMER_INITIAL_DURATION;

							swamp.fill(0);

							cars_manager.generate_level(level);

							river_manager.generate_level(level);
							boss.resetbullets();
							frog.reset();

						}
					}
					else if (1 == frog.update_swamp(swamp))
					{
						bool swamp_full = 1;

						for (unsigned char a = 0; a < swamp.size(); a++)
						{
							if (0 == swamp[a])
							{
								swamp_full = 0;
								break;
							}
						}

						if (1 == swamp_full)
						{
							next_level = 1;
							level++;
							timer_duration = std::max<unsigned short>(floor(0.25f * TIMER_INITIAL_DURATION), timer_duration - TIME_REDUCTION);
							timer = timer_duration;

							if (TOTAL_LEVELS == level)
							{
								level = static_cast<unsigned char>(floor(0.5f * TOTAL_LEVELS));
							}

							swamp.fill(0);
							cars_manager.generate_level(level);
							river_manager.generate_level(level);
						}
						else
						{
							timer = std::min<unsigned short>(timer_duration, timer + floor(0.5f * timer_duration));
						}

						frog.reset();
					}
				}
			}
			if (FRAME_DURATION > lag)
			{
				window.clear();
				if (gamestate == State::intro)
				{
					window.setView(sf::View(sf::FloatRect(0, 0, 756, 756)));

					if (clock.getElapsedTime().asSeconds() >= frameTime) {
						frameIndex = (frameIndex + 1) % frames.size();
						introsprite.setTexture(frames[frameIndex]);
						clock.restart();
						if(frameIndex ==0){
							sound.play();
							gamestate = State::menu;
						}
					}
					window.draw(introsprite);
				}
				else if (gamestate == State::menu)
				{
					window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));
					if(!changemm) {
						window.draw(SP);
					}
					else {
						window.draw(SP2);
					}
					draw_text(0, CELL_SIZE * 3, CELL_SIZE * MAP_HEIGHT, "Press Enter to Start", window);
				}
				else if (gamestate == State::play)
				{
					if (1 == next_level)
					{
						draw_text(1, 0, 0, "NEXT LEVEL!", window);
					}
					else
					{
						draw_map(swamp, window,level);

						if (0 == frog.get_dead()) {
							for(const auto& coin : coins){
								coin.draw(window);
							}
							river_manager.draw(window);
							if(level >= 1){
								boss.draw(window, frog.get_x(), frog.get_y());
							}
							witch.draw(window,level);
							frog.draw(window);

						}
						else
						{							
							for(const auto& coin : coins){
								coin.draw(window);
							}

							if(level >= 1){
								boss.draw(window, frog.get_x(), frog.get_y());
							}
							witch.draw(window,level);
							frog.draw(window);
							river_manager.draw(window);
						}

						cars_manager.draw(window);

						if (frog.get_god() == 1)
						{
							draw_text(0, 0, 0, "God: True", window);
						}
						else
						{
							draw_text(0, 0, 0, "", window);
						}

						for (const auto& bullet : boss.getBullets())
						{
							if (frog.get_rect().intersects(bullet.getBounds()))
							{
								frog.set_dead();
							}
						}
						for(auto it = coins.begin();it != coins.end();)
						{
							if(frog.get_rect().intersects(it->getBounds())){
								it = coins.erase(it);
								conir += 1;
							}
							else{
								++it;
							}
						}
						
							
						draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Time: " + std::to_string(static_cast<unsigned short>(floor(timer / 64.f))), window);
						draw_text(0, 112, CELL_SIZE * MAP_HEIGHT, "Coin: " + std::to_string(conir), window);
					}
				}

				window.display();
			}
		}
	}

	return 0;
}
