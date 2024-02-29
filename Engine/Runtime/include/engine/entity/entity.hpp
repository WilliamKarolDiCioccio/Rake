#pragma once

#include "base.hpp"

#include "scene.hpp"

namespace Rake::engine::entity {

template <class B, class D>
concept Derived = std::is_base_of_v<B, D>;

template <typename B, typename... Ds>
concept AllDerived = (std::is_base_of_v<B, Ds> && ...);

class Entity {
   private:
    Scene *m_scene = nullptr;
    Entity *m_parent = nullptr;

    const entt::entity m_enttHandle;

    uint64_t m_UUID = 0;
    std::string m_name = "";

   public:
    RK_API Entity() = default;
    RK_API Entity(entt::entity _enttHandle, Scene *_scene, Entity *_parent);
    RK_API virtual ~Entity() = default;

   protected:
    RK_API virtual void OnCreate() noexcept {};
    RK_API virtual void OnUpdate() noexcept {};
    RK_API virtual void OnDestroy() noexcept {};

   public:
    template <typename T, typename... Args>
    inline T &AddComponent(Args &&..._args) noexcept {
        RK_STATIC_ASSERT((Derived<Component, T>));

        T &component = m_scene->m_registry.emplace<T>(m_enttHandle, std::forward<Args>(_args)...);

        static_cast<Component &>(component).entity = this;

        m_scene->OnComponentAdded<T>(*this, component);

        return component;
    }

    template <typename T, typename... Args>
    inline T &AddOrReplaceComponent(Args &&..._args) noexcept {
        RK_STATIC_ASSERT((Derived<Component, T>));

        T &component = m_scene->m_registry.emplace_or_replace<T>(m_enttHandle, std::forward<Args>(_args)...);

        static_cast<Component>(component).entity = this;

        m_scene->OnComponentAdded<T>(*this, component);

        return component;
    }

    template <typename T>
    void RemoveComponent() noexcept {
        RK_STATIC_ASSERT((Derived<Component, T>));

        m_scene->m_registry.remove<T>(m_enttHandle);
    }

    template <typename... Ts>
    void RemoveComponents() noexcept {
        RK_STATIC_ASSERT((AllDerived<Component, Ts...>));

        m_scene->m_registry.remove<Ts...>(m_enttHandle);
    }

    template <typename T>
    bool HasComponent() noexcept {
        RK_STATIC_ASSERT((Derived<Component, T>));

        if (m_scene->m_registry.try_get<T>(m_enttHandle) != nullptr) return true;

        return false;
    }

    template <typename T>
    T &GetComponent() noexcept {
        RK_STATIC_ASSERT((Derived<Component, T>));

        return m_scene->m_registry.get<T>(m_enttHandle);
    }

    template <typename... Ts>
    auto GetComponents() noexcept -> decltype(entt::registry::view<Ts...>()) {
        RK_STATIC_ASSERT((AllDerived<Component, Ts...>));

        return m_scene->m_registry.view<Ts...>(m_enttHandle);
    }

   public:
    NODISCARD inline uint64_t GetUUID() const noexcept { return m_UUID; }

    NODISCARD inline const entt::entity &GetEnttHandle() const noexcept { return m_enttHandle; }
};

}  // namespace Rake::engine::entity
