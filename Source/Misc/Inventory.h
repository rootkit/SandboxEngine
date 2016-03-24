#ifndef INVENTORY_H
#define INVENTORY_H
#include <Leadwerks.h>
#include "WorldObject.h"

class Inventory
{
    public:
        Inventory();
        virtual ~Inventory();
    protected:
    private:
    	std::vector<WorldObject>* _items;
};

#endif // INVENTORY_H
