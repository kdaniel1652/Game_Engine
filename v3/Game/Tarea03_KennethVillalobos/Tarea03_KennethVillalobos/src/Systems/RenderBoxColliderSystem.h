// Copyright 2024 Kenneth Villalobos

#ifndef RENDERBOXCOLLIDERSYSTEM_H
#define RENDERBOXCOLLIDERSYSTEM_H

#include "../ECS/ECS.h"
#include <SDL.h>

class RenderBoxColliderSystem : public System {
public:
  RenderBoxColliderSystem();

  void update(SDL_Renderer* renderer, const SDL_Rect& camera);
};

#endif  // RENDERBOXCOLLIDERSYSTEM_H
