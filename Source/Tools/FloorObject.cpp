#define _GLIBCXX_USE_CXX11_ABI 0
#include "FloorObject.h"

FloorObject::FloorObject(Scene* scene)
{
	this->_scene = scene;

	this->_prefab = Leadwerks::Prefab::Load("Prefabs/Structural/metal_floor.pfb");
	this->_prefab->SetShape(Leadwerks::Shape::Load("Prefabs/Structural/metal_floor.phy"));

	this->_prefab->SetPosition(0,1,0,true);
}

FloorObject::~FloorObject()
{
    //dtor
}

void FloorObject::Update()
{

}
