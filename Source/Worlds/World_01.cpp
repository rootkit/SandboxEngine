#define _GLIBCXX_USE_CXX11_ABI 0
#include "World_01.h"

World_01::World_01(Leadwerks::Window* window,Context* context,World* world,Camera* camera)
    : Scene(window,context,world,camera)
{
    //ctor
    this->LoadMap("Maps/World_01.map");

    //_floorObject = new FloorObject(this);

    //_buildMatrixObject = AddBuildMatrixObject("", new Leadwerks::Vec3(2,2,2),new Leadwerks::Vec3(2,2,2),new Leadwerks::Vec3(3.8399,3.8299,3.8399));
    this->_monkeyWrench = new MonkeyWrench(NULL,this);
    this->_monkeyWrench->SetPosition(9,5,8,true);
}

World_01::~World_01()
{
    //dtor
}

void World_01::Update()
{
    Scene::Update();
    this->_monkeyWrench->Update();
}

void World_01::InputUpdate()
{
    Scene::InputUpdate();
}

void World_01::DrawContext()
{
    Scene::DrawContext();
    this->_monkeyWrench->DrawContext();
}
