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

class RkException : public std::exception
{
  protected:
    const char *m_msg;
    const char *m_file;
    U32 m_line;

  protected:
    inline virtual const char *GetType() const
    {
        return "RkException";
    }

    inline const char *GetMsg() const
    {
        return m_file;
    }

    inline const char *GetFile() const
    {
        return m_file;
    }

    inline U32 GetLine() const
    {
        return m_line;
    }

  public:
    RkException(const char *_msg, const char *_file, U32 _line) noexcept : m_msg(_msg), m_file(_file), m_line(_line){};

    const char *what() const noexcept;
    const char *where() const;
};

} // namespace Rake::Core
