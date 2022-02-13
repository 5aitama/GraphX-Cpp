#include "Material.hpp"
#include <I2DRenderer.hpp>

using namespace j2l::GraphX;

Material::Material(const I2DRenderer* renderer, const Shader& shader) 
    : _shader(shader), _renderer(renderer)
{

}

Material::~Material() {
    std::map<std::string, Uniform*>::const_iterator it = _uniforms.begin();
    while(it != _uniforms.end()) {
        delete it->second;
        std::advance(it, 1);
    }
}

const size_t Material::getUniformLen() const {
    return _uniforms.size();
}

const Uniform& Material::getUniform(const size_t at) const {
    std::map<std::string, Uniform*>::const_iterator it = _uniforms.begin();
    std::advance(it, at);
    return *it->second;
}

const Shader& Material::getShader() const {
    return _shader;
}

void Material::setUniform(const std::string& name, const uint64_t size, const uint64_t binding) {
    _uniforms.insert(std::make_pair(name, new Uniform(_renderer, size, binding)));
}