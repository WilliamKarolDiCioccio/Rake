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

namespace Rake::Core::Error
{

enum class ExceptionType : U32
{
};

class RkException : public std::exception
{
  protected:
    U32 m_line;
    const char *m_msg;
    const char *m_file;

  public:
    RAKE_API RkException(const char *_msg, const char *_file, const U32 _line) noexcept : m_msg(_msg), m_file(_file), m_line(_line){};

    RAKE_API const char *what() const noexcept;
    RAKE_API const char *RkWhere() const;

  protected:
    RAKE_API inline virtual const char *GetType() const
    {
        return "RkException";
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

} // namespace Rake::Core::Error
