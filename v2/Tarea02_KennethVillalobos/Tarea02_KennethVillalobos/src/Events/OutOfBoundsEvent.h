// Copyright 2024, Kenneth Villalobos

#ifndef OUTOFBOUNDSEVENT_H
#define OUTOFBOUNDSEVENT_H

#include "../ECS/ECS.h"
#include "../EventManager/Event.h"
#include "../EventManager/EventManager.h"

class OutOfBoundsEvent : public Event {
public:
  Entity outEntity;
  std::shared_ptr<EventManager>& eventManager;

  OutOfBoundsEvent(Entity& outEntity,
    std::shared_ptr<EventManager>& eventManager)
    : outEntity(outEntity),
    eventManager(eventManager) {
  }
};

#endif  // OUTOFBOUNDSEVENT_H