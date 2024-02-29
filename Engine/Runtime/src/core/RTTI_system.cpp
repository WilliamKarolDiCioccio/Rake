#include "pch.hpp"

#include "core/RTTI_system.hpp"

namespace Rake::core {

size_t AScriptableObject::GetTypeId() const { return 0; }

std::string AScriptableObject::GetTypeName() const { return std::string(); }

std::vector<std::string> AScriptableObject::GetClassHierarchy() const { return std::vector<std::string>(); }

std::string Property::GetName() const { return std::string(); }

Type* Property::GetType() const { return nullptr; }

size_t Type::GetTypeId() const { return 0; }

std::string Type::GetTypeName() const { return std::string(); }

std::vector<Type*> Type::GetBaseTypes() const { return std::vector<Type*>(); }

std::vector<Property*> Type::GetProperties() const { return std::vector<Property*>(); }

uint32_t Type::GetVersion() const { return 0; }

void Type::Serialize(const std::string& data) const { return; }

std::string Type::Deserialize() { return std::string(); }

AScriptableObject* Type::CreateInstance() { return nullptr; }

void RTTISystem::RegisterType(size_t typeId, Type* type) {}

Type* RTTISystem::GetType(size_t typeId) const { return nullptr; }

}  // namespace Rake::core
