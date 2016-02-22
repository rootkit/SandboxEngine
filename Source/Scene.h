#ifndef SCENE_H
#define SCENE_H
#include "Leadwerks.h"
#include "Tools/BuildMatrixObject.h"
#include "./Player.h"

using namespace Leadwerks;

class Scene
{
    public:
        Leadwerks::Window* window;
        Context* context;
        World* world;
        Camera* camera;

        std::vector<class Player*> LocalPlayers;
        Leadwerks::Entity* PlayerStart;

        Scene(Leadwerks::Window* window,Context* context,World* world,Camera* camera);
        void Update();
        void InputUpdate();
        void DrawContext();

        BuildMatrixObject* AddBuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize);

        virtual ~Scene();
    protected:
        void LoadMap(std::string mapFilename);
    private:
        Entity* GetMapEntityByName(std::string entityName);
        void LocalPlayersUpdate();
        void LocalPlayersInputUpdate();
        void LocalPlayersDrawContext();
};

#endif // SCENE_H
