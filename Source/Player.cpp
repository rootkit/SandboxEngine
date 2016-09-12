#define _GLIBCXX_USE_CXX11_ABI 0
#include "Player.h"

Player::Player(class Scene* scene)
{
    this->_scene = scene;
    ///Creating Inventory Object
    this->_inventory = new Inventory(scene);
    this->_pickSound = Leadwerks::Sound::Load("Sound/Interaction/switch12.wav");
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
    this->_body = Leadwerks::Shape::Box(0,0,0, 0,0,0, 1,1,1);
    this->_bodyModel = Leadwerks::Model::Box(this->_playerPivot);
    this->_bodyModel->SetPosition(0,1,0);
    this->_bodyModel->SetShape(this->_body);
    this->_bodyModel->SetScale(0.05,1,0.05);
    this->_bodyModel->SetCollisionType(Leadwerks::COLLISION_DEBRIS);
    this->_bodyModelMaterial = Leadwerks::Material::Create();
    this->_bodyModelMaterial->SetBlendMode(Leadwerks::Blend::Invisible);
    this->_bodyModelMaterial->SetShadowMode(0);
    this->_bodyModel->SetMaterial(this->_bodyModelMaterial);

    ///Creating Punch Physics
    this->_punchModelMaterial = Leadwerks::Material::Create();
    this->_punchModelMaterial->SetBlendMode(Leadwerks::Blend::Invisible);
    this->_punchModelMaterial->SetShadowMode(0);

    this->_punchShapeRight = Leadwerks::Shape::Sphere(0,0,0, 0,0,0, 1,1,1);
    this->_punchColliderModelRigth = Leadwerks::Model::Sphere(16);
    this->_punchColliderModelRigth->SetMass(10);
    this->_punchColliderModelRigth->SetGravityMode(0);
    this->_punchColliderModelRigth->SetPosition(0,1,0,false);
    this->_punchColliderModelRigth->SetShape(this->_punchShapeRight);
    this->_punchColliderModelRigth->SetScale(0.5,0.5,0.5);
    this->_punchColliderModelRigth->SetMaterial(this->_punchModelMaterial);
    this->_punchColliderModelRigth->SetCollisionType(Leadwerks::COLLISION_DEBRIS);

    this->_punchShapeLeft = Leadwerks::Shape::Sphere(0,0,0, 0,0,0, 1,1,1);
    this->_punchColliderModelLeft = Leadwerks::Model::Sphere(16);
    this->_punchColliderModelLeft->SetMass(10);
    this->_punchColliderModelLeft->SetGravityMode(0);
    this->_punchColliderModelLeft->SetPosition(0,1,0,false);
    this->_punchColliderModelLeft->SetShape(this->_punchShapeLeft);
    this->_punchColliderModelLeft->SetScale(0.5,0.5,0.5);
    this->_punchColliderModelLeft->SetMaterial(this->_punchModelMaterial);
    this->_punchColliderModelLeft->SetCollisionType(Leadwerks::COLLISION_DEBRIS);

    ///Creating Weapons Models
    this->_weapon = Leadwerks::Pivot::Create(this->_scene->camera);
    this->_weapon->SetPosition(0,0,0,false);
    this->_weaponModel = Leadwerks::Prefab::Load("Prefabs/Weapons/arms.pfb");
    this->_weaponModel->SetParent(this->_weapon);
    this->_weaponModel->SetPosition(0,-0.2,-0.2,false);
    this->_currentAnimation = "Idle";
    //this->_weaponModel->SetAnimationFrame(0,1,"fire");

    ///Crossair
    this->_crosshair = Leadwerks::Texture::Load("Materials/Crosshair/Crosshair.tex");

    ///Creating Camera Vectors
    this->_cameraRotation = new Leadwerks::Vec3();

    ///Pick Info
    std::string pickinfoFontPath = System::GetProperty("font","Fonts/arial.ttf");
    this->_pickinfoFont = Leadwerks::Font::Load(pickinfoFontPath,14,Leadwerks::Font::Smooth);
    //this->_pickinfo = new Leadwerks::PickInfo();
    //Create a sphere to indicate where the pick hits
    this->_pickSphere = Leadwerks::Model::Sphere();
    this->_pickSphere->SetCollisionType(Leadwerks::COLLISION_NONE);
    this->_pickSphere->SetColor(1.0,0.0,0.0);
    this->_pickSphere->SetPickMode(0);
    this->_pickSphere->Hide();
}

Player::~Player()
{
    delete _inventory;
    delete _pickSound;
    delete _body;
    delete _bodyModel;
    delete _bodyModelMaterial;
    delete _punchModelMaterial;
    delete _punchShapeRight;
    delete _punchColliderModelRigth;
    delete _punchShapeLeft;
    delete _punchColliderModelLeft;
    delete _weapon;
    delete _weaponModel;
    delete _crosshair;
    delete _pickSphere;
    delete _interactingObject;
    delete _currentMousePosition;
    delete _mouseDiference;
    delete _mouseCenter;
    delete _playerMovement;
    delete _playerPosition;
    delete _playerPivot;
    delete _cameraRotation;
}

