#pragma once

#include "Core/Objects/Components/Component.h"
#include "Core/Interfaces/Renderable.h"
#include "Data/Model.h"
#include "Data/Material.h"

// TO DO: Add Renderable Interface 

class StaticMesh: public Component, public IRenderable
{
public:
	StaticMesh();

	std::vector<Property> GetProperties() override;
	void Draw() override;

private:
	Model* model;
	Material* material;
};