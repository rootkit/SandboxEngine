#ifndef WORLD_01_H
#define WORLD_01_H
#include "Leadwerks.h"
#include "../../Source/Scene.h"
#include "../../Source/Tools/FloorObject.h"
#include "../../Source/Tools/BuildMatrixObject.h"

using namespace Leadwerks;

class World_01 : public Scene
{
    public:
        World_01(Leadwerks::Window* window,Context* context,World* world,Camera* camera);
        virtual ~World_01();
        void Update();
    protected:
    private:
    	FloorObject* _floorObject;
    	BuildMatrixObject* _buildMatrixObject;
};

#endif // WORLD_01_H
