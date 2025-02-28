// Copyright 2024 Kenneth Villalobos

#ifndef COMMON_H
#define COMMON_H

#include <string>

namespace constants {
  const float GRAVITY = 9.8f;
  const float AIR_DENSITY = 1.225f;
  const float DRAG_COEFFICIENT = 0.47;
  const float PIXELS_PER_METER = 64;


  const int FPS = 60;
  const int MILISECS_PER_FRAME = 1000 / FPS;
  const float TIME_PER_STEP = 1.0f / 60;
  const size_t MAX_STEPS = 5;

  const std::string GAME_NAME = std::string("Game Engine");
  const std::string TILESET_ID = std::string("terrain_img");
}

#endif  // COMMON_H