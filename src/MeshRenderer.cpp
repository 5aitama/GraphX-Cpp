#include "MeshRenderer.hpp"
#include <I2DRenderer.hpp>

using namespace j2l::GraphX;

MeshRenderer::MeshRenderer(const I2DRenderer* renderer, Mesh& mesh, Material& material) 
    : _renderer(renderer), _mesh(mesh), _material(material), _renderPipeline(nullptr), _bufferUniforms(nullptr)
{
    setupRenderPipeline();
}

MeshRenderer::~MeshRenderer() {
    GfxRenderPipelineDelete(_renderPipeline);
    delete [] _bufferUniforms;
}

void MeshRenderer::setupRenderPipeline() {
    GfxRenderPipelineDelete(_renderPipeline);

    delete [] _bufferUniforms;
    
    // Setup the material uniforms buffer...
    _bufferUniformsLen   = _material.getUniformLen();
    _bufferUniforms     = new GfxBufferUniform[_bufferUniformsLen];

    for(size_t i = 0; i < _bufferUniformsLen; i++)
        _bufferUniforms[i] = _material.getUniform(i).getRawUniformBuffer();

    GfxRenderPipelineParams params = GfxRenderPipelineParamsDefault;
    params.uniforms                 = _bufferUniforms;
    params.uniformsLen              = _bufferUniformsLen;
    params.vertexBufferLayout       = &_mesh.getVertexBufferLayout();
    params.vertexBufferLayoutLen    = 1;
    params.shader                   = _material.getShader().getRawShader();

    _renderPipeline = GfxRenderPipelineCreate(_renderer->getContext(), &params);
}

void MeshRenderer::draw(const GfxRenderPass& renderPass) const {
    // Set the vertex buffer to the render pass.
    GfxRenderPassSetVertexBuffer(renderPass, _mesh.getVertexBuffer(), 0);
    
    // Set the index buffer to the render pass.
    GfxRenderPassSetIndexBuffer(renderPass, _mesh.getIndexBuffer(), GfxLayoutIndexFormat_Uint16);

    for(size_t i = 0; i < _bufferUniformsLen; i++)
        GfxRenderPassSetUniform(renderPass, _bufferUniforms[i], static_cast<uint32_t>(i));

    // Draw the mesh
    GfxRenderPassDrawIndexed(renderPass, _mesh.getIndexAmount(), 1, 0, 0, 0);
}

const GfxRenderPipeline& MeshRenderer::getRenderPipeline() const {
    return _renderPipeline;
}