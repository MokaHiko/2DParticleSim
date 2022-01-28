#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SpriteRenderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class ParticleSimulator
{
public:
	void Init();

	void HandleInput();
	void Update();
	void Render();
	
	void Clean();
	inline bool isClosed() { return glfwWindowShouldClose(window); }
public:
	float GetFPS();

	// game state
	static bool Keys[1024];
	static glm::vec2 MousePos;
	static bool MouseButtons[7];
private:
	GLFWwindow* window;
	SpriteRenderer* spriteRenderer;

	// ui
	bool uiSelected = false;

	// time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float currentFrame;


	float frames = 0;
	float lastTime = 0;
	float timeDiff;
};

