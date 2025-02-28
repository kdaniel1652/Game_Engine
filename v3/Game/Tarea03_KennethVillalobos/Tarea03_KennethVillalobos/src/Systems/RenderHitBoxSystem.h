// Copyright 2024 Kenneth Villalobos

#ifndef RENDERHITBOXSYSTEM_H
#define RENDERHITBOXSYSTEM_H

#include "../ECS/ECS.h"
#include <SDL.h>

class RenderHitBoxSystem : public System {
public:
  RenderHitBoxSystem();

  void update(SDL_Renderer* renderer, const SDL_Rect& camera);
};

#endif  // RENDERHITBOXSYSTEM_H
