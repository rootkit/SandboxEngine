#ifndef MONKEYWRENCH_H
#define MONKEYWRENCH_H
#include "Leadwerks.h"
#include "../../Scene.h"
#include "../../Misc/WorldObject.h"

class MonkeyWrench : public WorldObject
{
    public:
        MonkeyWrench(Leadwerks::Entity* parent,class Scene* scene);
        virtual ~MonkeyWrench();
        void Update();
        void DrawContext();
        void SetPosition(Leadwerks::Vec3 position,bool global);
        void SetPosition(float x,float y,float z, bool global);
        Leadwerks::Vec3 GetPosition(bool global);
    protected:
    private:
};

#endif // MONKEYWRENCH_H
