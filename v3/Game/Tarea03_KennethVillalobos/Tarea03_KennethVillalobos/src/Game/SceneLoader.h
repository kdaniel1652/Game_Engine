// Copyright 2024 Kenneth Villalobos

#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "../AnimationManager/AnimationManager.h"
#include "../AssetStore/AssetStore.h"
#include "../ControllerManager/ControllerManager.h"
#include "../ECS/ECS.h"
#include <map>
#include <memory>
#include "../MusicManager/MusicManager.h"
#include <SDL.h>
#include <sol/sol.hpp>
#include "../SoundManager/SoundManager.h"
#include <string>
#include <tinyxml2/tinyxml2.h>

class SceneLoader {
private:
  std::map<std::string, std::string> scenePaths;

public:
  SceneLoader() = default;
  ~SceneLoader() = default;

private:
  void loadScenes(const sol::table& scenes);

  void loadAssets(const sol::table& assets,
    std::shared_ptr<AssetStore>& assetStore,
    SDL_Renderer* renderer);

  void loadInputActions(const sol::table& inputActions,
    std::shared_ptr<ControllerManager>& controllerManager);

  void loadSounds(const sol::table& sounds,
    std::shared_ptr<SoundManager>& soundManager);

  void loadAnimations(const sol::table& animations,
    std::shared_ptr<AnimationManager>& animationManager);

  void loadMap(const sol::table& map,
    std::shared_ptr<ECSManager>& manager,
    std::shared_ptr<AssetStore>& assetStore);
  void loadMapSprites(std::shared_ptr<ECSManager>& manager,
    tinyxml2::XMLElement* layer, const int tileWidth,
    const int tileHeight, const int levelWidth, const int levelHeight,
    const int tilesInWidth);
  void loadMapColliders(std::shared_ptr<ECSManager>& manager,
    tinyxml2::XMLElement* object);

  void loadEntities(const sol::table& entities, sol::state& lua,
    std::shared_ptr<ECSManager>& manager);
  Entity loadEntity(const sol::table& entity, sol::state& lua,
    std::shared_ptr<ECSManager>& manager);

  template<typename ComponentType, typename FunctionType>
  void loadComponent(Entity& entity,
    const sol::optional<sol::table>& componentTable,
    FunctionType createComponent) {
    if (componentTable != sol::nullopt) {
      entity.addComponent<ComponentType>(
        createComponent(componentTable.value())
      );
    }
  }
  void loadScriptComponent(Entity& entity,
    const sol::optional<sol::table>& componentTable,
    sol::state& lua);
  void loadHealthComponent(Entity& entity,
    const sol::optional<sol::table>& componentTable,
    sol::state& lua, std::shared_ptr<ECSManager>& manager);

  void loadSong(const sol::table& song,
    std::shared_ptr<MusicManager>& musicManager,
    std::shared_ptr<AssetStore>& assetStore);

public:
  void loadGame(const std::string& gameName, sol::state& lua,
    std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

  void loadScene(const std::string& sceneId, sol::state& lua,
    std::shared_ptr<AssetStore>& assetStore,
    std::shared_ptr<ControllerManager>& controllerManager,
    std::shared_ptr<SoundManager>& soundManager,
    std::shared_ptr<AnimationManager>& animationManager,
    std::shared_ptr<ECSManager>& manager,
    std::shared_ptr<MusicManager>& musicManager);
};
 
#endif  // SCENELOADER_H
