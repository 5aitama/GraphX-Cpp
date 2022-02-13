#ifndef GRAPHX_MESH_HPP
#define GRAPHX_MESH_HPP

#include <Gfx/Buffer.h>
#include <Gfx/RenderPipeline.h>
#include <Gfx/Render.h>

#include <stdint.h>
#include <stddef.h>

namespace j2l
{
    namespace GraphX
    {
        class Shader;
        class I2DRenderer;

        class Mesh
        {
            private:
                /** The vertex buffer. */
                GfxBuffer _vBuffer;

                /** The index buffer. */
                GfxBuffer _iBuffer;

                /** The vertices */
                float* _vertices;
                size_t _verticesLen;

                /** The indices */
                uint16_t* _indices;
                size_t _indicesLen;

                GfxLayoutBuffer     _vBufferLayout;
            public:
                /**
                 * @brief Create new Mesh.
                 * 
                 * @param renderer  The renderer.
                 * @param vertices  The mesh vertices.
                 * @param vertLen   The amount of vertices.
                 * @param indices   The mesh indices.
                 * @param indLen    The amount of indices.
                 */
                Mesh(const I2DRenderer* renderer, const float* vertices, size_t vertLen, const uint16_t* indices, size_t indLen);
                ~Mesh();

                /**
                 * @brief Get the Vertex Buffer
                 * 
                 * @return The vertex buffer.
                 */
                const GfxBuffer getVertexBuffer() const;

                /**
                 * @brief Get the vertex buffer layout.
                 * 
                 * @return The vertex buffer layout.
                 */
                const GfxLayoutBuffer& getVertexBufferLayout() const;

                /**
                 * @brief Get the Index Buffer
                 * 
                 * @return The index buffer.
                 */
                const GfxBuffer getIndexBuffer() const;

                const size_t getIndexAmount() const;
        };
    }
}

#endif