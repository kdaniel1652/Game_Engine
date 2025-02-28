// Copyright 2024, Kenneth Villalobos

#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL.h>

#include <glm/glm.hpp>
#include <string>

struct ProjectileEmitterComponent {
public:
  std::string assetId;
  float speed;
  int projectileWidth;
  int projectileHeight;
  glm::vec2 projectileScale;
  SDL_Rect srcRect;

public:
  explicit ProjectileEmitterComponent(
    const std::string& assetId = "",
    const float speed = 10.0f, const int projectileWidth = 0,
    const int projectileHeight = 0,
    const glm::vec2& projectileScale = glm::vec2(),
    const int srcRectX = -1, const int srcRectY = -1)
    : assetId(assetId),
    speed(speed),
    projectileWidth(projectileWidth),
    projectileHeight(projectileHeight),
    projectileScale(projectileScale),
    srcRect({srcRectX, srcRectY}) {
  };
};

#endif  // PROJECTILEEMITTERCOMPONENT_H
