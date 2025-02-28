// Copyright 2024 Kenneth Villalobos

#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include <SDL.h>

class CameraMovementSystem : public System {
public:
  CameraMovementSystem();

  void update(SDL_Rect& camera);
};

#endif  // CAMERAMOVEMENTSYSTEM_H
