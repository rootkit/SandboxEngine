#define _GLIBCXX_USE_CXX11_ABI 0
#include "InventoryItem.h"

InventoryItem::InventoryItem(class Scene* scene)
{
	this->_scene = scene;
    this->_position = new Leadwerks::Vec2(0,0);
}

InventoryItem::~InventoryItem()
{
    //dtor
}

void InventoryItem::SetPosition(Leadwerks::Vec2* position)
{
	this->_position = position;
}

void InventoryItem::SetPosition(float x, float y)
{
	delete this->_position;
	this->_position = new Leadwerks::Vec2(x,y);
}

void InventoryItem::SetWorldObject(class WorldObject* object)
{
	this->_worldObject = object;
}

void InventoryItem::SetWidth(float value)
{
	this->_width = value;
}

Leadwerks::Vec2* InventoryItem::GetPosition()
{
	return this->_position;
}

void InventoryItem::DrawContext()
{
	this->_scene->context->DrawImage(this->_worldObject->GetHudIcon64(),
									this->_position->x,
									this->_position->y);	
    this->_scene->context->SetColor(1,1,1);
    this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
    this->_scene->context->DrawRect(this->_position->x,this->_position->y,this->_width,this->_width,1);
}

void InventoryItem::Update()
{

}

void InventoryItem::InputUpdate()
{

}
