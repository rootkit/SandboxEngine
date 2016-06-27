#define _GLIBCXX_USE_CXX11_ABI 0
#include "MonkeyWrench.h"

MonkeyWrench::MonkeyWrench(Leadwerks::Entity* parent,class Scene* scene)
    : WorldObject(parent,scene)
{
    ///Atributes
    this->SetType("Tool");
    this->SetSubType("Tool");
    this->SetName("Monkey Wrench");
    this->SetGUID("5d73cbc9-5887-4dde-a1f7-b5a0c5359bab");
    this->SetDescription("The monkey wrench (US) or gas grips (UK) is an adjustable wrench");
    this->SetEquippably(true);
    this->SetInteractive(true);
    ///Physics
    Leadwerks::World::SetCurrent(this->_scene->world);
    this->entity = Leadwerks::Model::Load("Models/Tools/SM_MonkeyWrench.mdl");
    Leadwerks::Shape* physicsShape = Leadwerks::Shape::Load("Models/Tools/SM_MonkeyWrench.phy");
    this->entity->SetShape(physicsShape);
    this->SetParent(this->entity);
    this->entity->SetCollisionType(Leadwerks::COLLISION_DEBRIS);
    this->entity->SetMass(10);
    WorldObject::SetPosition(0,0,0,false);
    ///Hud
    WorldObject::SetHudIcon("Hud/Tools/MonkeyWrench_128.tex",
                            "Hud/Tools/MonkeyWrench_64.tex",
                            "Hud/Tools/MonkeyWrench_32.tex");
}

MonkeyWrench::~MonkeyWrench()
{
    //dtor
    this->entity->Release();
}

void MonkeyWrench::Update()
{
    WorldObject::Update();
}

void MonkeyWrench::DrawContext()
{
    WorldObject::DrawContext();

    this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
    this->_scene->context->SetColor(1,1,1);
    //this->_scene->context->DrawText("X:" + boost::lexical_cast<std::string>(this->entity->GetPosition(true).x),0,0);
    //this->_scene->context->DrawText("Y:" + boost::lexical_cast<std::string>(this->entity->GetPosition(true).y),0,40);
    //this->_scene->context->DrawText("Z:" + boost::lexical_cast<std::string>(this->entity->GetPosition(true).z),0,80);
    this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
    //this->_scene->context->DrawImage(WorldObject::GetHudIcon(),300,300);
}

void MonkeyWrench::SetPosition(Leadwerks::Vec3 position, bool global = false)
{
    this->entity->SetPosition(position,global);
}

void MonkeyWrench::SetPosition(float x, float y, float z, bool global = false)
{
    this->entity->SetPosition(x,y,z,global);
}

Leadwerks::Vec3 MonkeyWrench::GetPosition(bool global)
{
    return Leadwerks::Vec3(this->entity->GetPosition().x,this->entity->GetPosition().y,this->entity->GetPosition().z);
}
