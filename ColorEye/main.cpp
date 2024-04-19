#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>

#include "GUI.h"
#include "ColorUtils.h"
#include "Utils.h"

using namespace GUI;

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window  = glfwCreateWindow(windowWidth, windowHeight, "ColorEye", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	glewInit();
	glViewport(0, 0, windowWidth, windowHeight);

	ImInit::ImGuiInit(window);

	Utils::generateTexture("Images/clipboard.png", Texture::clipboard);
	
	Font::OpenSans::px20 = ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/OpenSans-Variable.ttf", 20);
	Font::OpenSans::px20 = ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/OpenSans-Variable.ttf", 30);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

		ImInit::StartImGuiFrame();

		GUI::MainWindow();

		GUI::Render();
    }

	ImInit::CleanUp();

	return 0;
}