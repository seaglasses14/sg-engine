#include "Scene.h"
#include "Core/Log.h"
#include "Utility/DataTypes.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include "Utility/ObjectFactory.h"
#include "Core/Objects/Components/Component.h"
#include "Core/Interfaces/Renderable.h"
#include "Data/Material.h"

Scene::Scene()
{
	GenerateFrameBuffer();

	objects = std::vector<GObject*>();
	objects.push_back(new GObject("Empty"));
	//objects.push_back(ObjectFactory::Cube("Cube"));

}

void Scene::PreRender()
{
	ResizeFrameBuffer();
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::FirstPass()
{
	BindFrameBuffer();
	ImVec2 windowSize = ImGui::GetContentRegionAvail();
	//LOG_INFO(std::to_string(windowSize.x));
	//LOG_INFO(std::to_string(windowSize.y));
	glViewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
	
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection;
	
	projection = glm::perspective(glm::radians(mainCamera->Fov), windowSize.x/windowSize.y, 0.1f, 1000.0f);

	glm::mat4 view = mainCamera->GetViewMatrix();

	RenderContext context({ projection, view, glm::vec3(1.0f, 1.0f, 0.0f) });

	for (GObject* obj : objects)
	{
		for (auto& comp : obj->components)
		{
			if (auto* renderable = dynamic_cast<IRenderable*>(comp))
			{
				renderable->Draw(context);
			}
		}
	}
	worldGrid->Activate(view, projection);
	worldGrid->Draw();
}

void Scene::SecondPass()
{
	
}

void Scene::Init()
{
	Material* mat = AssetManager::Get().GetMaterial(AssetHandle<Material>({ "BaseMaterial" }));
	worldGrid = ObjectFactory::genWorldGrid(mat, 100, 10);
}

void Scene::AddObject(const std::string& name)
{
	std::string label = GenerateUniqueLabel(name);

	objects.push_back(ObjectFactory::Cube(label));
}

std::string Scene::GenerateUniqueLabel(const std::string& name)
{
	unsigned int count = 0;
	std::string label;
	bool exists;
	do
	{
		exists = false;
		if (count > 0)
			label = name + "_" + std::to_string(count);
		else
			label = name;
		for (GObject* obj : objects)
		{
			if (obj->label == label)
			{
				exists = true;
				count++;
			}
		}
	} while (exists);

	return label;
}

void Scene::BindFrameBuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.fbo);
}

void Scene::UnbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::GenerateFrameBuffer()
{
	glGenFramebuffers(1, &fb.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fb.fbo);

	glGenTextures(1, &fb.tex);
	glBindTexture(GL_TEXTURE_2D, fb.tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB,
		GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		fb.tex, 0);

	glGenRenderbuffers(1, &fb.rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, fb.rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, fb.rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		LOG_INFO("Framebuffer Complete");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
	//	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
	//	GL_TEXTURE_2D, texture, 0);
}

void Scene::ResizeFrameBuffer()
{
	ImVec2 size = ImGui::GetContentRegionAvail();
	int width = static_cast<int>(size.x);
	int height = static_cast<int>(size.y);
	
	if (width <= 0 || height <= 0)
		return;

	if (width == fb.width && height == fb.height)
		return;
	
	fb.width = width;
	fb.height = height;
	//LOG_INFO(std::to_string(fb.width));
	//LOG_INFO(std::to_string(fb.height));
	
	glBindTexture(GL_TEXTURE_2D, fb.tex);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		nullptr
	);

	glBindRenderbuffer(GL_RENDERBUFFER, fb.rbo);

	glRenderbufferStorage(
		GL_RENDERBUFFER,
		GL_DEPTH24_STENCIL8,
		width,
		height
	);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}