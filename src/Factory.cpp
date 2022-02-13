#include <iostream>
#include <Factory.hpp>
#include "2DRenderer.hpp"

j2l::GraphX::I2DRenderer* j2l::GraphX::Factory::create2DRenderer(const int width, const int height, const char* title) {
    j2l::GraphX::Renderer2D* renderer2d = new j2l::GraphX::Renderer2D(width, height, title);
    return renderer2d;
}