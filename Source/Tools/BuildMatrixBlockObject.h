#ifndef BUILDMATRIXBLOCKOBJECT_H
#define BUILDMATRIXBLOCKOBJECT_H
#include "Leadwerks.h"

class BuildMatrixBlockObject
{
    public:
        BuildMatrixBlockObject(std::string prefabPath, Leadwerks::Vec3* position, Leadwerks::Vec3* blockSize);
        virtual ~BuildMatrixBlockObject();
    protected:
    private:
        Leadwerks::Entity* _entity;
};

#endif // BUILDMATRIXBLOCKOBJECT_H
