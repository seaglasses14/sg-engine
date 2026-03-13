#include "Scene.h"
#include "Core/Log.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>


Scene::Scene()
	: baseVertex("shaders/base.vert", "shaders/base.frag"), whiteMaterial(Material(&baseVertex, nullptr)), worldGrid(Shapes::genWorldGrid(&whiteMaterial, 50, 20.f))
{
	whiteMaterial.AddUniform("Color", glm::vec3(1.f, 1.f, 1.f));

	GenerateFrameBuffer();

	objects = std::vector<GObject*>();
}

void Scene::PreRender()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::FirstPass()
{
	BindFrameBuffer();
	
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(mainCamera->Fov), static_cast<float>(800) / 600, 0.1f, 1000.0f);

	glm::mat4 view = mainCamera->GetViewMatrix();

	worldGrid.Activate(view, projection);
	worldGrid.Draw();
}

void Scene::SecondPass()
{
	
}

void Scene::AddObject(const std::string& name)
{
	std::string label = GenerateUniqueLabel(name);

	objects.push_back(new GObject(label));
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
			if (obj->label.compare(label) == 0)
			{
				exists = true;
				count++;
			}
		}
	} while (exists);

	return label;
}

void Scene::BindFrameBuffer()
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
		GL_UNSIGNED_BYTE, NULL);
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
