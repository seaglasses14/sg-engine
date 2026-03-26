#pragma once

class GObject;

class ObjectFactory
{
public:
	static Object genPlane(Material* pMaterial, float size = 100);
	static Object genSimpleCube(Material* pMaterial, float edge_length = 1);
	static Object genCube(Material* pMaterial, float edge_length = 1);
	static GObject WorldGrid(const std::string& label, unsigned int size = 100, float stride = 5);
	static Object genUVSphere(Material* pMaterial, int stacks = 20, int slices = 20, float radius = 1);
};