#include "2DRenderer.hpp"
#include <GLFW/glfw3.h>
#include <Gfx/Render.h>

using namespace j2l::GraphX;

Renderer2D::Renderer2D(const uint32_t width, const uint32_t height, const char* title) {
    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE) {
        printf("Failed to initialize glfw !\n");
        return;
    }

    // Tell glfw to not use opengl
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create window
    _window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (_window == NULL) {
        printf("Failed to create window !\n");
        return;
    }

    // Create a surface from the glfw window created above
    // to draw on it.

    #if defined(_WIN32)
        _surface = GfxSurfaceCreate(glfwGetWin32Window(_window), GetModuleHandle(NULL), width, height);
    #elif defined(__linux__)
        _surface = GfxSurfaceCreate(glfwGetX11Display(), glfwGetX11Window(_window), width, height);
    #elif defined(__APPLE__)
        _surface = GfxSurfaceCreate(getMetalLayer(_window), width, height);
    #else
        #error Incompatible platform !
    #endif
    
    _ctx = GfxContextCreate(_surface);

    _shadersLen = 1;
    _shaders    = new Shader*[_shadersLen];

    _shaders[0] = new Shader(this, "shaders/color.wgsl");

    _materialsLen   = 1;
    _materials      = new Material*[_materialsLen];

    _materials[0] = new Material(this, *_shaders[0]);

    float vertices[] = {
        -.5f, -.5f,     1.f, 0.f, 0.f,
         .5f, -.5f,     0.f, 1.f, 0.f,
         .0f,  .5f,     0.f, 0.f, 1.f,
    };

    uint16_t indices[] = { 0, 1, 2 };

    _meshes.push_back(new Mesh(this, vertices, 15, indices, 3));
    _materials[0]->setUniform("time", sizeof(float), 0);

    _meshRenderers.push_back(new MeshRenderer(this, *_meshes[0], *_materials[0]));
}

Renderer2D::~Renderer2D() {
    for (size_t i = 0; i < _meshRenderers.size(); i++)
        delete _meshRenderers[i];

    for (size_t i = 0; i < _meshes.size(); i++)
        delete _meshes[i];

    for (size_t i = 0; i < _materialsLen; i++)
        delete _materials[i];
    
    delete [] _materials;

    for (size_t i = 0; i < _shadersLen; i++)
        delete _shaders[i];

    delete [] _shaders;

    GfxContextDelete(_ctx);
    GfxSurfaceDelete(_surface);

    glfwDestroyWindow(_window);
    glfwTerminate();
}

const bool Renderer2D::shouldClose() const {
    return glfwWindowShouldClose(_window);
}

void Renderer2D::render() const {
    // Get the window size and resize the context
    // swapchain. The GfxContextResize(...) handle
    // the case when the window have the same size
    // that the previous frame.
    uint32_t width, height;
    glfwGetWindowSize(_window, (int*)&width, (int*)&height);
    GfxContextResize(_ctx, width, height);

    // You'll need to call this before
    // any rendering operations.
    GfxPostRender(_ctx);

    // Create a command encoder. A command encoder
    // can record multiple render pass.
    GfxCommandEncoder commandEncoder = GfxCommandEncoderCreate(_ctx);

    float time = static_cast<float>(glfwGetTime());
    _materials[0]->writeUniform("time", &time, 0, 1);
    
    if (_meshRenderers.size() > 0) {
        // Draw all meshes
        for (size_t i = 0; i < _meshRenderers.size(); i++) {
            // Create a render pass with the pipeline created
            // above and begin recording render pass command(s).
            GfxRenderPass renderPass = GfxRenderPassBegin(_ctx, commandEncoder, _meshRenderers[i]->getRenderPipeline());

            _meshRenderers[i]->draw(renderPass);

            // End recording render pass command for the current
            // render pass.
            GfxRenderPassEnd(renderPass);
        }
    }

    // End recording render pass for the current encoder.
    GfxCommandEncoderEnd(_ctx, &commandEncoder, 1);

    // We can safely delete the render pass and the command
    // encoder.
    // GfxRenderPassDelete(renderPass);
    GfxCommandEncoderDelete(commandEncoder);
    
    // Render the current frame.
    GfxRender(_ctx);

    glfwPollEvents();
}

const GfxContext Renderer2D::getContext() const {
    return _ctx;
}

Shader* Renderer2D::createShader(const char* path) const {
    return new Shader(this, path);
}