// Copyright 2024, Kenneth Villalobos

#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/EnemyKilledEvent.h"

class ScoreSystem : public System {
public:
  ScoreSystem();

  void subscribeToEnemyKilledEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onEnemyKilledEvent(EnemyKilledEvent& event);
};

#endif  // SCORESYSTEM_H
