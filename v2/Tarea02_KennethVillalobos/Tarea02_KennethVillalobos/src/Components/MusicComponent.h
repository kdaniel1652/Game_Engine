// Copyright 2024, Kenneth Villalobos

#ifndef MUSICCOMPONENT_H
#define MUSICCOMPONENT_H

#include <string>

struct MusicComponent {
public:
  std::string assetId;
  int volume;
  bool isPlaying;

public:
  explicit MusicComponent(const std::string& assetId = "",
    const int volume = 0, bool isPlaying = false)
    : assetId(assetId),
    volume(volume),
    isPlaying(isPlaying) {
  };
};

#endif  // MUSICCOMPONENT_H
