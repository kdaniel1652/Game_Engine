// Copyright 2024, Kenneth Villalobos

#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <string>
#include <vector>

struct SoundComponent {
public:
  std::vector<std::string> assetIds;
  std::vector<int> volumes;
  size_t timesMustBePlayed;

public:
  explicit SoundComponent(const std::vector<std::string> assetIds =
    std::vector<std::string>(0),
    const std::vector<int> volumes = std::vector<int>(0),
    const size_t timesMustBePlayed = 0)
    : assetIds(assetIds),
    volumes(volumes),
    timesMustBePlayed(timesMustBePlayed) {
  };
};

#endif  // SOUNDCOMPONENT_H
