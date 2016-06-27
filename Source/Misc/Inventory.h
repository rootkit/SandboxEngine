#ifndef INVENTORY_H
#define INVENTORY_H
#include <Leadwerks.h>
#include "../Scene.h"
#include "WorldObject.h"
#include "InventoryItem.h"

class Inventory
{
    public:
        Inventory(class Scene* scene);
        virtual ~Inventory();
        void DrawContext();
        void Update();
        void InputUpdate();
        void Show();
        void Hide();
        bool IsVisible();
        void AddItem(class WorldObject* item);
    protected:
    private:
    	bool									_visible = false;
    	class Scene* 							_scene;
    	std::vector<class WorldObject*>* 		_items;
        std::vector<class InventoryItem*>*      _visualItems;
    	Leadwerks::Texture*						_background;
        Leadwerks::Vec2*                        _position;
        float                                   _itemMargin = 2;
        int                                     _columns = 6;
        float                                   _gridWidth = 64;
        float                                   _itemsAlignX = 44;
        float                                   _itemsAlignY = 44;

        void _drawItems();
};

#endif // INVENTORY_H
