#include "StaticMesh.h"

StaticMesh::StaticMesh()
{
	label = "Static Mesh";
}

StaticMesh::StaticMesh(AssetHandle<Model> pModelHandle)
	: modelHandle(pModelHandle)
{
	label = "Static Mesh";

	Init();
}

void StaticMesh::Init()
{
	cached_model = AssetManager::Get().GetModel(modelHandle);
	
	//materialInstances.clear();
}

std::vector<Property> StaticMesh::GetProperties()
{
	return
	{
		{ PropertyType::Asset, cached_model, "Model" }
	};
}

bool StaticMesh::SetModelHandle(AssetHandle<Model> pModelHandle)
{
	modelHandle = pModelHandle;
	cached_model = AssetManager::Get().GetModel(modelHandle);

	if(cached_model == nullptr)
		return false;
	return true;
}

bool StaticMesh::SetMaterialAtSlot(AssetHandle<Material> pMaterialHandle, unsigned int slot)
{
	if (cached_model == nullptr)
		return false;
	cached_model->materials[slot] = pMaterialHandle;
	return true;
}

void StaticMesh::Draw()
{
	if(cached_model != nullptr)
		cached_model->Draw();
	//material->Activate();
	//model->Draw(material->GetShader());
}