#define _GLIBCXX_USE_CXX11_ABI 0
#include "App.h"

using namespace Leadwerks;

App::App() : window(NULL), context(NULL), world(NULL), camera(NULL), appjson(NULL) {}

App::~App() { delete world; delete window; }

void App::ShowLoading()
{
    this->LoadingScreen = Leadwerks::Texture::Load("Images/Loading.tex");
    this->context->DrawImage(LoadingScreen,0,0);

    this->context->SetBlendMode(Blend::Alpha);
    this->context->SetFont(this->DefaultFont);
    this->context->SetColor(255,255,255);
    std::string text = "Loading";
    this->context->DrawText(text,(this->window->GetWidth() / 2) - (this->DefaultFont->GetTextWidth(text) / 2),(this->window->GetHeight() / 2) - (this->DefaultFont->GetHeight() / 2));

    this->context->Sync(false);
}

void App::CloseLoading()
{

}

bool App::Start()
{
    Leadwerks:Steamworks();


    std::string title = "RedRequest";

    this->appjson = new AppConfiguration();

	this->window = Leadwerks::Window::Create(title,0,0,1920,1080,Leadwerks::Window::FullScreen);

	//Create a context
	this->context = Context::Create(window);

	//Create a world
	this->world = World::Create();

	//Hide the mouse cursor
	this->window->HideMouse();

    std::string fontpath = System::GetProperty("font","Fonts/arial.ttf");
	this->DefaultFont = Leadwerks::Font::Load(fontpath,36,Leadwerks::Font::Smooth);

    /*list<Camera*>::iterator iter = this->world->cameras.begin();
    for (iter; iter != this->world->cameras.end(); iter++)
    {
        Camera* entity = *iter;
        //if (entity->script != NULL) {
        System::Print("Camera: " + entity->GetKeyValue("name"));
        //}
        if(entity != NULL){
            this->camera = entity;
            break;
        }
    }*/

    this->ShowLoading();

    //Instanciate World Controller
    this->CurrentScene = new World_01(this->window,this->context,this->world,this->camera);

	return true;
}

bool App::Loop()
{
	//Close the window to end the program
	if (this->window->Closed()) return false;

	//Press escape to end freelook mode
	if (this->window->KeyHit(Key::Escape))
	{
		this->window->ShowMouse();
		return false;
	}

	Leadwerks::Time::Update();

    this->CurrentScene->InputUpdate();

	this->CurrentScene->Update();

	this->world->Update();
	this->world->Render();

    this->context->Sync(false);

	return true;
}
