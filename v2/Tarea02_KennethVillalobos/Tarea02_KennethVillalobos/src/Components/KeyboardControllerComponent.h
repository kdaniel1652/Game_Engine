// Copyright 2024, Kenneth Villalobos

#ifndef KEYBOARDCONTROLLERCOMPONENT_H
#define KEYBOARDCONTROLLERCOMPONENT_H

struct KeyboardControllerComponent {
public:
  bool up;
  bool right;
  bool down;
  bool left;

public:
  explicit KeyboardControllerComponent(const bool up = false,
    const bool right = false, const bool down = false,
    const bool left = false)
    : up(up),
    right(right),
    down(down),
    left(left) {
  };
};

#endif  // KEYBOARDCONTROLLERCOMPONENT_H
