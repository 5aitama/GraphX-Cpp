#ifndef APPLE_EXT_H
#define APPLE_EXT_H

#include <GLFW/glfw3.h>
#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

void* getMetalLayer(GLFWwindow* window);

#endif