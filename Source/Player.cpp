#define _GLIBCXX_USE_CXX11_ABI 0
#include "Player.h"

Player::Player(class Scene* scene)
{
    this->_scene = scene;

    ///Creating Mouse Vectors
    this->_currentMousePosition = new Leadwerks::Vec3();
    this->_mouseDiference = new Leadwerks::Vec2();
    this->_mouseCenter = new Leadwerks::Vec2(this->_scene->context->GetWidth() / 2, this->_scene->context->GetHeight() / 2);
    this->_scene->window->SetMousePosition(this->_mouseCenter->x,this->_mouseCenter->y);

    ///Creating player pivot
    this->_playerMovement = new Leadwerks::Vec3();
    this->_playerPosition = new Leadwerks::Vec3();
    this->_playerPivot = Leadwerks::Pivot::Create();
    this->_playerPivot->SetPhysicsMode(Leadwerks::Entity::CharacterPhysics);
    this->_playerPivot->SetPosition(0,4,0);
    this->_playerPivot->SetMass(1);

    ///Creating Camera Vectors
    this->_cameraRotation = new Leadwerks::Vec3();
}

Player::~Player()
{
    //dtor
}

void Player::Update()
{
    this->_scene->camera->SetRotation(*this->_cameraRotation);

    if(this->_crouching)
        this->_playerCurrentHeigth = Leadwerks::Math::Curve(this->_playerHeigth - 1,this->_playerCurrentHeigth,5);
    else
        this->_playerCurrentHeigth =  Leadwerks::Math::Curve(this->_playerHeigth,this->_playerCurrentHeigth,5);

    if(this->_running){
        this->_moveCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 3,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 3,this->_strafeCurrentSpeed,5);
    }else{
        this->_moveCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_strafeCurrentSpeed,5);
    }

    this->_scene->camera->SetPosition(this->_playerPosition->x,this->_playerPosition->y + this->_playerCurrentHeigth,this->_playerPosition->z);
    //Leadwerks::Camera::SetRotation()
    //Leadwerks::Vec3* torque = new Leadwerks::Vec3(0,0.1,0);
    //this->_scene->camera->SetRotation(((this->_scene->camera->GetRotation(true) + (*torque) ) * 0.1)* Leadwerks::Time::GetSpeed(),true);
    this->_playerPivot->SetInput(this->_cameraRotation->y,this->_playerMovement->z, this->_playerMovement->x,this->_currentJumpForce, false, 1);
}

void Player::InputUpdate()
{

    this->_currentMousePosition = new Leadwerks::Vec3(this->_scene->window->GetMousePosition().x,this->_scene->window->GetMousePosition().y,this->_scene->window->GetMousePosition().z);
    this->_mouseDiference->x = this->_currentMousePosition->x - this->_mouseCenter->x;
    this->_mouseDiference->y = this->_currentMousePosition->y - this->_mouseCenter->y;

    this->_cameraRotation->x += this->_mouseDiference->y / this->_mouseSensibility;
    this->_cameraRotation->y += this->_mouseDiference->x / this->_mouseSensibility;
    this->_scene->window->SetMousePosition(this->_mouseCenter->x,this->_mouseCenter->y);

    ///Strafe and Move

    this->_playerMovement->x = (this->_scene->window->KeyDown(Leadwerks::Key::D) - this->_scene->window->KeyDown(Leadwerks::Key::A)) * Leadwerks::Time::GetSpeed() * this->_strafeCurrentSpeed;
    this->_playerMovement->z = (this->_scene->window->KeyDown(Leadwerks::Key::W) - this->_scene->window->KeyDown(Leadwerks::Key::S)) * Leadwerks::Time::GetSpeed() * this->_moveCurrentSpeed;

    this->_playerPosition = new Leadwerks::Vec3(this->_playerPivot->GetPosition().x,this->_playerPivot->GetPosition().y,this->_playerPivot->GetPosition().z);

    ///Jump
    this->_currentJumpForce = 0;
    if(this->_scene->window->KeyHit(Leadwerks::Key::Space) && !this->_playerPivot->GetAirborne())
        this->_currentJumpForce = this->_jumpForce;

    ///Crouching
    if(this->_scene->window->KeyHit(Leadwerks::Key::C))
        this->Crouch();

    ///Running
    if(this->_scene->window->KeyDown(Leadwerks::Key::Shift))
        this->Run();
    else
        this->Walk();
}
void Player::Crouch()
{
    this->_crouching = !this->_crouching;
}

void Player::Run()
{
    if(!this->_crouching)
        this->_running = true;
    else
        this->_running = false;
}

void Player::Walk()
{
    this->_running = false;
}


