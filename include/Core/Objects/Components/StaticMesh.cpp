#include "StaticMesh.h"

StaticMesh::StaticMesh(AssetHandle<Material> pMaterialHandle)
	: materialHandle(pMaterialHandle)
{
	label = "Static Mesh";

	cached_material = AssetManager::Get().GetMaterial(materialHandle);
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