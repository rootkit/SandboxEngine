#define _GLIBCXX_USE_CXX11_ABI 0
#include "Scene.h"

using namespace Leadwerks;

vector<Entity*> mapEntities;

void StoreWorldObjects(Entity* entity, Object* extra)
{
    System::Print("Loaded an entity and stored it: " + entity->GetKeyValue("name") + "\r\n");
    mapEntities.push_back(entity);
}

/** @brief GetMapEntityByName
  *
  * @todo: document this function
  */
Entity* Scene::GetMapEntityByName(std::string entityName)
{
	vector<Entity*>::iterator iter = mapEntities.begin();
    int id = 0;
    for (iter; iter != mapEntities.end(); iter++)
    {
        Entity* entity = *iter;
        //if (entity->script != NULL) {
        System::Print(entity->GetKeyValue("name"));
        //}
        if(entity->GetKeyValue("name") == entityName){
            return entity;
        }
    }
}

Scene::Scene(Leadwerks::Window* window,Context* context,World* world,Camera* camera)
{
    this->window = window;
	this->context = context;
	this->world = world;
	this->camera = camera;

    std::string postefect_bloom = System::GetProperty("shaders","Shaders/PostEffects/bloom.lua");

	//this->camera->AddPostEffect(postefect_bloom);
}

Scene::~Scene()
{
    //dtor
}

void Scene::LoadMap(std::string mapFilename)
{
    std::string mapname = System::GetProperty("map", mapFilename);
	Map::Load(mapname,StoreWorldObjects);
}

void Scene::Update()
{

}

BuildMatrixObject* Scene::AddBuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize)
{
    return new BuildMatrixObject(prefabSet,buildPosition,buildSize,blockSize);
}


