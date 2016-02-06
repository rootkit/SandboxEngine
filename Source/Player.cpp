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

    this->_playerPivot->SetPosition(this->_scene->PlayerStart->GetPosition(true).x,this->_scene->PlayerStart->GetPosition(true).y,this->_scene->PlayerStart->GetPosition(true).z);

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

    this->_scene->camera->SetPosition(this->_playerPosition->x, Leadwerks::Math::Curve(this->_playerPosition->y + this->_playerCurrentHeigth, this->_scene->camera->GetPosition().y,8),this->_playerPosition->z);
    this->_playerPivot->SetInput(this->_cameraRotation->y,this->_playerMovement->z, this->_playerMovement->x,this->_currentJumpForce,this->_crouching, 1,0.5,true);
}

void Player::InputUpdate()
{

    this->_currentMousePosition = new Leadwerks::Vec3(this->_scene->window->GetMousePosition().x,this->_scene->window->GetMousePosition().y,this->_scene->window->GetMousePosition().z);
    this->_mouseDiference->x = this->_currentMousePosition->x - this->_mouseCenter->x;
    this->_mouseDiference->y = this->_currentMousePosition->y - this->_mouseCenter->y;

    float tempCameraRotationX = this->_cameraRotation->x + (this->_mouseDiference->y / this->_mouseSensibility);

    if(tempCameraRotationX > this->_cameraTopAngle && tempCameraRotationX < this->_cameraBottomAngle)
        this->_cameraRotation->x = tempCameraRotationX;

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


