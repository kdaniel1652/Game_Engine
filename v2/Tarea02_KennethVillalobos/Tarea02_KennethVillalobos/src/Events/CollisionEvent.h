// Copyright 2024, Kenneth Villalobos

#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "../EventManager/Event.h"
#include "../EventManager/EventManager.h"

class CollisionEvent : public Event {
public:
  Entity first;
  Entity second;
  std::shared_ptr<EventManager>& eventManager;

  CollisionEvent(Entity& first, Entity& second,
    std::shared_ptr<EventManager>& eventManager)
    : first(first),
    second(second),
    eventManager(eventManager) {
  }
};

#endif  // COLLISIONEVENT_H