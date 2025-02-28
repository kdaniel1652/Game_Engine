// Copyright 2024, Kenneth Villalobos

#include "game/Game.h"

// main (It uses params to ensure normal behavior with SDL library)
int main(int  argc, char* argv[]) {
  // Create a game controller
  gameDev::Game game;
  // Run the controller
  game.run();
  return 0;
}
