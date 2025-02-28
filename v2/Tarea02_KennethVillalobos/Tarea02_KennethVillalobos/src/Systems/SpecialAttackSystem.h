// Copyright 2024, Kenneth Villalobos

#ifndef SPCECIALATTACKSYSTEM_H
#define SPCECIALATTACKSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseClickEvent.h"

class SpecialAttackSystem : public System {
public:
  SpecialAttackSystem();

  void update(const int msSinceLastUpdate);

  void subscribeToMouseClickEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onMouseClickEvent(MouseClickEvent& event);
};

#endif  // SPCECIALATTACKSYSTEM_H
