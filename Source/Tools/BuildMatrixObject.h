#ifndef BUILDMATRIXOBJECT_H
#define BUILDMATRIXOBJECT_H
#include "Leadwerks.h"

class BuildMatrixObject
{
    public:
        BuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize);
        virtual ~BuildMatrixObject();
        void Update();
        void SetPosition(float x,float y, float z);
    protected:
    private:
        Leadwerks::Vec3* _position;
        std::vector<std::vector<Leadwerks::Entity*>*> _grid;
};

#endif // BUILDMATRIXOBJECT_H
