// Copyright 2024 Kenneth Villalobos

#include "./Game/Game.h"

int main(int argc, char* argv[]) {
  try {
    Game& game = Game::getInstance();
    game.run();
  }
  catch (const sol::error& e) {
    std::cerr << "Sol Lua error occurred: " << e.what() << std::endl;
  }
  catch (const std::exception& e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Unknown exception occurred." << std::endl;
  }

  return 0;
}