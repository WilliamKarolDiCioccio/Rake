/*****************************************************************/ /**
 * \file   RkException.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Config.h"

#if defined(EXCEPTION_HANDLING_ENABLED)

#include <string>
#include <sstream>
#include <exception>

namespace Rake::Core
{

class RkException final : public std::exception
{
  protected:
    const char *m_msg;
    const char *m_file;
    U32 m_code;
    U32 m_line;

  public:
    RkException(const char *_msg, const U32 _code, const char *_file, const U32 _line) noexcept : m_msg(_msg), m_code(_code), m_file(_file), m_line(_line){};

    const char *what() const noexcept;
    const char *Code() const;

  protected:
    inline U32 GetCode() const
    {
        return this->m_code;
    }

    inline const char *GetMsg() const
    {
        return this->m_file;
    }

    inline const char *GetFile() const
    {
        return this->m_file;
    }

    inline U32 GetLine() const
    {
        return this->m_line;
    }
};

#define RkException Rake::Core::RkException

} // namespace Rake::Core

#else

#define RkException(...) ((void)0)

#endif
