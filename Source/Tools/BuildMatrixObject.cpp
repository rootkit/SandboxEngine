#define _GLIBCXX_USE_CXX11_ABI 0
#include "BuildMatrixObject.h"

BuildMatrixObject::BuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize)
{
    _position = new Leadwerks::Vec3();

    std::vector<Leadwerks::Entity*> row;

    for (int i = 0; i < buildSize->y; ++i)
    {
        row.clear();

        for(int j = 0; j < buildSize->z; ++j)
        {
            for (int k = 0; k < buildSize->x; ++k)
            {
                Leadwerks::Entity* block = Leadwerks::Model::Box(blockSize->x,blockSize->y,blockSize->z);
                block->SetPosition((blockSize->x * k),(blockSize->y * i),(blockSize->z * j));

                row.push_back(block);
            }
        }

        _grid.push_back(&row);
    }

}

BuildMatrixObject::~BuildMatrixObject()
{
    //dtor
}

void BuildMatrixObject::Update()
{

}

void BuildMatrixObject::SetPosition(float x,float y, float z)
{

}
