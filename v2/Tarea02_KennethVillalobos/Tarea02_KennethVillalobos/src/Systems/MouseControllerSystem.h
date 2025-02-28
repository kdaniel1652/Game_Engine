// Copyright 2024, Kenneth Villalobos

#ifndef MOUSECONTROLLERSYSTEM_H
#define MOUSECONTROLLERSYSTEM_H

#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseMotionEvent.h"

class MouseControllerSystem : public System {
public:
  MouseControllerSystem();

  void subscribeToMouseMotionEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onMouseMotionEvent(MouseMotionEvent& event);
};

#endif  // MOUSECONTROLLERSYSTEM_H
