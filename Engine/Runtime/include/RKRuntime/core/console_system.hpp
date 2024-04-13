#pragma once

#include "RKRuntime/base.hpp"

#include <RKSTL/string.hpp>
#include <RKSTL/enum.hpp>

#define MAX_CVAR_REGISTRY_SIZE 1024

namespace Rake::core {

/**
 * @brief The CVar permission flags
 */
enum class CVarPermissionFlags : uint8_t {
    read = 1 << 0,
    write = 1 << 1,
    readAndWrite = read | write,
};

/**
 * @brief The CVar system class is used to create and manage console variables, think of it as an enviroment variables manager.
 * 
 * @details
 * Console variables are used to store and manage game settings and configurations from anywhere in the program, they can be of type bool, int, float or string.
 * Console variables are also powerful tools for debugging and testing, they can be accessed and modified through the console.
 * 
 * @note This class is a singleton instantiated by the Application class and should be accessed through the Get() method.
 */
class CVarSystem final : public NonCopyable, NonMovable {
   private:
    template <typename T>
    struct CVar {
        T data;
        T oldData;

        libraries::EnumFlags<CVarPermissionFlags> flags;

        std::string description;

        CVar(T _data, CVarPermissionFlags _flags, const std::string &_description)
            : data(_data), oldData(_data), flags(_flags), description(_description){};
    };

    using BoolCVar = CVar<bool>;
    using IntCVar = CVar<int>;
    using FloatCVar = CVar<float>;
    using StringCVar = CVar<std::string>;

    static inline CVarSystem *m_instance = nullptr;

    std::unordered_map<std::string, std::shared_ptr<BoolCVar>> m_boolCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<IntCVar>> m_intCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<FloatCVar>> m_floatCVarReg = {};
    std::unordered_map<std::string, std::shared_ptr<StringCVar>> m_stringCVarReg = {};

   public:
    CVarSystem();
    ~CVarSystem();

   public:
    /**
	 * @brief Create a new console variable of type bool.
	 * 
	 * @param _name The name of the console variable.
	 * @param _description The description of the console variable.
	 * @param _flags The permission flags of the console variable.
	 * @param _data The data of the console variable.
	 */
    RK_API void CreateBoolCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, bool _data);

    /**
     * @brief Create a new console variable of type int.
     * 
     * @param _name The name of the console variable.
     * @param _description The description of the console variable.
     * @param _flags The permission flags of the console variable.
     * @param _data The data of the console variable.
	 */
    RK_API void CreateIntCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, int _data);

    /**
     * @brief Create a new console variable of type float.
     * 
     * @param _name The name of the console variable.
     * @param _description The description of the console variable.
     * @param _flags The permission flags of the console variable.
     * @param _data The data of the console variable.
	 */
    RK_API void CreateFloatCVar(
        const std::string &_name, const std::string &_description, CVarPermissionFlags _flags, float _data);

    /**
     * @brief Create a new console variable of type string.
     * 
     * @param _name The name of the console variable.
     * @param _description The description of the console variable.
     * @param _flags The permission flags of the console variable.
     * @param _data The data of the console variable.
     */
    RK_API void CreateStringCVar(
        const std::string &_name,
        const std::string &_description,
        CVarPermissionFlags _flags,
        const std::string &_data);

    /**
     * @brief Set the console variable of type bool.
     * 
     * @param _name The name of the console variable.
     * @param _data The data of the console variable.
     */
    RK_API void SetBoolCVar(const std::string &_name, bool _data);

    /**
     * @brief Set the console variable of type int.
     * 
     * @param _name The name of the console variable.
     * @param _data The data of the console variable.
     */
    RK_API void SetIntCVar(const std::string &_name, int _data);

    /**
	 * @brief Set the console variable of type float.
	 * 
	 * @param _name The name of the console variable.
	 * @param _data The data of the console variable.
     */
    RK_API void SetFloatCVar(const std::string &_name, float _data);

    /**
     * @brief Set the console variable of type string.
     * 
     * @param _name The name of the console variable.
     * @param _data The data of the console variable.
	 */
    RK_API void SetStringCVar(const std::string &_name, const std::string &_data);

    /**
     * @brief Get the console variable of type bool.
     * 
     * @param _name The name of the console variable.
     * @return The console variable.
	 */
    RK_API const bool GetBoolCVar(const std::string &_name) const;

    /**
	 * @brief Get the console variable of type int.
	 * 
	 * @param _name The name of the console variable.
	 * @return The console variable.
     */
    RK_API const int GetIntCVar(const std::string &_name) const;

    /**
     * @brief Get the console variable of type float.
     * 
     * @param _name The name of the console variable.
     * @return The console variable.
     */
    RK_API const float GetFloatCVar(const std::string &_name) const;

    /**
	 * @brief Get the console variable of type string.
	 * 
	 * @param _name The name of the console variable.
	 * @return The console variable.
	 */
    RK_API const std::string &GetStringCVar(const std::string &_name) const;

   public:
    /**
	 * @brief Get the singleton instance of the CVarSystem class.
	 * 
	 * @return The CVarSystem instance.
	 */
    RK_API NODISCARD static CVarSystem *Get() noexcept;

    /**
     * @brief Get the console variable registry.
     * 
     * @return The console variable registry.
	 */
    inline const std::unordered_map<std::string, std::shared_ptr<BoolCVar>> &GetBoolReg() const noexcept {
        return m_boolCVarReg;
    }

    /**
	 * @brief Get the console variable registry.
	 * 
	 * @return The console variable registry.
     */
    inline const std::unordered_map<std::string, std::shared_ptr<IntCVar>> &GetIntReg() const noexcept {
        return m_intCVarReg;
    }

    /**
	 * @brief Get the console variable registry.
	 * 
	 * @return The console variable registry.
     */
    inline const std::unordered_map<std::string, std::shared_ptr<FloatCVar>> &GetFloatReg() const noexcept {
        return m_floatCVarReg;
    }

    /**
     * @brief Get the console variable registry.
     * 
     * @return The console variable registry.
     */
    inline const std::unordered_map<std::string, std::shared_ptr<StringCVar>> &GetStringReg() const noexcept {
        return m_stringCVarReg;
    }
};

}  // namespace Rake::core
