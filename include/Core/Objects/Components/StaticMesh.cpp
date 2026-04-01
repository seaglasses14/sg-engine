#include "StaticMesh.h"

StaticMesh::StaticMesh(AssetHandle<Model> pModelHandle)
	: modelHandle(pModelHandle)
{
	label = "Static Mesh";

	Init();
}

void StaticMesh::Init()
{
	cached_model = AssetManager::Get().GetModel(modelHandle);
	
	materialInstances.clear();

	for()
}

std::vector<Property> StaticMesh::GetProperties()
{
	return
	{
		{ PropertyType::Asset, model, "Model" },
		{ PropertyType::Asset, cached_material, "Material" }
	};
}

void StaticMesh::Draw()
{
	material->Activate();
	model->Draw(material->GetShader());
}