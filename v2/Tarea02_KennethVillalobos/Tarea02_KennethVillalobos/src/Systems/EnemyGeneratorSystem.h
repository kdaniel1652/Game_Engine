// Copyright 2024, Kenneth Villalobos

#ifndef ENEMYGENERATORSYSTEM_H
#define ENEMYGENERATORSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/GameOverEvent.h"
#include "../Utils/RandomGenerator.h"

class EnemyGeneratorSystem : public System {
public:
  EnemyGeneratorSystem();

  void update(const int xLimit, const int yLimit,
    const int msSinceLastUpdate);
};

#endif  // ENEMYGENERATORSYSTEM_H
