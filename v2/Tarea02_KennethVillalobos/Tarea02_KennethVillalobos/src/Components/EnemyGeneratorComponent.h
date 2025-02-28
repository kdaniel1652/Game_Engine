// Copyright 2024, Kenneth Villalobos

#ifndef ENEMYGENERATORCOMPONENT_H
#define ENEMYGENERATORCOMPONENT_H

#include <glm/glm.hpp>

struct EnemyGeneratorComponent {
public:
  int msToGenerate;
  int msSinceGeneration;

  int minSpeed;
  int maxSpeed;
  
  glm::vec2 enemyScale;

public:
  explicit EnemyGeneratorComponent(const int msToGenerate = 3000,
    const int minSpeed = 1, int maxSpeed = 100,
    const glm::vec2& enemyScale = glm::vec2(1, 1))
    : msToGenerate(msToGenerate),
    msSinceGeneration(0),
    minSpeed(minSpeed),
    maxSpeed(maxSpeed),
    enemyScale(enemyScale) {
  };
};

#endif  // ENEMYGENERATORCOMPONENT_H
