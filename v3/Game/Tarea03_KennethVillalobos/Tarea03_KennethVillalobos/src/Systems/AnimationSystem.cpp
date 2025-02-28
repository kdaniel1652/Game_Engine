// Copyright 2024 Kenneth Villalobos

#include "AnimationSystem.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.H>

AnimationSystem::AnimationSystem() {
  this->requireComponent<AnimationComponent>();
  this->requireComponent<SpriteComponent>();
}

void AnimationSystem::update() {
  for (auto entity : this->getSystemEntities()) {
    auto& animation = entity.getComponent<AnimationComponent>();
    auto& sprite = entity.getComponent<SpriteComponent>();

    animation.currentFrame = ((SDL_GetTicks() - animation.startTime) *
      animation.frameSpeedRate / 1000) % animation.numberFrames;

    sprite.srcRect.x = animation.currentFrame * sprite.width;
  }
}
