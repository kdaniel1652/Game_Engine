// Copyright 2024 Kenneth Villalobos

#include "AnimationManager.h"

AnimationData::AnimationData(const std::string& spriteLabel,
  const int width, const int height, const int numberFrames,
  const int currentFrame, const int frameSpeedRate)
  : spriteLabel(spriteLabel),
  width(width),
  height(height),
  numberFrames(numberFrames),
  currentFrame(currentFrame),
  frameSpeedRate(frameSpeedRate) {
}

void AnimationManager::addAnimation(const std::string& entityType,
  const std::string& action, const std::string& spriteLabel, const int width,
  const int height, const int numberFrames, const int currentFrame,
  const int frameSpeedRate) {
  AnimationData animationData = AnimationData(spriteLabel, width, height,
    numberFrames, currentFrame, frameSpeedRate);
  this->animations[entityType][action] = animationData;
}

bool AnimationManager::hasAnimationData(const std::string& entityType,
  const std::string& action) const {
  bool hasAnimation = false;

  if (this->hasEntity(entityType)) {
    hasAnimation = (this->animations.at(entityType).find(action) !=
      this->animations.at(entityType).end());
  }

  return hasAnimation;
}
