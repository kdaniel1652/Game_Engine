// Copyright 2024 Kenneth Villalobos

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"

class AnimationSystem : public System {
public:
  AnimationSystem();

  void update();
};

#endif  // ANIMATIONSYSTEM_H
