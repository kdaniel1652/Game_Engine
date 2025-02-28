// Copyright 2024 Kenneth Villalobos

#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "../EventManager/Event.h"

class CollisionEvent : public Event {
public:
  Entity first;
  Entity second;

  CollisionEvent(Entity& first, Entity& second)
  : first(first),
  second(second) {
  }
};

#endif  // COLLISIONEVENT_H
