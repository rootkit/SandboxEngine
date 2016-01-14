#define _GLIBCXX_USE_CXX11_ABI 0
#include "BuildMatrixBlockObject.h"

BuildMatrixBlockObject::BuildMatrixBlockObject(std::string prefabPath, Leadwerks::Vec3* position, Leadwerks::Vec3* blockSize)
{
    this->_entity = Leadwerks::Prefab::Load("Prefabs/Structural/BlockSet/Developer/CENTER_BLOCK_1.pfb");
	this->_entity->SetShape(Leadwerks::Shape::Load("Prefabs/Structural/BlockSet/Developer/CENTER_BLOCK_1.phy"));

    this->_entity->SetPosition(Leadwerks::Vec3(position->x,position->y,position->z),true);
}

BuildMatrixBlockObject::~BuildMatrixBlockObject()
{
    //dtor
}
