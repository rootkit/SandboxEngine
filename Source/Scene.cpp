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
        Leadwerks::Entity* entity = *iter;
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


}

Scene::~Scene()
{
    //dtor
}

void Scene::LoadMap(std::string mapFilename)
{
    std::string mapname = System::GetProperty("map", mapFilename);
	Map::Load(mapname,StoreWorldObjects);

	//Creating Game Instances
	///DEFAULT CAMERA
	this->camera = Leadwerks::Camera::Create();
	///_PLAYER_START
	this->PlayerStart = this->GetMapEntityByName("_PLAYER_START");
	if(PlayerStart != NULL){
        Player* localPlayer = new Player(this);
        this->LocalPlayers.push_back(localPlayer);
	}

    ///SET CAMERA DEFAULT'S
    this->camera->SetPosition(PlayerStart->GetPosition(true).x,PlayerStart->GetPosition(true).y + 3,PlayerStart->GetPosition(true).z,true);
    std::string postefect_bloom = System::GetProperty("shaders","Shaders/PostEffects/bloom.lua");
	this->camera->AddPostEffect(postefect_bloom);

}

void Scene::Update()
{
    this->LocalPlayersUpdate();
}

void Scene::InputUpdate()
{
    this->LocalPlayersInputUpdate();
}

BuildMatrixObject* Scene::AddBuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize)
{
    return new BuildMatrixObject(prefabSet,buildPosition,buildSize,blockSize);
}

void Scene::LocalPlayersUpdate()
{
    vector<class Player*>::iterator iter = this->LocalPlayers.begin();
    int id = 0;
    for (iter; iter != this->LocalPlayers.end(); iter++)
    {
        class Player* entity = *iter;

        entity->Update();
    }
}

void Scene::LocalPlayersInputUpdate()
{
    vector<class Player*>::iterator iter = this->LocalPlayers.begin();
    int id = 0;
    for (iter; iter != this->LocalPlayers.end(); iter++)
    {
        class Player* entity = *iter;

        entity->InputUpdate();
    }
}


