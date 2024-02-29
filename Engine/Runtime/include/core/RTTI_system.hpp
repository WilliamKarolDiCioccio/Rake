#pragma once

#include "base.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace Rake::core {

class Type;

class ISerializable {
   public:
    virtual void Serialize(const std::string& data) const = 0;
    virtual std::string Deserialize() = 0;
};

class AScriptableObject {
   private:
    size_t typeId;

   public:
    size_t GetTypeId() const;
    std::string GetTypeName() const;
    std::vector<std::string> GetClassHierarchy() const;
};

class Property {
   private:
    std::string name;
    Type* type;

   public:
    std::string GetName() const;
    Type* GetType() const;
};

class Type : public ISerializable {
   private:
    size_t typeId;
    std::string typeName;
    std::vector<Type*> baseTypes;
    std::vector<Property*> properties;
    size_t version;

   public:
    size_t GetTypeId() const;
    std::string GetTypeName() const;
    std::vector<Type*> GetBaseTypes() const;
    std::vector<Property*> GetProperties() const;
    uint32_t GetVersion() const;
    void Serialize(const std::string& data) const override;
    std::string Deserialize() override;
    AScriptableObject* CreateInstance();
};

class RTTISystem {
   private:
    std::unordered_map<size_t, Type*> m_typeRegistry = {};

   public:
    void RegisterType(size_t typeId, Type* type);
    Type* GetType(size_t typeId) const;
};

}  // namespace Rake::core
