#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H
#include <Leadwerks.h>
#include "../Scene.h"
#include "WorldObject.h"

class InventoryItem
{
    public:
        InventoryItem(class Scene* scene);
        virtual ~InventoryItem();
        void DrawContext();
        void Update();
        void InputUpdate();
        void SetPosition(Leadwerks::Vec2* position);
        void SetPosition(float x, float y);
        void SetWorldObject(class WorldObject* object);
        void SetWidth(float value);

        Leadwerks::Vec2* GetPosition();

    protected:
    private:
    	bool									_visible = false;
    	class Scene* 							_scene;
        Leadwerks::Vec2*                        _position;
        class WorldObject*                      _worldObject;
        float                                   _width = 64;
};

#endif // INVENTORYITEM_H
