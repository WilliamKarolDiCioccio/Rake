#pragma once

#include "base.hpp"

#include <entt/entt.hpp>

#include "Components.hpp"

namespace Rake::engine::entity {

class Entity;
class SceneSerializer;
class SceneManager;

class Scene {
    friend class Entity;
    friend class SceneSerializer;

   private:
    static inline Scene *m_instance = nullptr;

    double m_UUID = 0;
    std::string name = "";

    entt::registry m_registry;
    std::unordered_map<uint64_t, entt::entity> m_entities;

   public:
    Scene();
    ~Scene();

   protected:
    virtual void OnCreate() noexcept {};
    virtual void OnDestroy() noexcept {};

   public:
    RK_API Entity CreateEntity(const std::string &_name, Entity *_parent = nullptr) noexcept;
    RK_API Entity CreateEntityWithUUID(uint64_t _UUID, const std::string &_name, Entity *_parent) noexcept;
    RK_API void DestroyEntity(Entity _entity) noexcept;

   private:
    template <typename T>
    inline void OnComponentAdded(Entity _entity, T &_component) noexcept {}

    template <typename T>
    inline void OnComponentRemoved(Entity _entity, T &_component) noexcept {}

   public:
    NODISCARD static inline Scene *Get() noexcept { return m_instance; }

    NODISCARD inline entt::registry &GetAllEntities() noexcept { return m_registry; }

    template <typename... Components>
    NODISCARD inline auto GetAllEntitiesWith() noexcept {
        return m_registry.view<Components...>();
    }

    NODISCARD inline std::unordered_map<uint64_t, entt::entity> &GetEntityMap() noexcept { m_entities; }

    NODISCARD inline entt::entity &GetEntityWithUUID(uint64_t _UUID) noexcept { return m_entities.at(_UUID); }
};

class SceneSerializer final {
   public:
    SceneSerializer() = default;
};

class SceneManager final {
   private:
    SceneManager() = default;
};

}  // namespace Rake::engine::entity
