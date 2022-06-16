#include "src/RkPch.hpp"

#include "Renderer/Renderer.hpp"

namespace Rake::Renderer
{

Renderer *Renderer::m_rendererInstance = nullptr;

Renderer::Renderer(const RendererAPI _rendererApi, const RendererType _type)
{
    if ()
    {

        switch (_rendererApi)
        {
        default:
            break;
        }
    }
}

B8 Renderer::Init()
{
    return true;
}

void Renderer::Release()
{
}

} // namespace Rake::Renderer
