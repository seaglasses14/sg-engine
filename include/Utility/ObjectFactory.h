#pragma once
#include <string>

class Object;
class GObject;
class Material;

class ObjectFactory
{
public:
	static Object* genWorldGrid(Material* pMaterial, unsigned int size, float stride);
	//static Object genPlane(Material* pMaterial, float size = 100);
	//static Object genSimpleCube(Material* pMaterial, float edge_length = 1);
	//static Object genCube(Material* pMaterial, float edge_length = 1);
	static GObject* Cube(const std::string& label);
	//static Object genUVSphere(Material* pMaterial, int stacks = 20, int slices = 20, float radius = 1);
};