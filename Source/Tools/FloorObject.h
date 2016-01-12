#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H
#include "Leadwerks.h"
#include "../Scene.h"

class FloorObject
{
    public:
        FloorObject(Scene* scene);
        virtual ~FloorObject();
        void Update();
    protected:
    private:
    	Scene* _scene;
    	Leadwerks::Entity* _prefab;
};

#endif // FLOOROBJECT_H
