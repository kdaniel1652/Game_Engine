// Copyright 2024, Kenneth Villalobos

#ifndef ENTITYDEFEATEDVENT_H
#define ENTITYDEFEATEDVENT_H

#include "../ECS/ECS.h"
#include "../EventManager/Event.h"

class EntityDefeatedEvent : public Event {
public:
  Entity defeatedEntity;

  EntityDefeatedEvent(Entity& defeatedEntity)
    : defeatedEntity(defeatedEntity) {
  }
};

#endif  // ENTITYDEFEATEDVENT_H