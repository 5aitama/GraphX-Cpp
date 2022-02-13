#ifndef GRAPHX_UNIFORM_HPP
#define GRAPHX_UNIFORM_HPP

#include <Gfx/Buffer.h>
#include <I2DRenderer.hpp>

#include <iostream>

namespace j2l
{
    namespace GraphX
    {
        class Uniform
        {
        private:
            GfxBuffer           _buffer;
            GfxBufferUniform    _uniform;

            const uint64_t      _size;
            const I2DRenderer*  _renderer;
        
        public:

            /**
             * Create new uniform buffer.
             * 
             * @param renderer  The renderer.
             * @param size      The buffer size.
             * @param binding   The uniform binding index.
             */
            Uniform(const I2DRenderer* renderer, const uint64_t size, const uint64_t binding);
            ~Uniform();
            
            /**
             * Write data to the uniform buffer.
             * 
             * @param data      A pointer to the data to write in the buffer.
             * @param offset    The index (in the uniform buffer) at where the data need to be write.
             * @param len       The length of data array.
             */
            template<typename T>
            void write(const T* data, const uint64_t offset, const size_t len) {
                size_t size = sizeof(T) * len;

                // Ensure that we don't write outside of the buffer.
                // We can have diffrent strategy here to treat this
                // buffer overflow. For now we just return 
                if(size + offset > _size) {
                    std::cout << "[Buffer overflow] Can't write to the uniform buffer..." << std::endl;
                    return;
                }

                GfxBufferWrite(_renderer->getContext(), _buffer, data, offset, size);
            };

            const GfxBufferUniform& getRawUniformBuffer() const;
        };
    }
}

#endif