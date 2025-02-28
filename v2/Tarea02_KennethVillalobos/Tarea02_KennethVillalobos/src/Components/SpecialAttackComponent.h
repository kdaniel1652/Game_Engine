// Copyright 2024, Kenneth Villalobos

#ifndef SPECIALATTACKCOMPONENT_H
#define SPECIALATTACKCOMPONENT_H

#include <SDL.h>
#include <string>

#include "../ECS/ECS.h"

struct SpecialAttackComponent {
public:
  std::string cloneAssetId;
  SDL_Rect srcRect;
  int msToBeAvailable;
  int msSinceLastUsed;
  int msDuration;
  int msSinceActivated;
  Entity clone;

public:
  explicit SpecialAttackComponent(const std::string& cloneAssetId = "",
    const int srcRectX = -1, const int srcRectY = -1,
    const int msToBeAvailable = 10000, const int msDuration = 5000,
    const Entity& clone = Entity(0))
    : cloneAssetId(cloneAssetId),
    srcRect({srcRectX, srcRectY}),
    msToBeAvailable(msToBeAvailable),
    msSinceLastUsed(0),
    msDuration(msDuration),
    msSinceActivated(0),
    clone(clone) {
  }
};

#endif  // SPECIALATTACKCOMPONENT_H
