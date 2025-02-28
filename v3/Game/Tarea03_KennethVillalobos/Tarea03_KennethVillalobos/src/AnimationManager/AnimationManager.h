// Copyright 2024 Kenneth Villalobos

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <map>
#include <string>

struct AnimationData {
  std::string spriteLabel;
  int width;
  int height;
  int numberFrames;
  int currentFrame;
  int frameSpeedRate;

  AnimationData(const std::string& spriteLabel = std::string(""),
    const int width = 0, const int height = 0, const int numberFrames = 1,
    const int currentFrame = 1, const int frameSpeedRate = 1);
};

typedef std::map<std::string, AnimationData> ActionAnimationMap;

class AnimationManager { 
private:
  std::map<std::string, ActionAnimationMap> animations;

public:
  AnimationManager() = default;
  ~AnimationManager() = default;

  inline void clear() {
    this->animations.clear();
  }

  void addAnimation(const std::string& entityType, const std::string& action,
    const std::string& spriteLabel, const int width, const int height,
    const int numberFrames, const int currentFrame, const int frameSpeedRate);

  bool hasAnimationData(const std::string& entityType,
    const std::string& action) const;

  inline bool hasEntity(const std::string& entityType) const {
    return this->animations.find(entityType) != this->animations.end();
  }

  inline AnimationData getAnimationData(const std::string& entityType,
    const std::string& action) const {
    return this->animations.at(entityType).at(action);
  }
};

#endif  // ANIMATIONMANAGER_H
