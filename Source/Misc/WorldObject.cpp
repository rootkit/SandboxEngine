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

void WorldObject::SetName(string value)
{
	this->_name = value;
}

void WorldObject::SetDescription(string value)
{
	this->_description = value;
}

void WorldObject::SetInteractive(bool value)
{
	this->_interactive = value;
}

void WorldObject::SetEquippably(bool value)
{
	this->_equippably = value;
}

void WorldObject::SetType(string value)
{
	this->_type = value;
}

void WorldObject::SetSubType(string value)
{
	this->_subType = value;
}

bool WorldObject::GetInteractive()
{
	return this->_interactive;
}

bool WorldObject::GetEquippably()
{
	return this->_equippably;
}

string WorldObject::GetType()
{
	return this->_type;
}

string WorldObject::GetSubType()
{
	return this->_subType;
}

string WorldObject::GetDescription()
{
	return this->_description;
}

string WorldObject::GetName()
{
	return this->_name;
}
