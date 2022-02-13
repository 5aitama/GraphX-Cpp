#include <I2DRenderer.hpp>
#include <Factory.hpp>

#include <iostream>

int main(int argc, char** argv) {
    // Create a renderer.
    // To create fullscreen window
    // you set the resolution to 0.
    j2l::GraphX::I2DRenderer* renderer = j2l::GraphX::Factory::create2DRenderer(800, 600, "GraphX");
    
    while (!renderer->shouldClose()) {
        
        // Here draw anythings you want !
        /// ...

        // Don't forget to call render at
        // the end otherwise it will show
        // nothing !
        renderer->render();   
    }

    return EXIT_SUCCESS;
}
