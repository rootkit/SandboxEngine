#ifndef BUILDMATRIXOBJECT_H
#define BUILDMATRIXOBJECT_H
#include "Leadwerks.h"

class BuildMatrixObject
{
    public:
        BuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize);
        virtual ~BuildMatrixObject();
        void Update();
        void SetPosition(Leadwerks::Vec3* position);
    protected:
    private:
    	bool _attributeChange =	false;
        Leadwerks::Vec3* _position;
    	Leadwerks::Vec3* _buildSize;
    	Leadwerks::Vec3* _blockSize;
        std::vector<std::vector<Leadwerks::Entity*>*> _grid;
        void _ProcessGrid();
        void _CreateGrid();
};

#endif // BUILDMATRIXOBJECT_H
