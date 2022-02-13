#ifndef GRAPHX_2D_RENDERER_HPP
#define GRAPHX_2D_RENDERER_HPP

#include <stdint.h>
#include <GLFW/glfw3.h>
#include <I2DRenderer.hpp>
#include <Gfx/Context.h>
#include <Gfx/Shader.h>
#include <Gfx/RenderPipeline.h>

// We need to expose GFLW native functions
// for each platform.

#if defined(_WIN32)
    #include <Windows.h>
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__APPLE__)
    #include "appleExt.hpp"
    #define GLFW_EXPOSE_NATIVE_COCOA
#elif defined(__linux__)
    #define GLFW_EXPOSE_NATIVE_X11
#endif
#include <GLFW/glfw3native.h>

#include "Shader.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"

#include <vector>

namespace j2l
{
    namespace GraphX
    {
        class Renderer2D : public I2DRenderer
        {
            private:
                GLFWwindow* _window;
                GfxSurface _surface;
                GfxContext _ctx;

                Shader** _shaders;
                size_t  _shadersLen;

                Material**  _materials;
                size_t      _materialsLen;

                std::vector<Mesh*> _meshes;
                std::vector<MeshRenderer*> _meshRenderers;

                GfxRenderPipeline _renderPipeline;

            public:
                Renderer2D(const uint32_t width, const uint32_t height, const char* title);
                ~Renderer2D();

                /**
                 * @brief Check if the renderer should close.
                 * 
                 * @return `true` if the renderer should close otherwise `false`.
                 */
                const bool shouldClose() const;

                void render() const;

                const GfxContext getContext() const;

                Shader* createShader(const char* path) const;
        };
    }
}

#endif