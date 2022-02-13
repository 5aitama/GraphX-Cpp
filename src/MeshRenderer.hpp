#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <Gfx/Render.h>
#include <Gfx/RenderPipeline.h>

#include "Mesh.hpp"
#include "Material.hpp"

namespace j2l
{
    namespace GraphX
    {
        class I2DRenderer;
        class MeshRenderer
        {
        private:
            GfxRenderPipeline   _renderPipeline;
            Material&           _material;
            Mesh&               _mesh;
            const I2DRenderer*   _renderer;
            
            GfxBufferUniform*  _bufferUniforms;
            size_t             _bufferUniformsLen;

            /**
             * Build / Rebuild the render pipeline.
             */
            void setupRenderPipeline();

        public:
            /**
             * Create new MeshRenderer.
             * 
             * @param mesh      The mesh to render.
             * @param material  The material used to render the mesh.
             */
            MeshRenderer(const I2DRenderer* renderer, Mesh& mesh, Material& material);
            ~MeshRenderer();

            void draw(const GfxRenderPass& renderPass) const;
            const GfxRenderPipeline& getRenderPipeline() const;
        };
    }
}

#endif