#ifndef GRAPHX_I_2D_RENDERER_HPP
#define GRAPHX_I_2D_RENDERER_HPP

#include <Gfx/Context.h>

namespace j2l
{
    namespace GraphX
    {
        class I2DRenderer
        {
        public:
            virtual const bool shouldClose() const = 0;
            virtual void render() const = 0;
            virtual const GfxContext getContext() const = 0;
        };
    }
}

#endif