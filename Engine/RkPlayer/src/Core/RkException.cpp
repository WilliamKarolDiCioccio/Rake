#include "src/RkPch.h"

#if defined(EXCEPTION_HANDLING_ENABLED)

#include "RkException.hpp"

namespace Rake::Core
{

const char *RkException::what() const noexcept
{
    std::string buffer;
    std::stringstream ss;
    ss << GetMsg() << GetFile() << GetLine();
    buffer = ss.str();

    return buffer.c_str();
}

const char *RkException::Code() const
{
    std::string buffer;
    std::stringstream ss;
    ss << GetCode();
    buffer = ss.str();

    return buffer.c_str();
}

} // namespace Rake::Core

#endif
