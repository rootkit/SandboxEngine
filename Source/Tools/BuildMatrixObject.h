#ifndef BUILDMATRIXOBJECT_H
#define BUILDMATRIXOBJECT_H
#include "Leadwerks.h"

class BuildMatrixObject
{
    public:
        BuildMatrixObject(std::string prefabSet, float buildSizeX, float buildSizeY, float buildSizeZ,float blockSizeX, float blockSizeY, float blockSizeZ);
        virtual ~BuildMatrixObject();
        void Update();
    protected:
    private:
        std::vector<std::vector<Leadwerks::Entity*>*> _grid;
};

#endif // BUILDMATRIXOBJECT_H
