// Copyright 2024, Kenneth Villalobos

#ifndef PAUSECOMPONENT_H
#define PAUSECOMPONENT_H

struct PauseComponent {
public:
  bool mustBeRender;

public:
  explicit PauseComponent(const bool mustBeRender = false)
    : mustBeRender(mustBeRender) {
  };
};

#endif  // PAUSECOMPONENT_H
