// Copyright 2024 Kenneth Villalobos

#include <algorithm>
#include "ControllerManager.h"

void ControllerManager::clear() {
  this->keyActionMap.clear();
  this->buttonActionMap.clear();
  this->actionActiveMap.clear();

  this->mouseX = 0;
  this->mouseY = 0;
  this->mousePressed = false;
}

void ControllerManager::mapKeyAction(const SDL_Keycode key,
  const std::string& action) {
  this->keyActionMap[key] = action;
  this->actionActiveMap[action] = false;
}

void ControllerManager::mapButtonAction(const Uint8 button,
  const std::string& action) {
  this->buttonActionMap[button] = action;
  this->actionActiveMap[action] = false;
}

std::string ControllerManager::getAction(const SDL_Keycode key) const {
  const auto it = this->keyActionMap.find(key);
  return (it != this->keyActionMap.cend()) ?
    it->second : std::string("");
}

std::string ControllerManager::getAction(const Uint8 button) const {
  const auto it = this->buttonActionMap.find(button);
  return (it != this->buttonActionMap.cend()) ?
    it->second : std::string("");
}

bool ControllerManager::isActionMapped(const std::string& action) const {
  bool mapped = std::any_of(
    this->keyActionMap.begin(),
    this->keyActionMap.end(),
    [&action](const std::pair<int, std::string>& element) {
      return element.second == action;
    });

  if (!mapped) {
    mapped = std::any_of(
      this->buttonActionMap.begin(),
      this->buttonActionMap.end(),
      [&action](const std::pair<int, std::string>& element) {
        return element.second == action;
    });
  }

  return mapped;
}

bool ControllerManager::getActionState(const std::string& action) const {
  const auto it = this->actionActiveMap.find(action);
  return (it != this->actionActiveMap.cend()) ?
    it->second : false;
}

void ControllerManager::changeMousePosition(const int x, const int y) {
  this->mouseX = x;
  this->mouseY = y;
}
