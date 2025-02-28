// Copyright 2024, Kenneth Villalobos

#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H

#include "../EventManager/Event.h"
#include "../EventManager/EventManager.h"

class MouseClickEvent : public Event {
public:
  bool buttonDown;
  Uint8 button;
  std::shared_ptr<EventManager>& eventManager;

  MouseClickEvent(bool buttonDown, Uint8 button,
    std::shared_ptr<EventManager>& eventManager)
    :buttonDown(buttonDown),
    button(button),
    eventManager(eventManager) {
  }
};

#endif  // MOUSECLICKEVENT_H
