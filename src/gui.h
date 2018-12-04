#ifndef GUI_H
#define GUI_H

#include <external/imgui/imgui.h>

#include <external/imgui/imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class BasicGUI {
  GLFWwindow* window;

  public:
    BasicGUI(GLFWwindow* window);
    void render();
};

#endif
