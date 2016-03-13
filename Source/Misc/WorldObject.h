#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "Leadwerks.h"
#include "../Scene.h"

class WorldObject : public Leadwerks::Pivot
{
    public:
        WorldObject(Leadwerks::Entity* parent,class Scene* scene);
        virtual ~WorldObject();
        void Update();
        void DrawContext();
        void SetPosition(Leadwerks::Vec3 position,bool global);
        void SetPosition(float x,float y,float z, bool global);
        Leadwerks::Vec3 GetPosition(bool global);
        string ObjectType = "";
        Leadwerks::Entity* entity;
    protected:
        class Scene* _scene;
        Leadwerks::Vec3* _position;
        void SetScene(class Scene* scene);
    private:
};

#endif // WORLDOBJECT_H
