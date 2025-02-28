// Copyright 2024, Kenneth Villalobos

#ifndef RESPAWNSYSTEM_H
#define RESPAWNSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/EntityDefeatedEvent.h"

class RespawnSystem : public System {
public:
  RespawnSystem();

  void update(std::shared_ptr<EventManager>& eventManager,
    const int msSinceLastUpdate);
  void subscribeToEntityDefeatedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onEntityDefeatedEvent(EntityDefeatedEvent& event);
};

#endif  // RESPAWNSYSTEM_H
