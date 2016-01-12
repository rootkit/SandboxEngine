#define _GLIBCXX_USE_CXX11_ABI 0
#include "BuildMatrixObject.h"

BuildMatrixObject::BuildMatrixObject(std::string prefabSet, float buildSizeX, float buildSizeY, float buildSizeZ,float blockSizeX , float blockSizeY, float blockSizeZ)
{
    std::vector<Leadwerks::Entity*> row;

    for (int i = 0; i < buildSizeY; ++i)
    {
        row.clear();

        for(int j = 0; j < buildSizeZ; ++j)
        {
            for (int k = 0; k < buildSizeX; ++k)
            {
                Leadwerks::Entity* block = Leadwerks::Model::Box(blockSizeX,blockSizeY,blockSizeZ);
                block->SetPosition((buildSizeX * k) / 3,(buildSizeY * i) / 2,(buildSizeZ * j) / 3);

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
