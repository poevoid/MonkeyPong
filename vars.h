#pragma once
#include "Vector.h"

#define FRAME(x) x * 3 + arduboy.currentPlane()
#define MAX_FPS 10
#define SPLASH_TIME 75

int startcounter = SPLASH_TIME;
uint16_t currentPlane;
int offsetX = 0, offsetY = 0;
float intensity = 1.25;

struct Sprite {
  uint8_t x, y;
  uint24_t sprite;
  uint8_t framecount;
  uint8_t currentframe;
  uint8_t framewait;
  int counter;
  bool inc;
};

struct Ball {
  int8_t x, y;
  uint24_t sprite;
  uint8_t framecount;
  uint8_t currentframe;
  uint8_t framewait;
  int counter;
  uint8_t size;
  bool inc;
  bool right;
  bool down;
  bool up;
};

struct Paddle {
  int x, y;
  uint8_t spritey;
  uint24_t sprite;
  uint8_t framecount;
  uint8_t currentframe;
  uint8_t framewait;
  int counter;
  uint8_t height;
  uint8_t width;
  uint8_t score;
};

enum class Screen : uint8_t {
  Splash,
  Title,
  Game,
  Gameover,
  Win
};



Paddle player = { -16, 5, 0, MonkeyIdleEast, 2, 0, 3, 0, 22, 32, 0 };
Paddle oppo = { WIDTH - 16, 5, 0, MonkeyIdleWest, 2, 0, 3, 0, 22, 32, 0 };
Ball ball = { 64, 32, bananaspin, 3, 0, 3, 0, 16, true, false, true, false };
Sprite sprite = { 0, 0, punklogooutlined, 0, 0, 0, 0, true };
Sprite face = { 84 - 16, 16, monkeywin, 1, 0, 16, 0 };
Sprite Abutton = { 0, 0, abutton, 3, 0, 6, 0 };
Sprite Bbutton = { 28, 0, bbutton, 3, 0, 6, 0 };
Screen screen = { Screen::Splash };