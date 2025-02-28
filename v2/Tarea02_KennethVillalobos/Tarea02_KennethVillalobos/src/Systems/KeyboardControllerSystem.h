// Copyright 2024, Kenneth Villalobos

#ifndef KEYBOARDCONTROLLERSYSTEM_H
#define KEYBOARDCONTROLLERSYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/KeyboardEvent.h"
#include "../Events/GameUnPausedEvent.h"

class KeyboardControllerSystem : public System {
public:
  KeyboardControllerSystem();

  void subscribeToKeyboardEvents(std::shared_ptr<EventManager>& eventManager);
  void subscribeToGameUnPausedEvents(
    std::shared_ptr<EventManager>& eventManager);

  void onKeyboardEvent(KeyboardEvent& event);
  void onGameUnPausedEvent(GameUnPausedEvent& event);
};

#endif  // KEYBOARDCONTROLLERSYSTEM_H
