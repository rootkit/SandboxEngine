#pragma once

#include "Leadwerks.h"
#include "AppConfiguration.h"
#include "Scene.h"
#include "Worlds/World_01.h"

#undef GetFileType

using namespace Leadwerks;

class App
{
public:
	Leadwerks::Window* window;
	Context* context;
	World* world;
	Camera* camera;
	AppConfiguration* appjson;

    Leadwerks::Texture* LoadingScreen;

    Leadwerks::Font* DefaultFont;

	Scene* CurrentScene;

	App();
	virtual ~App();

    void ShowLoading();
    void CloseLoading();
    bool Start();
    bool Loop();
};
