// Copyright 2024, Kenneth Villalobos

#ifndef ENTITYCLEANERSYSTEM_H
#define ENTITYCLEANERSYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/OutOfBoundsEvent.h"

class EntityCleanerSystem : public System {
public:
  EntityCleanerSystem();

  void subscribeToOutOfBoundsEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onOutOfBoundsEvent(OutOfBoundsEvent& event);
};

#endif  // ENTITYCLEANERSYSTEM_H
