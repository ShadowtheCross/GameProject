#include "GameState.h"
#include "Config.h"

GameState* GameState::instance = NULL;
int Config::window_width = 2560;
int Config::window_height = 1440;

int Config::mainPlayerWidth = 10;
int Config::mainPlayerHeight = 30;

float Config::playerVelocity = 0.5f;
float Config::playerHealth = 100.0f;