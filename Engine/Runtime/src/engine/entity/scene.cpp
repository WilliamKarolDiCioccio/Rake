#include "pch.hpp"

#include "engine/entity/scene.hpp"
#include "engine/entity/entity.hpp"

namespace Rake::engine::entity {

Scene::Scene() {
    if (m_instance != nullptr) throw std::runtime_error("Scene already created!");

    m_instance = this;

    OnCreate();
}

Scene::~Scene() {
    OnDestroy();

    m_instance = nullptr;
    delete (m_instance);
}

Entity Scene::CreateEntity(const std::string &_name, Entity *_parent) noexcept {
    return CreateEntityWithUUID(0u, _name, _parent);
}

Entity Scene::CreateEntityWithUUID(uint64_t _UUID, const std::string &_name, Entity *_parent) noexcept {
    Entity entity = {m_registry.create(), this, _parent};

    entity.AddComponent<TagComponent>(_name);
    entity.AddComponent<UUIDComponent>(_UUID);

    return entity;
}

void Scene::DestroyEntity(Entity _entity) noexcept {
    m_entities.erase(_entity.GetUUID());
    m_registry.destroy(_entity.GetEnttHandle());
}

}  // namespace Rake::engine::entity
