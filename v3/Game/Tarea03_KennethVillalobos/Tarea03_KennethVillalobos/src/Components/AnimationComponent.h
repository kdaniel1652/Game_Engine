// Copyright 2024 Kenneth Villalobos

#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL.h>

struct AnimationComponent {
public:
  int numberFrames;
  int currentFrame;
  int frameSpeedRate;
  int startTime;  

public:
  AnimationComponent(const int numberFrames = 1,
    const int currentFrame = 1,
    const int frameSpeedRate = 1)
    : numberFrames(numberFrames),
    currentFrame(currentFrame),
    frameSpeedRate(frameSpeedRate),
    startTime(SDL_GetTicks()) {
  };
};

#endif  // ANIMATIONCOMPONENT_H
