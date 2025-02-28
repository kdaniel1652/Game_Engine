// Copyright 2024, Kenneth Villalobos

#ifndef MOUSEMOTIONEVENT_H
#define MOUSEMOTIONEVENT_H

#include <glm/glm.hpp>

#include "../EventManager/Event.h"

class MouseMotionEvent : public Event {
public:
  glm::vec2 position;

  MouseMotionEvent(const glm::vec2 position = glm::vec2(0))
    : position(position) {
  }
};

#endif  // MOUSEMOTIONEVENT_H