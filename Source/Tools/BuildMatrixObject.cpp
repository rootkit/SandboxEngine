#define _GLIBCXX_USE_CXX11_ABI 0
#include "BuildMatrixObject.h"

BuildMatrixObject::BuildMatrixObject(std::string prefabSet, Leadwerks::Vec3* buildPosition,Leadwerks::Vec3* buildSize, Leadwerks::Vec3* blockSize)
{
    this->_position   = buildPosition;
    this->_buildSize  = buildSize;
    this->_blockSize  = blockSize;

    this->_CreateGrid();
    this->_ProcessGrid();
}

BuildMatrixObject::~BuildMatrixObject()
{
    //dtor
}

void BuildMatrixObject::Update()
{
    if(_attributeChange)
        return;

    this->_ProcessGrid();
}

void BuildMatrixObject::SetPosition(Leadwerks::Vec3* position)
{
    this->_attributeChange = true;

    this->_position = position;
}

void BuildMatrixObject::_ProcessGrid()
{
    std::vector<std::vector<BuildMatrixBlockObject*>*>::iterator i = _grid.begin();

    for (i; i != _grid.end(); i++)
    {
        std::vector<BuildMatrixBlockObject*>* row = *i;
        std::vector<BuildMatrixBlockObject*>::iterator j = row->begin();

        for (j; j != row->end(); j++)
        {
            BuildMatrixBlockObject* block = *j;

            //block->GetPosition(true)

            //block->SetPosition((this->_blockSize->x * k) + this->_position->x,(this->_blockSize->y * i)  + this->_position->y,(this->_blockSize->z * j)  + this->_position->z,true);
        }
    }
}

void BuildMatrixObject::_CreateGrid()
{
    std::vector<BuildMatrixBlockObject*> row;

    for (int i = 0; i < this->_buildSize->y; ++i)
    {
        row.clear();

        for(int j = 0; j < this->_buildSize->z; ++j)
        {
            for (int k = 0; k < this->_buildSize->x; ++k)
            {
                Leadwerks::Vec3* position = new Leadwerks::Vec3((this->_blockSize->x * k) + this->_position->x,(this->_blockSize->y * i)  + this->_position->y,(this->_blockSize->z * j)  + this->_position->z);
                BuildMatrixBlockObject* block = new BuildMatrixBlockObject("",position,this->_blockSize);

                row.push_back(block);
            }
        }

        this->_grid.push_back(&row);
    }
}
