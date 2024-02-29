#pragma once

#include "base.hpp"

namespace Rake::engine::entity {

class Entity;

struct Component {
    Entity *entity = nullptr;
};

struct TagComponent : Component {
    std::string tag;

    TagComponent(const std::string &_tag) : tag(_tag){};
};

struct UUIDComponent : Component {
    uint64_t UUID;

    UUIDComponent(uint64_t _UUID) : UUID(_UUID){};
};

struct GraphicsComponent : Component {
    GraphicsComponent(){};
};

struct PhysicsComponent : Component {
    PhysicsComponent(){};
};

struct AudioComponent : Component {
    AudioComponent(){};
};

struct NetworkComponent : Component {
    NetworkComponent(){};
};

struct TransformComponent : Component {
    TransformComponent(){};
};

}  // namespace Rake::engine::entity
