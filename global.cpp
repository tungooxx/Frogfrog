#include "header\global.h"
#include <SFML\Graphics.hpp>
#include <array> 
#include <chrono>
#include <cmath>
unsigned char CELL_SIZE = 16;
unsigned char CROCODILE_ANIMATION_SPEED = 32;
unsigned char FAST_SPEED = 3;
unsigned char FONT_HEIGHT = 16;
unsigned char FROG_ANIMATION_SPEED = 8;
unsigned char MAP_WIDTH = 16;
unsigned char MAP_HEIGHT = 15;
unsigned char NORMAL_SPEED = 2;
unsigned char SCREEN_RESIZE = 3;
unsigned char SLOW_SPEED = 1;
unsigned char TOTAL_LEVELS = 100;
unsigned char TURTLE_ANIMATION_SPEED = 16;
unsigned char TURTLE_DIVING_SPEED = 32;
unsigned short TIMER_INITIAL_DURATION = 4096;
unsigned short TIME_REDUCTION = 512;

std::chrono::microseconds FRAME_DURATION(16667);
