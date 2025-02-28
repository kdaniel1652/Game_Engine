// Copyright 2024, Kenneth Villalobos

#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H

#include "../EventManager/Event.h"

class GameOverEvent : public Event {
public:
  GameOverEvent() = default;
};

#endif  // GAMEOVEREVENT_H