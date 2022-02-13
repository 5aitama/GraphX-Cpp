#include "appleExt.hpp"

#include <Foundation/Foundation.h>
#include <QuartzCore/CAMetalLayer.h>

void* getMetalLayer(GLFWwindow* window) {
    id metal_layer = NULL;
    NSWindow *ns_window = glfwGetCocoaWindow(window);
    [ns_window.contentView setWantsLayer:YES];

    metal_layer = [CAMetalLayer layer];
    [ns_window.contentView setLayer:metal_layer];

    return metal_layer;
}