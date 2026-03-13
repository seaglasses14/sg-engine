#pragma once

#include "Core/Objects/Components/Component.h"
#include "Data/Model.h"
#include "Data/Material.h"

// TO DO: Add Renderable Interface 

class StaticMesh: public Component
{
public:
	StaticMesh();

	std::vector<Property> GetProperties() override;

private:
	Model* model;
	Material* material;

	void UpdateModel();
};