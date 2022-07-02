#include "src/RkPch.h"

#if defined(PLATFORM_WINDOWS)

#include "Direct3DRenderer.hpp"

namespace Rake::Drivers::Direct3D
{

Direct3DRenderer::Direct3DRenderer()
{
}

B8 Direct3DRenderer::InitAPI()
{
    return true;
}

B8 Direct3DRenderer::CheckDeviceSuitability()
{
    return true;
}

U32 Direct3DRenderer::RateDeviceSuitability()
{
    return true;
}

B8 Direct3DRenderer::CheckDeviceExtensionSupport()
{
    return true;
}

} // namespace Rake::Drivers::Direct3D

#endif
