// Copyright 2024, Kenneth Villalobos

#ifndef ENEMYKILLEDEVENT_H
#define ENEMYKILLEDEVENT_H

#include "../ECS/ECS.h"
#include "../EventManager/Event.h"

class EnemyKilledEvent : public Event {
public:
  Entity diyingEntity;

  EnemyKilledEvent(Entity& diyingEntity)
    : diyingEntity(diyingEntity) {
  }
};

#endif  // ENEMYKILLEDEVENT_H