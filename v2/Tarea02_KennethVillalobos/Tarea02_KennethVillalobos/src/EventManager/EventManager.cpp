// Copyright 2024, Kenneth Villalobos

#include "EventManager.h"

void IEventCallback::execute(Event& event) {
  this->call(event);
}

void EventManager::clear() {
  this->subscribers.clear();
}
