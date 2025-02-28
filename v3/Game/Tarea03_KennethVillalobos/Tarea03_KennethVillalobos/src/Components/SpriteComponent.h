// Copyright 2024 Kenneth Villalobos

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include <string>

struct SpriteComponent {
public:
  std::string assetId;
  int width;
  int height;
  SDL_Rect srcRect;
  bool flip = false;

public:
  SpriteComponent(const std::string& assetId = std:: string(""),
    const int width = 0, const int height = 0, const int srcRectX = 0,
    const int srcRectY = 0)
    : assetId(assetId),
    width(width),
    height(height),
    srcRect({srcRectX, srcRectY, this->width, this->height}) {
  }
};

#endif  // SPRITECOMPONENT_H