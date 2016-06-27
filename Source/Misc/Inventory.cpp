#define _GLIBCXX_USE_CXX11_ABI 0
#include "Inventory.h"

Inventory::Inventory(class Scene* scene)
{
	this->_scene = scene;
	this->_background = Leadwerks::Texture::Load("Hud/Inventory/background.tex");
    this->_items = new std::vector<WorldObject*>();
    this->_visualItems = new std::vector<InventoryItem*>();
    this->_position = new Leadwerks::Vec2(0,0);
}

Inventory::~Inventory()
{
    //dtor
}

void Inventory::Show()
{
    this->_visible = true;
    this->_scene->window->ShowMouse();
    float screenCenterWidth = (this->_scene->window->GetWidth() / 2) - (this->_background->GetWidth() / 2);
    float screenCenterHeight = (this->_scene->window->GetHeight() / 2) - (this->_background->GetHeight() / 2);
    this->_position->x = screenCenterWidth;
    this->_position->y = screenCenterHeight;
    //Position of items
}
void Inventory::Hide()
{
    this->_visible = false;
    this->_scene->window->HideMouse();
}

bool Inventory::IsVisible()
{
    return this->_visible;
}

void Inventory::AddItem(WorldObject* item)
{
    this->_items->push_back(item);
    class InventoryItem* visualItem = new InventoryItem(this->_scene);
    visualItem->SetWorldObject(item);
    visualItem->SetWidth(64);
    this->_visualItems->push_back(visualItem);
}

void Inventory::_drawItems()
{
    int currentCol = 1;
    int currentRow = 1;
    float gridSize = this->_gridWidth + this->_itemMargin;            
    float currentX = 0;
    float currentY = this->_position->y + this->_itemsAlignY;
    vector<InventoryItem*>::iterator iter = this->_visualItems->begin();
    for (iter; iter != this->_visualItems->end(); iter++)
    {
        class InventoryItem* item = *iter;

        if(currentCol > this->_columns){
            currentCol = 1;
            currentRow++;
            currentY = (this->_position->y + this->_itemsAlignY) + ((currentRow - 1)* gridSize);            
        }

        currentX = (this->_position->x + this->_itemsAlignX) + ((currentCol - 1) * gridSize);

        item->SetPosition(currentX,currentY);
        item->DrawContext();

        currentCol++;
    }

    //delete iter;
}

void Inventory::DrawContext()
{
    if(!this->_visible)
        return;

  	this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
	//this->_scene->context->SetColor(0.2,0.2,0.2);
    this->_scene->context->DrawImage(this->_background,this->_position->x,this->_position->y);
    //this->_scene->context->SetColor(0,1,0);
    //this->_scene->context->DrawRect(0,0,100,100);
    this->_scene->context->SetColor(1,1,1);
    //Leadwerks::Font* this->_scene->context->GetFont();
	this->_scene->context->DrawText("Inventory",30,30);
    //Darwing Items
    this->_drawItems();
}

void Inventory::Update()
{

}

void Inventory::InputUpdate()
{
    if(this->_scene->window->KeyHit(Leadwerks::Key::I))
    {
    	if(!this->_visible)
    		this->Show();
    	else
    		this->Hide();
    }
}
