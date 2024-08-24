#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <array>
#include <chrono>
#include <cmath>

extern unsigned char CELL_SIZE;
extern unsigned char CROCODILE_ANIMATION_SPEED;
extern unsigned char FAST_SPEED;
extern unsigned char FONT_HEIGHT;
extern unsigned char FROG_ANIMATION_SPEED;
extern unsigned char MAP_WIDTH;
extern unsigned char MAP_HEIGHT;
extern unsigned char NORMAL_SPEED;
extern unsigned char SCREEN_RESIZE;
extern unsigned char SLOW_SPEED;
extern unsigned char TOTAL_LEVELS;
extern unsigned char TURTLE_ANIMATION_SPEED;
extern unsigned char TURTLE_DIVING_SPEED;

extern unsigned short TIMER_INITIAL_DURATION;
extern unsigned short TIME_REDUCTION;

extern std::chrono::microseconds FRAME_DURATION;

#endif // GLOBAL_H
