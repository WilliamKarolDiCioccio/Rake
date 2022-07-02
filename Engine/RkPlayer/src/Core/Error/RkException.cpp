#include "src/RkPch.h"

#include "RkException.hpp"

namespace Rake::Core::Error
{

const char *RkException::what() const noexcept
{
    std::string buffer;
    std::stringstream ss;
    ss << (U8)GetType() << GetMsg();

    return buffer.c_str();
}

const char *RkException::RkWhere() const
{
    std::string buffer;
    std::stringstream ss;
    ss << GetFile() << GetLine();

    return buffer.c_str();
}

} // namespace Rake::Core::Error
