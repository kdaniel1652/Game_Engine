// Copyright 2024 Kenneth Villalobos

#include "../Bindings/LuaBindings.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ScriptComponent.h"
#include <glm/glm.hpp>
#include "ScriptSystem.h"
#include <SDL.h>
#include "../Systems/OverlapSystem.h"

ScriptSystem::ScriptSystem() {
  this->requireComponent<ScriptComponent>();
}

void ScriptSystem::createLuaBindings(sol::state& lua) {
  this->createLuaClasses(lua);

  lua.set_function("is_action_active", &isActionActive);
  lua.set_function("get_ticks", &getTicks);
  lua.set_function("str_contains", &stringContains);
  lua.set_function("play_sound", &playSound);
  lua.set_function("change_animation", &changeAnimation);
  lua.set_function("check_collision_dir",
    &checkCollisionDirection);
  lua.set_function("change_scene", &changeScene);
}

void ScriptSystem::awake(sol::state& lua, std::set<Entity>& entities) {
  for (auto entity : entities) {
    if (entity.hasComponent<ScriptComponent>()) {
      const auto& script = entity.getComponent<ScriptComponent>();
      if (script.awake != sol::nil) {
        lua["this"] = entity;
        script.awake();
      }
    }
  }
}

void ScriptSystem::update(sol::state& lua) {
  for (auto entity : this->getSystemEntities()) {
    const auto& script = entity.getComponent<ScriptComponent>();
    if (script.update != sol::nil) {
      lua["this"] = entity;
      script.update();
    }
  }
}

void ScriptSystem::createLuaClasses(sol::state& lua) {
  lua.new_usertype<glm::vec2>(
    "vec",
    "x", &glm::vec2::x,
    "y", &glm::vec2::y
  );

  lua.new_usertype<SDL_Rect>(
    "rect",
    "x", &SDL_Rect::x,
    "y", &SDL_Rect::y
  );

  lua.new_usertype<Entity>(
    "entity",
    "get_id", &Entity::getId,
    "get_tag", &Entity::getTag,
    "kill", &Entity::kill,
    "has_health", &hasHealth,
    "get_health", &getHealth,
    "get_hit_box", &getHitBox,
    "get_box_collider", &getBoxCollider,
    "get_rigid_body", &getRigidBody,
    "get_sprite", &getSprite,
    "get_transform", &getTransform
  );

  lua.new_usertype<BoxColliderComponent>(
    "collider",
    "width", &BoxColliderComponent::width,
    "height", &BoxColliderComponent::height,
    "offset", &BoxColliderComponent::offset
  );

  lua.new_usertype<HealthComponent>(
    "health",
    "max_health", &HealthComponent::maxHealth,
    "current_health", &HealthComponent::currentHealth
  );

  lua.new_usertype<HitBoxComponent>(
    "hit_box",
    "active", &HitBoxComponent::active,
    "damage", &HitBoxComponent::damage,
    "width", &HitBoxComponent::width,
    "height", &HitBoxComponent::height,
    "offset", &HitBoxComponent::offset
  );

  lua.new_usertype<RigidBodyComponent>(
    "rigid_body",
    "velocity", &RigidBodyComponent::velocity,
    "sum_forces", &RigidBodyComponent::sumForces,
    "on_ground", &RigidBodyComponent::onGround,
    "is_static", &RigidBodyComponent::isStatic
  );

  lua.new_usertype<SpriteComponent>(
    "sprite",
    "width", &SpriteComponent::width,
    "height", &SpriteComponent::height,
    "flip", &SpriteComponent::flip
  );

  lua.new_usertype<TransformComponent>(
    "transform",
    "position", &TransformComponent::position,
    "scale", &TransformComponent::scale
  );
}
