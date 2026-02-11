#define _STDCALL_SUPPORTED
#include <imgui_internal.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include "mygui.h"

using namespace ImGui;
using namespace std;
using namespace filesystem;

string descript;
// wstring descript;
map<string, string> objectList;
const char *mdPath = "readme.md";
fstream fp;
int fsize;
vector<string> line;
#define Sname it->first
#define Sdescript it->second

int main()
{

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
	{
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window *window = SDL_CreateWindow("Diretory Description Generator", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
	if (window == nullptr)
	{
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (gl_context == nullptr)
	{
		printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO &io = GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	StyleColorsDark();

	ImGuiStyle &style = GetStyle();
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool done = false;
	bool show_demo_window = true;
	bool show_another_window = false;
	bool show_save_done = false;
	ImFont *font = io.Fonts->AddFontFromFileTTF(
		"C:/Windows/Fonts/msyh.ttc",
		24,
		nullptr,
		io.Fonts->GetGlyphRangesChineseFull());
	IM_ASSERT(font != nullptr);
	const ImGuiViewport *viewport = ImGui::GetMainViewport();
	GUIsetcolor();

	fsize = file_size(mdPath);
	fp = fstream{mdPath, ios::in};
	if (exists(mdPath))
	{
		for (string t; getline(fp, t);)
		{
			line.push_back(t);
		}
		for (int i = 0; i < line.size(); i++)
		{
			string name, descript;
			int pos = line[i].find(" |");
			descript = line[i].substr(0, pos);
			name = line[i].substr(pos + 3, line[i].size() - pos - 5);
			objectList[name] = descript;
		}
	}
	fp.close();
	directory_iterator list(current_path());
	for (auto &it : list)
	{
		string fileName = it.path().filename().string();
		auto pos = fileName.find('.');
		if (pos != fileName.npos)
		{
			fileName.erase(fileName.begin() + pos, fileName.end());
		}
		if (pos == 0)
			continue;
		objectList.try_emplace(fileName, "");
	}
	map<string, char[256]> buffer;
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		strcpy(buffer[it->first], it->second.c_str());
	}
	while (!done)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
		{
			SDL_Delay(10);
			continue;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		NewFrame();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		Begin("Diretory Description Generator", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);
		{
			// 窗口逻辑开始
			BeginChild("##menu", ImVec2(180, 40), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened);
			if (ImGui::BeginMenu("主题（Other）"))
			{
				if (ImGui::MenuItem("暗黑（Dark）"))
				{
					ImGui::StyleColorsDark();
				}
				if (ImGui::MenuItem("明亮（Light）"))
				{
					ImGui::StyleColorsLight();
				}
				if (ImGui::MenuItem("经典（Classic）"))
				{
					ImGui::StyleColorsClassic();
				}
				if (ImGui::MenuItem("mumu特调"))
				{
					GUIsetcolor();
				}

				ImGui::EndMenu();
			}
			EndChild();
			BeginChild("##colors", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened);
			BeginChild("##First", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened);
			for (auto it = objectList.begin(); it != objectList.end(); it++)
			{
				Text(it->first.c_str());
			}
			EndChild();
			SameLine();
			BeginChild("##Second", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened);
			for (auto it = objectList.begin(); it != objectList.end(); it++)
			{
				ImGui::InputText(string("##input" + it->first).c_str(), buffer[it->first], sizeof(buffer));
				objectList[it->first] = string(buffer[it->first]);
			}
			EndChild();
			if (Button("save"))
			{
				fp.open(mdPath, ios::out | ios::trunc);
				fp.close();
				fp.open(mdPath, ios::out | ios::app);
				for (auto it = objectList.begin(); it != objectList.end(); it++)
				{
					fp << (it->second + " | " + it->first + "  \n").c_str();
				}
				fp.close();
				show_save_done = true;
			}
			if (show_save_done)
			{
				SameLine();
				Text("save done");
			}

			EndChild();
		}

		End();
		Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	DestroyContext();

	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}