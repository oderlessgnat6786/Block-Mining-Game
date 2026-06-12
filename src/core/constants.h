
#pragma once

#include <string>

inline constexpr int blockRadius = 5; //10
inline constexpr int TILE_SIZE = 121;
inline constexpr unsigned WINDOW_WIDTH = 1280; //1024x1024
inline constexpr unsigned WINDOW_HEIGHT = 1080;
inline constexpr float GRAVITY = 16.53f*TILE_SIZE;
inline constexpr float FALL_SPEED = 12.4f*TILE_SIZE;
inline constexpr float safe_step = 30;
inline constexpr std::string gameTitle = "Boannt";
