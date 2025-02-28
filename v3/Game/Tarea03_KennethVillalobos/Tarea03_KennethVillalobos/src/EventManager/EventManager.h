// Copyright 2024 Kenneth Villalobos

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Event.h"
#include <list>
#include <map>
#include <memory>
#include <typeindex>

class IEventCallback {
private:
  virtual void call(Event& event) = 0;

public:
  ~IEventCallback() = default;
  void execute(Event& event);
};

template<typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
  typedef void (TOwner::*CallbackFunction)(TEvent&);

private:
  TOwner* owner;
  CallbackFunction function;

  virtual void call(Event& event) override {
    std::invoke(function, owner, static_cast<TEvent&>(event));
  }

public:
  EventCallback(TOwner* owner, CallbackFunction function)
  : owner(owner),
  function(function) {
  }

  virtual ~EventCallback() = default;
};

typedef std::list<std::shared_ptr<IEventCallback>> HandlerList;

class EventManager {
private:
  std::map<std::type_index, std::shared_ptr<HandlerList>> subscribers;


public:
  EventManager() = default;
  ~EventManager() = default;

  void clear();
  
  template<typename TOwner, typename TEvent>
  void subscribeToEvent(TOwner* owner,
    void (TOwner::* callbackFunction)(TEvent&)) {
    if (!this->subscribers[typeid(TEvent)].get()) {
      this->subscribers[typeid(TEvent)] = std::make_shared<HandlerList>();
    }

    auto subscriber = std::make_shared<EventCallback<TOwner, TEvent>>(owner,
      callbackFunction);

    this->subscribers[typeid(TEvent)]->push_back(subscriber);
  }

  template<typename TEvent, typename ...TArgs>
  void emitEvent(TArgs&& ...args) {
    auto handler = this->subscribers[typeid(TEvent)].get();
    if (handler) {
      for (auto it = handler->begin(); it != handler->end(); ++it) {
        auto subscriber = *it;
        TEvent event(std::forward<TArgs>(args)...);
        subscriber->execute(event);
      }
    }
  }
};

#endif  // EVENTMANAGER_H
