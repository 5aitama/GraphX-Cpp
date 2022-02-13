#ifndef GRAPHX_SHADER_HPP
#define GRAPHX_SHADER_HPP

#include <Gfx/Shader.h>

namespace j2l
{
    namespace GraphX
    {
        class I2DRenderer;

        class Shader
        {
            private:
                GfxShader _shader;

            public:
                Shader();
                /**
                 * @brief Construct a new Shader
                 * 
                 * @param path The `.wgsl` shader path.
                 */
                Shader(const I2DRenderer* renderer, const char* path);
                ~Shader();

                /**
                 * @brief Get the raw shader.
                 * 
                 * @return The raw shader.
                 */
                const GfxShader& getRawShader() const;
        };
    }
}

#endif