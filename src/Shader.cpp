#include <iostream>
#include <I2DRenderer.hpp>

#include "Shader.hpp"

using namespace j2l::GraphX;

Shader::Shader()
    : _shader(nullptr)
{

}

Shader::Shader(const I2DRenderer* renderer, const char* path) {
    _shader = GfxShaderCreate(path);

    if (GfxShaderCompile(renderer->getContext(), _shader) == 0) {
        std::cout << "Failed to compile shader at " << path << std::endl;
        GfxShaderDelete(_shader);
    }
}

Shader::~Shader() {
    GfxShaderDelete(_shader);
}

const GfxShader& Shader::getRawShader() const {
    return _shader;
}