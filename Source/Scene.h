#ifndef SCENE_H
#define SCENE_H
#include "Leadwerks.h"
#include "Tools/BuildMatrixObject.h"

using namespace Leadwerks;

class Scene
{
    public:
        Leadwerks::Window* window;
        Context* context;
        World* world;
        Camera* camera;
        Scene(Leadwerks::Window* window,Context* context,World* world,Camera* camera);
        void Update();

        BuildMatrixObject* AddBuildMatrixObject(std::string prefabSet, float buildSizeX, float buildSizeY, float buildSizeZ,float blockSizeX, float blockSizeY, float blockSizeZ);

        virtual ~Scene();
    protected:
        void LoadMap(std::string mapFilename);
    private:
        Entity* GetMapEntityByName(std::string entityName);
};

#endif // SCENE_H
