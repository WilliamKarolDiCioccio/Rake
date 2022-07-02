#include "src/RkPch.h"

#include "Renderer.hpp"

#if defined(PLATFORM_WINDOWS) == 1
#include "Drivers/Direct3D/Direct3DRenderer.hpp"
#endif

namespace Rake::Engine::Graphics
{

B8 Renderer::m_isInitialized = false;

std::unique_ptr<Renderer> Renderer::CreateRenderer()
{
    if (!m_isInitialized)
    {
#if defined(PLATFORM_WINDOWS) == 1
        return std::make_unique<Drivers::Direct3D::Direct3DRenderer>();
#endif
    }
    else
    {
        throw Core::Error::RkException("GraphicsEngine instance already created!", __FILE__, __LINE__);
        RK_SIGABRT;
    }
}

} // namespace Rake::Engine::Graphics
