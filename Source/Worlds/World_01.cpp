#define _GLIBCXX_USE_CXX11_ABI 0
#include "World_01.h"

World_01::World_01(Leadwerks::Window* window,Context* context,World* world,Camera* camera)
    : Scene(window,context,world,camera)
{
    //ctor
    this->LoadMap("Maps/start.map");

    //_floorObject = new FloorObject(this);

    _buildMatrixObject = AddBuildMatrixObject("",3,2,3,1,1,1);
}

World_01::~World_01()
{
    //dtor
}

void World_01::Update()
{
    Scene::Update();
}
