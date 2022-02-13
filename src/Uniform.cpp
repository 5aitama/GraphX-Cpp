#include "Uniform.hpp"
#include <I2DRenderer.hpp>

using namespace j2l::GraphX;

Uniform::Uniform(const I2DRenderer* renderer, const uint64_t size, const uint64_t binding)
    : _size(size), _renderer(renderer)
{
    _buffer     = GfxBufferCreate(renderer->getContext(), size, (GfxBufferUsage)(GfxBufferUsage_Uniform | GfxBufferUsage_CopyDst));
    _uniform    = GfxBufferUniformCreate(renderer->getContext(), _buffer, binding, 0);
}

Uniform::~Uniform()
{
    GfxBufferUniformDelete(_uniform);
    GfxBufferDelete(_buffer, 1);
}

const GfxBufferUniform& Uniform::getRawUniformBuffer() const {
    return _uniform;
}