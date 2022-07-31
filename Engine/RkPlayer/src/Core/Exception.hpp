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

class Exception final : public std::exception
{
  protected:
    const char *m_msg;
    const char *m_file;
    U32 m_code;
    U32 m_line;

  public:
    B8 m_forUser;

  public:
    Exception(const char *_msg, U32 _code, const char *_file, U32 _line, B8 _forUser) noexcept : m_msg(_msg), m_code(_code), m_file(_file), m_line(_line), m_forUser(_forUser){};

    RAKE_API const char *what() const noexcept;
    RAKE_API const char *Code() const;

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

#define RkException(msg, code, file, line, forUser) Rake::Core::Exception(msg, code, file, line, forUser)

} // namespace Rake::Core

#else

#define RkException(msg, code, file, line, forUser) ((void)0)

#endif
