// Copyright 2024, Kenneth Villalobos

#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <SDL.h>

#include "../EventManager/Event.h"

class KeyboardEvent : public Event {
public:
  bool keyDown;
  SDL_Keycode keycode;

  KeyboardEvent(bool keyDown = false, SDL_Keycode keycode = SDLK_UNKNOWN)
    :keyDown(keyDown),
    keycode(keycode) {
  }
};

#endif  // KEYBOARDEVENT_H