void Player::Update()
{
    this->_scene->camera->SetRotation(*this->_cameraRotation);

    if(this->_crouching)
        this->_playerCurrentHeigth = Leadwerks::Math::Curve(this->_playerHeigth - 0.6,this->_playerCurrentHeigth,5);
    else
        this->_playerCurrentHeigth =  Leadwerks::Math::Curve(this->_playerHeigth,this->_playerCurrentHeigth,5);

    if(this->_running){
        this->_moveCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 1.3,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed = Leadwerks::Math::Curve(this->_moveSpeed + 1.3,this->_strafeCurrentSpeed,5);
    }else{
        this->_moveCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_moveCurrentSpeed,5);
        this->_strafeCurrentSpeed =  Leadwerks::Math::Curve(this->_strafeSpeed,this->_strafeCurrentSpeed,5);
    }

    this->_scene->camera->SetPosition(this->_playerPosition->x, Leadwerks::Math::Curve(this->_playerPosition->y + this->_playerCurrentHeigth, this->_scene->camera->GetPosition().y,2),this->_playerPosition->z);
    this->_playerPivot->SetInput(this->_cameraRotation->y,this->_playerMovement->z, this->_playerMovement->x,this->_currentJumpForce,this->_crouching, 1,0.5,true);

    //this->_body->position = Leadwerks::Vec3(this->_playerPosition->x,this->_playerPosition->y,this->_playerPosition->z);

    if(this->_punching)
    {
        if(this->_currentAnimationFrame == 25)
            this->_punching = false;
    }
    else
    {
        this->_freeToPunch = true;
    }

    ///Weapon Ajusts
    //this->_weapon->SetPosition(0,this->_playerCurrentHeigth,0,false);
    this->_timer = Leadwerks::Time::GetCurrent() / 40;
    this->_loopAnimation();

    ///Punch Collider
    Leadwerks::Entity* rNode1 = this->_weaponModel->GetChild(0);
    Leadwerks::Entity* rNode2 = rNode1->GetChild(2);
    Leadwerks::Entity* rNode3 = rNode2->GetChild(0);
    Leadwerks::Entity* rPalm = rNode3;

    this->_punchColliderModelRigth->SetPosition(rPalm->GetPosition(true),true);

    Leadwerks::Entity* lNode1 = this->_weaponModel->GetChild(0);
    Leadwerks::Entity* lNode2 = lNode1->GetChild(3);
    Leadwerks::Entity* lNode3 = lNode2->GetChild(0);
    Leadwerks::Entity* lPalm = lNode3;

    this->_punchColliderModelLeft->SetPosition(lPalm->GetPosition(true),true);

    ///Pick Info
    Leadwerks::Vec3 p0 = this->_scene->camera->GetPosition(true);
	Leadwerks::Vec3 p1 = Leadwerks::Transform::Point(0,0,1.5,this->_scene->camera,NULL);

	if(this->_scene->world->Pick(p0,p1, this->_pickinfo,0, true)){
        this->_pickSphere->SetPosition(this->_pickinfo.position);
	}
}

void Player::InputUpdate()
{
    this->_inventory->InputUpdate();

    if(this->_inventory->IsVisible())
        return;

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

    ///Interact
    if(this->_scene->window->KeyHit(Leadwerks::Key::E))
        this->Interact();
}


void Player::DrawContext()
{
    this->_screenHeigthCenter = (this->_scene->window->GetHeight() / 2);
    this->_screenWidthCenter = (this->_scene->window->GetWidth() / 2);

    this->_scene->context->SetBlendMode(Leadwerks::Blend::Alpha);
    this->_scene->context->DrawImage(this->_crosshair,
                                    this->_screenWidthCenter - (this->_crosshair->GetWidth() / 2),
                                    this->_screenHeigthCenter - (this->_crosshair->GetHeight() / 2));

    if(this->_pickinfo.entity != NULL){

       try{
            WorldObject* _worldObject = dynamic_cast<WorldObject*>(this->_pickinfo.entity->GetChild(0));

            if(_worldObject != NULL){
                this->_scene->context->SetFont(this->_pickinfoFont);
                this->_scene->context->DrawText("(E) " + _worldObject->GetName(),this->_screenWidthCenter + 40,this->_screenHeigthCenter - 40);
                this->_interactingObject = _worldObject;
            }
            else{
                //this->_scene->context->DrawText("PICK INFO: NONE",0,200);
                this->_interactingObject = NULL;
            }

        }catch(int e){
            //this->_scene->context->DrawText("PICK INFO: NONE",0,200);
            this->_interactingObject = NULL;
        }
    }

    this->_inventory->DrawContext();
}

void Player::_playAnimation(string animationName)
{
    if(this->_currentAnimation != animationName){
        this->_currentAnimation = animationName;
        this->_currentAnimationFrame = 0;
        this->_currentAnimationLength = this->_weaponModel->GetAnimationLength(animationName);
    }
}

void Player::_loopAnimation()
{
    if(Leadwerks::Time::GetCurrent() >= this->_currentAnimationLastFrameTime){

        this->_currentAnimationLastFrameTime = Leadwerks::Time::GetCurrent() + 15;

        if(this->_currentAnimationFrame <= (this->_currentAnimationLength - 1)){
            this->_currentAnimationFrame++;
            this->_weaponModel->SetAnimationFrame(this->_currentAnimationFrame, 10, this->_currentAnimation, true);
        }else{
            this->_playAnimation("Idle");
        }
    }
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

            srand (time(NULL));
            int animVar = rand() % 2;
            if(animVar == 1){
                this->_playAnimation("Punch");
            }else{
                this->_playAnimation("PunchSecondary");
            }
        }
}

void Player::Interact()
{
    if(this->_interactingObject != NULL){
        this->_inventory->AddItem(this->_interactingObject);
        this->_pickSound->Play();
        this->_interactingObject->Hide();
    }
}
