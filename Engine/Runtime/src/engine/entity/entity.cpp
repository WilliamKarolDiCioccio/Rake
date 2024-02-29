#include "pch.hpp"

#include "engine/entity/entity.hpp"

namespace Rake::engine::entity {

Entity::Entity(entt::entity _enttHandle, Scene *_scene, Entity *_parent)
    : m_enttHandle(_enttHandle), m_scene(_scene), m_parent(_parent) {}

}  // namespace Rake::engine::entity
