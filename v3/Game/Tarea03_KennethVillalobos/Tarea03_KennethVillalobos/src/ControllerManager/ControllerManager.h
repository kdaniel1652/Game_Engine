// Copyright 2024 Kenneth Villalobos

#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <map>
#include <SDL.h>
#include <string>

class ControllerManager {
private:
  std::map<SDL_Keycode, std::string> keyActionMap;
  std::map<Uint8, std::string> buttonActionMap;
  std::map<std::string, bool> actionActiveMap;

  int mouseX = 0;
  int mouseY = 0;
  bool mousePressed = false;

public:
  ControllerManager() = default;
  ~ControllerManager() = default;

  void clear();

  void mapKeyAction(const SDL_Keycode key, const std::string& action);
  inline bool isKeyMapped(const SDL_Keycode key) const {
    return this->keyActionMap.find(key) != this->keyActionMap.cend();
  }

  void mapButtonAction(const Uint8 button, const std::string& action);
  inline bool isButtonMapped(const Uint8 button) const {
    return this->buttonActionMap.find(button) != this->buttonActionMap.cend();
  }

  std::string getAction(const SDL_Keycode key) const;
  std::string getAction(const Uint8 button) const;

  bool isActionMapped(const std::string& action) const;
  bool getActionState(const std::string& action) const;

  inline void changeActionState(const std::string& action,
    const bool activation) {
    this->actionActiveMap[action] = activation;
  }

  void changeMousePosition(const int x, const int y);
  inline void changeMouseState(const bool pressed) {
    this->mousePressed = pressed;
  }
};

#endif  // CONTROLLERMANAGER_H
