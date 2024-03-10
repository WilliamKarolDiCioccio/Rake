#pragma once

#include "base.hpp"

#include "RKSTL/string.hpp"
#include "RKSTL/enum.hpp"

#define MAX_CVAR_REGISTRY_SIZE 1024

namespace Rake::core {

enum class CVarPermissionFlags : uint8_t {
    read = 1 << 0,
    write = 1 << 1,
    readAndWrite = read | write,
};

template <typename T>
struct CVar {
    T data;
    T oldData;

    libraries::EnumFlags<CVarPermissionFlags> flags;

    std::string description;

    CVar(T _data, CVarPermissionFlags _flags, const std::string &_description)
        : data(_data), oldData(_data), flags(_flags), description(_description){};
};

class CVarSystem final : public NonCopyable, NonMovable {
    using BoolCVar = CVar<bool>;
    using IntCVar = CVar<int32_t>;
    using FloatCVar = CVar<float>;
    using StringCVar = CVar<std::string>;
    using EnumCVar = CVar<std::map<std::string, uint32_t>>;

   private:
    static inline CVarSystem *m_instance = nullptr;

    std::unordered_map<std::string, std::shared_ptr<BoolCVar>> m_boolCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<IntCVar>> m_intCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<FloatCVar>> m_floatCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<StringCVar>> m_stringCVarReg = {};

   public:
    CVarSystem();
    ~CVarSystem();

   public:
    RK_API void CreateBoolCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, bool _data);
    RK_API void CreateIntCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, int32_t _data);
    RK_API void CreateFloatCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, float _data);
    RK_API void CreateStringCVar(
        const std::string &_name,
        const std::string &_description,
        CVarPermissionFlags _flags,
        const std::string &_data);

    RK_API void SetBoolCVar(const std::string &_name, bool _data);
    RK_API void SetIntCVar(const std::string &_name, int32_t _data);
    RK_API void SetFloatCVar(const std::string &_name, float _data);
    RK_API void SetStringCVar(const std::string &_name, const std::string &_data);
    RK_API const bool GetBoolCVar(const std::string &_name) const;
    RK_API const int32_t GetIntCVar(const std::string &_name) const;
    RK_API const float GetFloatCVar(const std::string &_name) const;
    RK_API const std::string &GetStringCVar(const std::string &_name) const;

   public:
    RK_API NODISCARD static CVarSystem *Get() noexcept;

    inline const std::unordered_map<std::string, std::shared_ptr<BoolCVar>> &GetBoolReg() const noexcept {
        return m_boolCVarReg;
    }

    inline const std::unordered_map<std::string, std::shared_ptr<IntCVar>> &GetIntReg() const noexcept {
        return m_intCVarReg;
    }

    inline const std::unordered_map<std::string, std::shared_ptr<FloatCVar>> &GetFloatReg() const noexcept {
        return m_floatCVarReg;
    }

    inline const std::unordered_map<std::string, std::shared_ptr<StringCVar>> &GetStringReg() const noexcept {
        return m_stringCVarReg;
    }
};

}  // namespace Rake::core
