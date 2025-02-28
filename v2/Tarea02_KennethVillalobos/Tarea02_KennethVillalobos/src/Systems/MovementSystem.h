// Copyright 2024, Kenneth Villalobos

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"

class MovementSystem : public System {
public:
  MovementSystem();

  void update(std::shared_ptr<EventManager>& eventManager,
    const float deltaTime, const int xLimit, const int yLimit);
};

#endif  // MOVEMENTSYSTEM_H
