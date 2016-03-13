#define _GLIBCXX_USE_CXX11_ABI 0
#include "WorldObject.h"

WorldObject::WorldObject(Leadwerks::Entity* parent, class Scene* scene)
{
    this->_scene = scene;
    this->_position = new Leadwerks::Vec3();
}

WorldObject::~WorldObject()
{
    //dtor
}

void WorldObject::Update()
{

}

void WorldObject::DrawContext()
{

}

void WorldObject::SetScene(class Scene* scene)
{
    this->_scene = scene;
}


void WorldObject::SetPosition(Leadwerks::Vec3 position, bool global = false)
{
    Leadwerks::Pivot::SetPosition(position,global);
    this->_position = new Leadwerks::Vec3(position.x,position.y,position.z);
}

void WorldObject::SetPosition(float x, float y, float z, bool global = false)
{
    Leadwerks::Pivot::SetPosition(x,y,z,global);
    this->_position = new Leadwerks::Vec3(x,y,z);
}

Leadwerks::Vec3 WorldObject::GetPosition(bool global)
{
    return Leadwerks::Vec3(this->_position->x,this->_position->y,this->_position->z);
}


