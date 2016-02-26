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
    this->_playerPivot->SetCollisionType(Leadwerks::COLLISION_CHARACTER);

    this->_playerPivot->SetPosition(this->_scene->PlayerStart->GetPosition(true).x,this->_scene->PlayerStart->GetPosition(true).y,this->_scene->PlayerStart->GetPosition(true).z);

    this->_playerPivot->SetMass(1);


    ///Creating body Physics
    this->_body = Leadwerks::Shape::Box(0,0,0, 0,0,0, 1,3,1);
    this->_bodyModel = Leadwerks::Model::Box(this->_playerPivot);
    this->_bodyModel->SetPosition(0,1,0);
    this->_bodyModel->SetShape(this->_body);
    //this->_bodyModel->SetScale(0.5,1,0.5);
    this->_bodyModel->SetCollisionType(Leadwerks::COLLISION_DEBRIS);
    this->_bodyModelMaterial = Leadwerks::Material::Create();
    this->_bodyModelMaterial->SetBlendMode(Leadwerks::Blend::Invisible);
    this->_bodyModelMaterial->SetShadowMode(0);
    this->_bodyModel->SetMaterial(this->_bodyModelMaterial);

    ///Creating Punch Physics
    this->_punchShape = Leadwerks::Shape::Sphere(0,0,0, 0,0,0, 1,1,1);
    this->_punchModel = Leadwerks::Model::Sphere(16,this->_scene->camera);
    this->_punchModel->SetMass(10);
    this->_punchModel->SetGravityMode(0);
    this->_punchModel->SetPosition(0,1,0,false);
    this->_punchModel->SetShape(this->_punchShape);
    this->_punchModel->SetScale(0.5,0.5,0.5);
    this->_punchModel->SetCollisionType(Leadwerks::COLLISION_DEBRIS);
    this->_punchModelMaterial = Leadwerks::Material::Create();
    this->_punchModelMaterial->SetBlendMode(Leadwerks::Blend::Invisible);
    this->_punchModelMaterial->SetShadowMode(0);
    this->_punchModel->SetMaterial(this->_punchModelMaterial);

    ///Creating Weapons Models
    this->_weapon = Leadwerks::Pivot::Create(this->_scene->camera);
    this->_weapon->SetPosition(0,-0.1,0.0,false);
    this->_weaponModel = Leadwerks::Prefab::Load("Prefabs/Weapons/arms.pfb");
    this->_weaponModel->SetParent(this->_weapon);
    this->_weaponModel->SetPosition(0,0,0,false);
    //this->_weaponModel->SetAnimationFrame(0,1,"fire");

    ///Crossair
    this->_crosshair = Leadwerks::Texture::Load("Materials/Crosshair/Crosshair.tex");

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
        this->_playerCurrentHeigth = Leadwerks::Math::Curve(this->_playerHeigth - 0.6,this->_playerCurrentHeigth,5);
    else
        this->_playerCurrentHeigth =  Leadwerks::Math::Curve(this->_playerHeigth,this->_playerCurrentHeigth,5);

    if(this->_running){
        this->_moveCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 3,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 3,this->_strafeCurrentSpeed,5);
    }else{
        this->_moveCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_strafeCurrentSpeed,5);
    }

    this->_scene->camera->SetPosition(this->_playerPosition->x, Leadwerks::Math::Curve(this->_playerPosition->y + this->_playerCurrentHeigth, this->_scene->camera->GetPosition().y,4),this->_playerPosition->z);
    this->_playerPivot->SetInput(this->_cameraRotation->y,this->_playerMovement->z, this->_playerMovement->x,this->_currentJumpForce,this->_crouching, 1,0.5,true);

    //this->_body->position = Leadwerks::Vec3(this->_playerPosition->x,this->_playerPosition->y,this->_playerPosition->z);

    if(this->_punching)
    {
        //this->_punchModel->SetPosition(0,0,1,false);
        this->_punchModel->SetPosition(0,0,Leadwerks::Math::Curve(2,this->_punchModel->GetPosition().z,2),false);
        if(this->_punchModel->GetPosition().z >= 1.8)
            this->_punching = false;

        //this->_punchModel->tr

    }
    else
    {
        this->_punchModel->SetPosition( 0,0,Leadwerks::Math::Curve(0,this->_punchModel->GetPosition().z,10), false);
        if(this->_punchModel->GetPosition().z <= 1)
            this->_freeToPunch = true;
        //this->_punchModel->SetPosition(0,0,0,false);
    }

    ///Weapon Ajusts
    //this->_weapon->SetPosition(0,this->_playerCurrentHeigth,0,false);
    this->_timer = Leadwerks::Time::GetCurrent() / 40;
    this->_weaponModel->SetAnimationFrame(this->_timer, 10, 0, true);

    //this->_punchModel->SetRotation(0,0,0,false);
    //this->_punchModel->SetRotation(this->_scene->camera->GetRotation().x,this->_scene->camera->GetRotation().y,this->_scene->camera->GetRotation().z,false);
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

    ///Punch
    if(this->_scene->window->MouseHit(1))
        this->Punch();
}


void Player::DrawContext()
{
    this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
    this->_scene->context->DrawImage(this->_crosshair,
                                    (this->_scene->window->GetWidth() / 2) - (this->_crosshair->GetWidth() / 2),
                                    (this->_scene->window->GetHeight() / 2) - (this->_crosshair->GetHeight() / 2));
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

void Player::Punch()
{
    if(this->_freeToPunch)
        if(!this->_punching)
        {
            this->_punching = true;
            this->_freeToPunch = false;
        }
}
