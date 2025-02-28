// Copyright 2024, Kenneth Villalobos

#ifndef GAMESTATECOMPONENT_H
#define GAMESTATECOMPONENT_H

struct GameStateComponent {
public:
  bool gameOver;
  bool isPaused;
  bool isRunning;
  bool failed;

public:
  explicit GameStateComponent(const bool gameOver = false,
    const bool isPaused = false, const bool isRunning = true,
    const bool failed = false)
    : gameOver(gameOver),
    isPaused(isPaused),
    isRunning(isRunning),
    failed(failed) {
  }
};

#endif  // GAMESTATECOMPONENT_H
