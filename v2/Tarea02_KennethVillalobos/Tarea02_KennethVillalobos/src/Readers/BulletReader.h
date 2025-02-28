// Copyright 2024, Kenneth Villalobos

#ifndef BULLETREADER_H
#define BULLETREADER_H

#include <string>

#include "../ECS/ECS.h"
#include "Reader.h"

class BulletReader : Reader {
protected:
  std::string label;
  int speed;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->label >> this->speed;
  };

public:
  BulletReader() = default;
  virtual ~BulletReader() = default;

  void build(Entity& player, const int bulletWidth, const int bulletHeight) {
    // ASUMPTIONS
    const glm::vec2 bulletScale(1.5, 1.5);
    const std::string cloneAssetLabel("clone_img");
    const int cloneSrcRectX = 0;
    const int cloneSrcRectY = 0;
    const int specialAttackRechargeTime = 10000;
    const int specialAttackDuration = 5000;

    player.addComponent<ProjectileEmitterComponent>(this->label, this->speed,
      bulletWidth, bulletHeight, bulletScale);

    player.addComponent<SpecialAttackComponent>(cloneAssetLabel,
      cloneSrcRectX, cloneSrcRectY, specialAttackRechargeTime,
      specialAttackDuration);
  }
};

#endif  // BULLETREADER_H
