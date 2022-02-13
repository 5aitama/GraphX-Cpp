#ifndef GRAPHX_MATERIAL_HPP
#define GRAPHX_MATERIAL_HPP

#include <map>
#include <string>
#include <Gfx/Buffer.h>

#include "Uniform.hpp"
#include "Shader.hpp"

namespace j2l
{
    namespace GraphX
    {
        class I2DRenderer;

        class Material
        {
        private:
            const Shader& _shader;
            const I2DRenderer* _renderer;
            std::map<std::string, Uniform*> _uniforms;

        public:
            Material();
            Material(const I2DRenderer* renderer, const Shader& shader);
            ~Material();
            
            void setUniform(const std::string& name, const uint64_t size, const uint64_t binding);

            template<typename T>
            void writeUniform(const std::string& name, const T* data, const uint64_t offset, const size_t len) {
                if (_uniforms.find(name) == _uniforms.end())
                    return;
                
                _uniforms[name]->write(data, offset, len);
            }

            const size_t getUniformLen() const;
            const Uniform& getUniform(const size_t at) const;
            const Shader& getShader() const;
        };
    }
}

#endif