/*****************************************************************/ /**
 * \file   RkException.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <string>
#include <sstream>
#include <exception>

#include "Common.def.h"

namespace Rake::Core
{

enum class Layer
{
    None = 0,
    ApplicationLayer = 1
};

enum class Type
{
    None = 0,
    ResourcesAcquirement = 1
};

class RkException : public std::exception
{
  protected:
    U32 m_line;
    Layer m_layer;
    const char *m_msg;
    const char *m_file;

  public:
    RAKE_API RkException(const char *_msg, const char *_file, const U32 _line, Layer _layer, Type _type) noexcept : m_msg(_msg), m_file(_file), m_line(_line), m_layer(_layer){};

    RAKE_API const char *what() const noexcept;
    RAKE_API const char *where() const;

  protected:
    RAKE_API inline virtual Layer GetType() const
    {
        return m_layer;
    }

    RAKE_API inline const char *GetMsg() const
    {
        return m_file;
    }

    RAKE_API inline const char *GetFile() const
    {
        return m_file;
    }

    RAKE_API inline U32 GetLine() const
    {
        return m_line;
    }
};

#define LAYER_NONE        Rake::Core::Layer::None
#define APPLICATION_LAYER Rake::Core::Layer::ApplicationLayer

#define TYPE_NONE                 Rake::Core::Type::None
#define RESOURCE_ACQUIREMENT_TYPE Rake::Core::Type::ResourcesAcquirement
} // namespace Rake::Core
