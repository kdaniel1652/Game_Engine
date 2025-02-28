// Copyright 2024 Kenneth Villalobos

#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <deque>
#include <map>
#include <memory>
#include <limits>
#include <list>
#include <set>
#include <typeindex>
#include "../Util/Pool.h"
#include <unordered_map>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent {
protected:
  inline static size_t nextId;
};

template<typename TComponent>
class Component : public IComponent {
public:
  static size_t getId() {
    static size_t id = IComponent::nextId++;
    return id;
  }
};

class Entity {
private:
  size_t id = 0;

public:
  class ECSManager* manager = nullptr;

  Entity(const size_t id = std::numeric_limits<size_t>::max());
  Entity(const Entity& other) = default;
  ~Entity() = default;

  inline size_t getId() const {
    return this->id;
  }
  inline bool valid() const {
    return this->id != std::numeric_limits<size_t>::max();
  }
  void kill();

  Entity& operator=(const Entity& other) = default;

  bool operator==(const Entity& other) const;
  bool operator!=(const Entity& other) const;
  bool operator>(const Entity& other) const;
  bool operator<(const Entity& other) const;

  template<typename TComponent, typename ...TArgs>
  void addComponent(TArgs&& ...args);

  template<typename TComponent>
  void changeComponentState(const bool activate);

  template<typename TComponent>
  bool hasComponent() const;
  template<typename TComponent>
  TComponent& getComponent() const;

  void addTag(const std::string& tag);
  std::string getTag() const;
};

class System {
private:
  Signature componentSignature;
  std::vector<Entity> entities;

public:
  System() = default;
  ~System() = default;

  void addEntityToSystem(Entity& entity);
  void removeEntityFromSystem(Entity& entity);

  std::vector<Entity> getSystemEntities() const;
  const Signature& getComponentSignature() const;

  template<typename TComponent>
  void requireComponent() {
    const size_t componentId = Component<TComponent>::getId();
    componentSignature.set(componentId);
  };
};

class ECSManager {
private:
  size_t numEntities = 0;
  std::vector<std::shared_ptr<IPool>> componentPools;
  std::vector<Signature> entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;

  std::deque<size_t> freeIds;

  std::map<int, std::pair<std::string, Entity>> entityTag;
  std::map<std::string, std::list<int>> entityGroups;

public:
  void update();

  Entity createEntity();
  void killEntity(Entity& entity);
  std::set<Entity>& getEntitiesToBeAdded();

  template<typename TComponent, typename ...TArgs>
  void addComponent(Entity& entity, TArgs&& ...args) {
    const size_t componentId = Component<TComponent>::getId();
    const size_t entityId = entity.getId();

    if (componentId >= this->componentPools.size()) {
      this->componentPools.resize(componentId + 1, nullptr);
    }

    if (!this->componentPools[componentId]) {
      this->componentPools[componentId] =
        std::make_shared<Pool<TComponent>>();
    }

    std::shared_ptr<Pool<TComponent>> componentPool =
      std::static_pointer_cast<Pool<TComponent>>(
        this->componentPools[componentId]);

    if (entityId >= componentPool->getSize()) {
      componentPool->resize(entityId + 1);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);
    componentPool->set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
  }
  template<typename TComponent>
  void changeComponentState(Entity& entity, const bool activate) {
    const size_t componentId = Component<TComponent>::getId();
    const size_t entityId = entity.getId();

    this->entityComponentSignatures[entityId].set(componentId, activate);
  }
  template<typename TComponent>
  bool hasComponent(const Entity& entity) const {
    const size_t componentId = Component<TComponent>::getId();
    const size_t entityId = entity.getId();

    return this->entityComponentSignatures[entityId].test(componentId);
  }
  template<typename TComponent>
  TComponent& getComponent(const Entity& entity) const {
    const size_t componentId = Component<TComponent>::getId();
    const size_t entityId = entity.getId();

    std::shared_ptr<Pool<TComponent>> componentPool =
      std::static_pointer_cast<Pool<TComponent>>(
        this->componentPools[componentId]);

    return componentPool->get(entityId);
  }

  template<typename TSystem, typename ...TArgs>
  void addSystem(TArgs&& ...args) {
    std::shared_ptr<System> newSsystem =
      std::make_shared<TSystem>(std::forward<TArgs>(args)...);

    this->systems.insert(std::make_pair(
      std::type_index(typeid(TSystem)), newSsystem));
  }
  template<typename TSystem>
  void removeSystem() {
    systems.erase(std::type_index(typeid(TSystem)));
  }
  template<typename TSystem>
  bool hasSystem() const {
    auto it = this->systems.find(std::type_index(typeid(TSystem)));
    return it != this->systems.end();
  }
  template<typename TSystem>
  TSystem& getSystem() const {
    auto it = this->systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(it->second));
  }

  void addEntityToSystem(Entity& entity);
  void removeEntityFromSystem(Entity& entity);
  Entity getEntity(const int id);
  void clean();
  void destroy();

  void addTagToEntity(Entity& entity, const std::string& tag);
  void setTagToEntity(Entity& entity, const std::string& tag);
  std::string getTagFromEntity(const Entity& entity) const ;
  void clearTags();
};

template<typename TComponent, typename ...TArgs>
void Entity::addComponent(TArgs&& ...args) {
  this->manager->addComponent<TComponent>(
    *this, std::forward<TArgs>(args)...);
}
template<typename TComponent>
void Entity::changeComponentState(const bool activate) {
  this->manager->changeComponentState<TComponent>(*this, activate);
}
template<typename TComponent>
bool Entity::hasComponent() const {
  return this->manager->hasComponent<TComponent>(*this);
}
template<typename TComponent>
TComponent& Entity::getComponent() const {
  return this->manager->getComponent<TComponent>(*this);
}

#endif  // ECS_H
