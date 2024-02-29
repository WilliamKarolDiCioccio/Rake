#include "pch.hpp"

#include <string>
#include <memory>
#include <unordered_map>
#include <imgui.h>

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
    const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, int32_t _data) {
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

void CVarSystem::SetIntCVar(const std::string &_name, int32_t _data) {
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

void CVarSystem::EditBoolCVar(const std::string &_name) {
    auto &cVar = m_boolCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    ImGui::Begin("Editing bool CVar");

    ImGui::Text("Name: %s", _name.c_str());

    ImGui::Separator();

    if (cVar->flags & CVarPermissionFlags::write) {
        ImGui::Checkbox("Value", &cVar->data);
    } else {
        ImGui::Text("Value: %s", cVar->data ? "true" : "false");
    }

    ImGui::End();
}

void CVarSystem::EditIntCVar(const std::string &_name) {
    auto &cVar = m_intCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    ImGui::Begin("Edit int CVar");

    ImGui::Text("Name: %s", _name.c_str());

    ImGui::Separator();

    if (cVar->flags & CVarPermissionFlags::write) {
        ImGui::InputInt("Value", &cVar->data);
    } else {
        ImGui::Text("Value: %i", cVar->data);
    }

    ImGui::End();
}

void CVarSystem::EditFloatCVar(const std::string &_name) {
    auto &cVar = m_floatCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    ImGui::Begin("Editing float CVar");

    ImGui::Text("Name: %s", _name.c_str());

    ImGui::Separator();

    if (cVar->flags & CVarPermissionFlags::write) {
        ImGui::InputFloat("Value", &cVar->data);
    } else {
        ImGui::Text("Value: %d", cVar->data);
    }

    ImGui::End();
}

void CVarSystem::EditStringCVar(const std::string &_name) {
    auto &cVar = m_stringCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!", _name);

    ImGui::Begin("Editing string CVar");

    ImGui::Text("Name: %s", _name.c_str());

    ImGui::Separator();

    if (cVar->flags & CVarPermissionFlags::write) {
        static char buffer[128];

        strcpy(buffer, cVar->data.c_str());

        if (ImGui::InputText("Value", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            cVar->data = buffer;

            memset(buffer, 0, sizeof(buffer));
        }
    } else {
        ImGui::Text("Value: %s", cVar->data);
    }

    ImGui::End();
}

const bool CVarSystem::GetBoolCVar(const std::string &_name) const {
    if (m_boolCVarReg.find(_name) == m_boolCVarReg.end()) throw RkException("CVar '{}' does not exist!", _name);

    auto cVar = m_boolCVarReg.at(_name);

    if (!(cVar->flags & CVarPermissionFlags::read)) throw RkException("CVar '{}' is not readable!");

    return cVar->data;
}

const int32_t CVarSystem::GetIntCVar(const std::string &_name) const {
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

void CVarSystem::ShowCVarMenu(bool &_status) noexcept {
    ImGui::Begin("CVar Menu", &_status);

    {
        const auto &boolCVarNames = populateCVarNames(m_boolCVarReg);

        static int currentItem = 0;
        static bool showEditor = false;

        if (ImGui::ListBox("Bool CVars", &currentItem, boolCVarNames.data(), boolCVarNames.size()))
            showEditor = !showEditor;

        if (showEditor) EditBoolCVar(boolCVarNames[currentItem]);
    }

    ImGui::Separator();

    {
        const auto &intCVarNames = populateCVarNames(m_intCVarReg);

        static int currentItem = 0;
        static bool showEditor = false;

        if (ImGui::ListBox("Int CVars", &currentItem, intCVarNames.data(), intCVarNames.size()))
            showEditor = !showEditor;

        if (showEditor) EditIntCVar(intCVarNames[currentItem]);
    }

    ImGui::Separator();

    {
        const auto &floatCVarNames = populateCVarNames(m_floatCVarReg);

        static int currentItem = 0;
        static bool showEditor = false;

        if (ImGui::ListBox("Float CVars", &currentItem, floatCVarNames.data(), floatCVarNames.size()))
            showEditor = !showEditor;

        if (showEditor) EditFloatCVar(floatCVarNames[currentItem]);
    }

    ImGui::Separator();

    {
        const auto &stringCVarNames = populateCVarNames(m_stringCVarReg);

        static int currentItem = 0;
        static bool showEditor = false;

        if (ImGui::ListBox("String CVars", &currentItem, stringCVarNames.data(), stringCVarNames.size()))
            showEditor = !showEditor;

        if (showEditor) EditStringCVar(stringCVarNames[currentItem]);
    }

    ImGui::End();
}

CVarSystem *CVarSystem::Get() noexcept { return m_instance; }

}  // namespace Rake::core
