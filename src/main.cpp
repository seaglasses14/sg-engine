#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "Core/Log.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Scene/Scene.h"
#include "Core/Input/InputManager.h"
#include "object.h"
#include "camera.h"
#include <Core/GLFW_Context.h>
#include "Core/GUI/GUI.h"
#include "Core/AssetPipeline/AssetManager.h"

void processInput(GLFWwindow* window);

//Globals

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;
const bool WIREFRAME_MODE = false;
const bool DEPTH_TESTING = true;

//Camera
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

int main()
{
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	GLFW_Context* GLFWcontext = new GLFW_Context();
	Scene* scene = new Scene();
	scene->mainCamera = &camera;
	GLFWcontext->scene = scene;
	GLFWcontext->GetWindow();
	
	GUI* gui = new GUI(GLFWcontext->GetWindow(), scene);

	stbi_set_flip_vertically_on_load(true);

	//**************************** DATA CREATION *****************************************

	// Initializes AssetManager
	AssetManager::Get().Init();
	
	InputAction* ia = new InputAction{ std::string("Forward"), ActionValueType::Bool };
	
	auto& IM = InputManager::Get();
	IM.inputActions.push_back(ia);

	InputManager::Get().inputMapping.AddActionToInput(Key_W, ia);
	InputManager::Get().inputMapping.AddActionToInput(Key_Up, ia);
	InputManager::Get().inputMapping.AddActionToInput(Key_S, new InputAction{ std::string("Backward"), ActionValueType::Bool } );
	InputManager::Get().inputMapping.AddActionToInput(Key_A, new InputAction{ std::string("Left"), ActionValueType::Bool } );
	InputManager::Get().inputMapping.AddActionToInput(Key_D, new InputAction{ std::string("Right"), ActionValueType::Bool } );
	InputManager::Get().inputMapping.AddActionToInput(Key_Q, new InputAction{ std::string("Downward"), ActionValueType::Bool } );
	InputManager::Get().inputMapping.AddActionToInput(Key_E, new InputAction{ std::string("Upward"), ActionValueType::Bool } );
	InputManager::Get().inputMapping.AddActionToInput(Mouse_Delta, new InputAction{ std::string("Look"), ActionValueType::Float2D } );
	
	scene->Init();

	InputManager::Get().BindListener("Forward", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(FORWARD, deltaTime); });
	InputManager::Get().BindListener("Backward", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(BACKWARD, deltaTime); });
	InputManager::Get().BindListener("Left", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(LEFT, deltaTime); });
	InputManager::Get().BindListener("Right", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(RIGHT, deltaTime); });
	InputManager::Get().BindListener("Downward", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(DOWNWARD, deltaTime); });
	InputManager::Get().BindListener("Upward", Pressed, [scene, &deltaTime](const ActionValue &){ scene->mainCamera->ProcessDirectionInput(UPWARD, deltaTime); });
	InputManager::Get().BindListener("Look", Pressed, [scene, &deltaTime](const ActionValue & value){
		const glm::vec2& delta = std::get<glm::vec2>(value);
		scene->mainCamera->ProcessRotationInput(delta.x, delta.y);
	});

	bool showDemoWindow = true;
	bool showWindow = false;
	//**************************** RENDER *****************************************

	scene->CreateRotating("RotatingCube");
	scene->Begin();

	while (GLFWcontext->IsRunning())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		InputManager::Get().ProcessEvents();
		//processInput(GLFWcontext->GetWindow());

		InputManager::Get().RefreshPerFrameValue();

		scene->Update(deltaTime);

		if (glfwGetWindowAttrib(GLFWcontext->GetWindow(), GLFW_ICONIFIED))
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}

		gui->StartDrawing();

		/*
		ImGui::Begin("First Window");
		ImGui::Text("Mammt");
		ImGui::Checkbox("Show Demo", &showDemoWindow);
		ImGui::Checkbox("Show Other Window", &showWindow);
		ImGui::SliderFloat("float", &f, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::ColorEdit3("ClearColor", (float*)&clear_color);

		if(ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / io.Framerate, io.Framerate);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000 * deltaTime, 1 / deltaTime);
		ImGui::End();

		if (showWindow)
		{
			ImGui::Begin("Window", &showWindow);
			ImGui::Text("New Window");
			if (ImGui::Button("Close"))
				showWindow = false;
			ImGui::End();
		}

		*/



		// processInput(GLFWcontext->GetWindow());


		//Demo Window
		if (showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);

		gui->Draw();
		scene->PreRender();
		scene->FirstPass();
		gui->DrawViewport(scene->fb.tex);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 800, 800);
		gui->Render();
		
		

		//**************************** DRAWING *****************************************
		/*
		//lightPos = glm::vec3(sin(glfwGetTime()) * 8, 0, cos(glfwGetTime()) * 8);
		lightPos = glm::vec3(0, 0, -10 + 5 * sin(glfwGetTime()));
		
		glm::mat4 lightModel2 = glm::translate(lightModel, lightPos);
		lightSource.SetModel(lightModel2);

		glm::mat4 normalSphere = glm::transpose(glm::inverse(view * sphereModel));

		planetMaterial.AddUniform("normalMat", normalSphere);
		planetMaterial.AddUniform("lightPos", lightPos);
		planetMaterial.AddUniform("light.constant", 1.0f);
		planetMaterial.AddUniform("light.linear", 0.02f);
		planetMaterial.AddUniform("light.quadratic", 0.007f);
		planetMaterial.AddUniform("directLight.direction", glm::vec3(view * glm::normalize(glm::vec4(-0.2f, -1.0f, -0.3f, 0))));
		planetMaterial.AddUniform("light.position", lightPos);
		planetMaterial.AddUniform("viewPos", camera.Position);

		worldGrid.Activate(view, projection);
		worldGrid.Draw();

		lightSource.Activate(view, projection);
		lightSource.Draw();


		sphere.Activate(view, projection);
		sphere.Draw();
		*/		

		GLFWcontext->AtEndOfLoop();
	}

	//object.Clean();

	gui->Shutdown();

	glfwDestroyWindow(GLFWcontext->GetWindow());
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	auto& IM = InputManager::Get();
	//if(IM.mode != SceneViewer)
	//	return;
	
	/*
	if (IM.IsKeyDown(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	if (IM.IsKeyDown(GLFW_KEY_W))
		camera.ProcessDirectionInput(FORWARD, deltaTime);
	if (IM.IsKeyDown(GLFW_KEY_S))
		camera.ProcessDirectionInput(BACKWARD, deltaTime);
	if (IM.IsKeyDown(GLFW_KEY_A))
		camera.ProcessDirectionInput(LEFT, deltaTime);
	if (IM.IsKeyDown(GLFW_KEY_D))
		camera.ProcessDirectionInput(RIGHT, deltaTime);
	if (IM.IsKeyDown(GLFW_KEY_Q))
		camera.ProcessDirectionInput(DOWNWARD, deltaTime);
	if (IM.IsKeyDown(GLFW_KEY_E))
		camera.ProcessDirectionInput(UPWARD, deltaTime);
	*/
	camera.ProcessRotationInput(IM.GetMouseDeltaX(), IM.GetMouseDeltaY());	
}