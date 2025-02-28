// Copyright 2024, Kenneth Villalobos

#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System {
private:
  void handleEntity(Entity& entity,
    std::shared_ptr<EventManager>& eventManager);

public:
  DamageSystem();

  void subscribeToCollisionEvents(std::shared_ptr<EventManager>& eventManager);
  void onCollisionEvent(CollisionEvent& event);
};

#endif  // DAMAGESYSTEM_H
