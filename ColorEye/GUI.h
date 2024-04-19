#pragma once

#include <string>
#include "Utils.h"
#include "ColorUtils.h"

namespace Texture
{
	inline GLuint clipboard;
}

namespace Font {
	namespace OpenSans {
		inline ImFont* px10, *px20, *px30;
	}
}

namespace GUI
{
	GLFWwindow* window = nullptr;
	int windowWidth = 340;
	int windowHeight = 720;

	Vec3<int> rgb255(255, 255, 255);
	Vec3<float>rgb01(1, 1, 1);
	std::string hexColor = "";
	Vec3<int> hsv(0, 0, 0);

	ImGuiKey key = ImGuiKey_P; std::string bindedMsg = "Binded Key: " + std::to_string(key);

	void Render()
	{
		//End of the main window
		ImGui::End();
		ImGui::Render();

		glViewport(0, 0, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);

		glClearColor(0.10f, 0.10f, 0.10f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

	}

	void clipboardImageButton(std::string id, const std::string& cpy_str)
	{
		ImGui::PushID(id.c_str());
		if (ImGui::ImageButton((void*)(intptr_t)Texture::clipboard, ImVec2((float)20, (float)20), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 1, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f))) {
			Utils::CopyStringToClipboard(cpy_str);
		}
		ImGui::PopID();
	}

	void MainWindow()
	{
		ImGui::Begin("Pigeon Client", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

		//Resize Imgui window
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		ImVec2 newSize = ImVec2(windowWidth * 1.0f, windowHeight * 1.0f);
		ImGui::SetWindowSize(newSize);

		ImGui::BeginChild("ColorBox", ImVec2(windowWidth, 320), true);

		rgb01 = ColorUtils::rgb255To01(rgb255);
		hexColor = ColorUtils::rgb255ToHex(rgb255);
		hsv.importHSV(ColorUtils::rgb255toHSV(rgb255.x, rgb255.y, rgb255.z));

		ImGui::SetCursorPosX(windowWidth / 2 - 150);
		ImGui::SetCursorPosY(320 / 2 - 150);
		ImGui::ColorButton("##MyColor", rgb01.to_ImVec4(), ImGuiColorEditFlags_NoDragDrop, ImVec2(300, 300));

		ImGui::EndChild(); //End of ColorBox

		ImGui::BeginChild("InfoBox", ImVec2(windowWidth, windowHeight - 356), true);

		ImGui::PushFont(Font::OpenSans::px30);
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex((ImGuiKey)key)))
		{
			rgb255 = ColorUtils::getCurrentPixelColor();
		}

		ImGui::SetCursorPosY(10);
		ImGui::SetCursorPosX(20); ImGui::Text("RGB(0-1): {%s}", rgb01.to_string().c_str()); ImGui::SameLine(); 
		clipboardImageButton("Clipboard1", rgb01.to_string());
		ImGui::Dummy(ImVec2(0.0f, 3));

		ImGui::SetCursorPosX(20); ImGui::Text("RGB(0-255): {%s}", rgb255.to_string().c_str()); ImGui::SameLine();
		clipboardImageButton("Clipboard2", rgb255.to_string());
		ImGui::Dummy(ImVec2(0.0f, 3));

		ImGui::SetCursorPosX(20); ImGui::Text("HEX: {%s}", hexColor); ImGui::SameLine();
		clipboardImageButton("Clipboard3", hexColor);
		ImGui::Dummy(ImVec2(0.0f, 3));

		ImGui::SetCursorPosX(20); ImGui::Text("HSV: {%s}", hsv.to_string().c_str()); ImGui::SameLine();
		clipboardImageButton("Clipboard4", hsv.to_string());
		
		ImGui::EndChild(); //End of InfoBox

		ImGui::BeginChild("KeyBindBox", ImVec2(windowWidth, 36), true);

		ImGui::PushItemWidth(windowWidth);
		ImGui::PushFont(Font::OpenSans::px20);
		ImGui::InputText("##Key", &bindedMsg, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_NoUndoRedo);
		if (ImGui::IsItemActive())
		{
			bool mouseInput = false;
			for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().KeysDown); i++) {
				if (ImGui::IsKeyPressed((ImGuiKey)i)) {
					for (int key = 655; key <= 659; key++)
					{
						if ((ImGuiKey)i == key)
							mouseInput = true;
					}
					if (mouseInput)
						break;

					key = (ImGuiKey)i;
					bindedMsg = "Binded Key: " + std::to_string(key);
					ImGui::SetWindowFocus(NULL);
					break;
				}
			}
		}
		
		ImGui::EndChild(); //End of KeyBindBox

		ImGui::End();
	}
}

namespace ImInit
{
	void ImGuiInit(GLFWwindow* window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();


		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(0.00f, 0.00f);
		style.FramePadding = ImVec2(5.00f, 2.00f);
		style.CellPadding = ImVec2(6.00f, 6.00f);
		style.ItemSpacing = ImVec2(0.00f, 0.00f);
		style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
		style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
		style.IndentSpacing = 25;
		style.ScrollbarSize = 15;
		style.GrabMinSize = 10;
		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = 1;
		style.TabBorderSize = 1;
		style.WindowRounding = 7;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		style.ScrollbarRounding = 9;
		style.GrabRounding = 3;
		style.LogSliderDeadzone = 4;
		style.TabRounding = 4;

		/*ImGui::GetStyle().WindowPadding = ImVec2(0.00f, 0.00f);
		ImGui::GetStyle().FrameRounding = 0.f;
		ImGui::GetStyle().ItemSpacing = ImVec2(0.00f, 0.00f);*/
	}

	void StartImGuiFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//This is to make the first imgui window fill all the sdl window
		ImGui::SetNextWindowSize(ImVec2(GUI::windowWidth, GUI::windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}

	void CleanUp()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(GUI::window);
		glfwTerminate();
	}
}