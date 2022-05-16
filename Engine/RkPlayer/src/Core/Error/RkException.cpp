#include "RkPch.hpp"

#include "RkException.hpp"

namespace Rake::Core
{

const char *RkException::what() const noexcept
{
    std::string buffer;
    std::stringstream ss;
    ss << GetType() << GetMsg();

    return buffer.c_str();
}

const char *RkException::where() const
{
    std::string buffer;
    std::stringstream ss;
    ss << GetFile() << GetLine();

    return buffer.c_str();
}

} // namespace Rake::Core
