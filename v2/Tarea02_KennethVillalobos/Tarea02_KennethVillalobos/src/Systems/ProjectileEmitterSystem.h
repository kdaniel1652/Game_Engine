// Copyright 2024, Kenneth Villalobos

#ifndef PROJECTILEEMITTERSYSTEM_H
#define PROJECTILEEMITTERSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseClickEvent.h"

class ProjectileEmitterSystem : public System {
public:
  ProjectileEmitterSystem();

  void subscribeToMouseClickEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onMouseClickEvent(MouseClickEvent& event);
};

#endif  // PROJECTILEEMITTERSYSTEM_H
