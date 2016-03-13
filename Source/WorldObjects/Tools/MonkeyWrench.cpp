#define _GLIBCXX_USE_CXX11_ABI 0
#include "MonkeyWrench.h"

MonkeyWrench::MonkeyWrench(Leadwerks::Entity* parent,class Scene* scene)
    : WorldObject(parent,scene)
{
    this->entity = Leadwerks::Prefab::Load("Prefabs/Tools/MonkeyWrench.pfb");
    Leadwerks::Shape* physicsShape = Leadwerks::Shape::Load("Prefabs/Tools/MonkeyWrench.phy");
    this->SetShape(physicsShape);
    this->entity->SetParent(this,false);
    this->SetPhysicsMode(Leadwerks::Entity::CharacterPhysics);
    this->SetCollisionType(Leadwerks::COLLISION_PROP);
    this->SetMass(3);
}

MonkeyWrench::~MonkeyWrench()
{
    //dtor
}

void MonkeyWrench::Update()
{
    WorldObject::Update();
    this->SetPosition(this->entity->GetPosition(true),true);
}

void MonkeyWrench::DrawContext()
{
    WorldObject::DrawContext();

    this->_scene->context->SetBlendMode(Blend::Alpha);
    this->_scene->context->SetColor(1,1,1);
    this->_scene->context->DrawText("X:" + boost::lexical_cast<std::string>(this->entity->GetPosition(true).y),0,0);
    this->_scene->context->SetBlendMode(Blend::Solid);
}

void MonkeyWrench::SetPosition(Leadwerks::Vec3 position, bool global = false)
{
    WorldObject::SetPosition(position,global);
    this->entity->SetPosition(position,global);
}

void MonkeyWrench::SetPosition(float x, float y, float z, bool global = false)
{
    WorldObject::SetPosition(x,y,z,global);
    this->entity->SetPosition(x,y,z,global);
}

Leadwerks::Vec3 MonkeyWrench::GetPosition(bool global)
{
    return Leadwerks::Vec3(this->_position->x,this->_position->y,this->_position->z);
}
