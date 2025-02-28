// Copyright 2024 Kenneth Villalobos

#ifndef OVERLAPSYSTEM_H
#define OVERLAPSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"
#include <memory>

class OverlapSystem : public System {
public:
  OverlapSystem();

  void subscribeToCollideEvents(std::shared_ptr<EventManager>& eventManager);
  void onCollisionEvent(CollisionEvent& event);

private:
  void avoidOverlap(Entity& eDynamic, Entity& eStatic);
};

#endif  // OVERLAPSYSTEM_H
