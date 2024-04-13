#include "pch.hpp"

#include <string>
#include <memory>
#include <unordered_map>

#include "core/console_system.hpp"

namespace Rake::core {

auto const populateCVarNames = [](const auto &cVarMap) {
    std::vector<const char *> cvarNames = {};

    for (const auto &[k, v] : cVarMap) cvarNames.emplace_back(k.c_str());

    return cvarNames;
};

CVarSystem::CVarSystem() {
    if (m_instance != nullptr) throw std::runtime_error("CVar system already created!");

    m_instance = this;
}

CVarSystem::~CVarSystem() {
    m_instance = nullptr;
    delete (m_instance);
}

void CVarSystem::CreateBoolCVar(
    const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, bool _data) {
    if (m_boolCVarReg.size() >= MAX_CVAR_REGISTRY_SIZE) throw RkException(L"Bool CVar registry is full!");

    auto cVar = std::make_shared<BoolCVar>(_data, _flags, _description);

    m_boolCVarReg.insert({_name, cVar});
}

void CVarSystem::CreateIntCVar(
    const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, int _data) {
    if (m_intCVarReg.size() >= MAX_CVAR_REGISTRY_SIZE) throw RkException(L"Int CVar registry is full!");

    auto cVar = std::make_shared<IntCVar>(_data, _flags, _description);

    m_intCVarReg.insert({_name, cVar});
}

void CVarSystem::CreateFloatCVar(
    const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, float _data) {
    if (m_floatCVarReg.size() >= MAX_CVAR_REGISTRY_SIZE) throw RkException(L"Float CVar registry is full!");

    auto cVar = std::make_shared<FloatCVar>(_data, _flags, _description);

    m_floatCVarReg.insert({_name, cVar});
}

void CVarSystem::CreateStringCVar(
    const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, const std::string &_data) {
    if (m_stringCVarReg.size() >= MAX_CVAR_REGISTRY_SIZE) throw RkException(L"String CVar registry is full!");

    auto cVar = std::make_shared<StringCVar>(_data, _flags, _description);

    m_stringCVarReg.insert({_name, cVar});
}

void CVarSystem::SetBoolCVar(const std::string &_name, bool _data) {
    if (m_boolCVarReg.find(_name) == m_boolCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_boolCVarReg.at(_name);

    if (cVar->flags & CVarPermissionFlags::write) {
        cVar->oldData = cVar->data;
        cVar->data = _data;
    }
}

void CVarSystem::SetIntCVar(const std::string &_name, int _data) {
    if (m_intCVarReg.find(_name) == m_intCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_boolCVarReg.at(_name);

    if (cVar->flags & CVarPermissionFlags::write) {
        cVar->oldData = cVar->data;
        cVar->data = _data;
    }
}

void CVarSystem::SetFloatCVar(const std::string &_name, float _data) {
    if (m_floatCVarReg.find(_name) == m_floatCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_floatCVarReg.at(_name);

    if (cVar->flags & CVarPermissionFlags::write) {
        cVar->oldData = cVar->data;
        cVar->data = _data;
    }
}

void CVarSystem::SetStringCVar(const std::string &_name, const std::string &_data) {
    if (m_stringCVarReg.find(_name) == m_stringCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_stringCVarReg.at(_name);

    if (cVar->flags & CVarPermissionFlags::write) {
        cVar->oldData = cVar->data;
        cVar->data = _data;
    }
}

const bool CVarSystem::GetBoolCVar(const std::string &_name) const {
    if (m_boolCVarReg.find(_name) == m_boolCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_boolCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!");

    return cVar->data;
}

const int CVarSystem::GetIntCVar(const std::string &_name) const {
    if (m_intCVarReg.find(_name) == m_intCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_intCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    return cVar->data;
}

const float CVarSystem::GetFloatCVar(const std::string &_name) const {
    if (m_floatCVarReg.find(_name) == m_floatCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_floatCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    return cVar->data;
}

const std::string &CVarSystem::GetStringCVar(const std::string &_name) const {
    if (m_stringCVarReg.find(_name) == m_stringCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_stringCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    return cVar->data;
}

CVarSystem *CVarSystem::Get() noexcept { return m_instance; }

}  // namespace Rake::core
