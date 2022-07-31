#include "RkPch.h"

#if defined(EXCEPTION_HANDLING_ENABLED)

#include "Exception.hpp"

namespace Rake::Core
{

const char *Exception::what() const noexcept
{
    std::string buffer;
    std::stringstream ss;
    ss << GetMsg() << GetFile() << GetLine();
    buffer = ss.str();

    return buffer.c_str();
}

const char *Exception::Code() const
{
    std::string buffer;
    std::stringstream ss;
    ss << GetCode();
    buffer = ss.str();

    return buffer.c_str();
}

} // namespace Rake::Core

#endif
