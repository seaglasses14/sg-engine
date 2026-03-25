#include "StaticMesh.h"

StaticMesh::StaticMesh()
{
	label = "Static Mesh";
}

std::vector<Property> StaticMesh::GetProperties()
{
	return
	{
		{ PropertyType::Asset, model, "Model" },
		{ PropertyType::Asset, material, "Material" }
	};
}

void StaticMesh::Draw()
{
	material->Activate();
	model->Draw(material->GetShader());
}