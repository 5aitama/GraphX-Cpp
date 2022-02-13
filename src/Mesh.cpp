#include "Mesh.hpp"
#include <I2DRenderer.hpp>

#include <memory>
#include <cstring>

using namespace j2l::GraphX;

Mesh::Mesh(const I2DRenderer* renderer, const float* vertices, size_t vertLen, const uint16_t* indices, size_t indLen) {
    _vertices   = new float[vertLen];
    _indices    = new uint16_t[indLen];

    _verticesLen    = vertLen;
    _indicesLen     = indLen;

    std::memcpy(_vertices, vertices, sizeof(float) * vertLen);
    std::memcpy(_indices, indices, sizeof(uint16_t) * indLen);

    // Create buffers and copy data to them.
    _vBuffer = GfxBufferCreateWithData(renderer->getContext(), vertices, sizeof(float) * vertLen, GfxBufferUsage_Vertex);
    _iBuffer = GfxBufferCreateWithData(renderer->getContext(), indices, sizeof(uint16_t) * indLen, GfxBufferUsage_Index);

    GfxLayoutBufferAttribute* layoutVertexAttributes = new GfxLayoutBufferAttribute[2];

    layoutVertexAttributes[0] = (GfxLayoutBufferAttribute) { .format = GfxLayoutBufferAttributeFormat_Float32x2 };
    layoutVertexAttributes[1] = (GfxLayoutBufferAttribute) { .format = GfxLayoutBufferAttributeFormat_Float32x3 };

    GfxLayoutBuffer layoutVertexBuffer = {
        .stride         = sizeof(float) * 5,
        .attributes     = layoutVertexAttributes,
        .attributesLen  = 2,
    };

    _vBufferLayout = layoutVertexBuffer;
}

Mesh::~Mesh() {

    delete [] _vBufferLayout.attributes;

    GfxBufferDelete(_vBuffer, 1);
    GfxBufferDelete(_iBuffer, 1);
    
    delete [] _vertices;
    delete [] _indices;
}

const GfxBuffer Mesh::getVertexBuffer() const {
    return _vBuffer;
}

const GfxLayoutBuffer& Mesh::getVertexBufferLayout() const {
    return _vBufferLayout;
}

const GfxBuffer Mesh::getIndexBuffer() const {
    return _iBuffer;
}

const size_t Mesh::getIndexAmount() const {
    return _indicesLen;
}