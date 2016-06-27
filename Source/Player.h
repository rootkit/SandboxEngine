#ifndef PLAYER_H
#define PLAYER_H
#include <boost/lexical_cast.hpp>
#include "Leadwerks.h"
#include "Scene.h"
#include "Misc/WorldObject.h"
#include "Misc/Inventory.h"
class Player
{
    public:
        Player(class Scene* scene);
        virtual ~Player();
        void Update();
        void InputUpdate();
        void DrawContext();
        void Crouch();
        void Run();
        void Walk();
        void Punch();
        void Interact();
    protected:
        Scene* _scene;
    private:
        //Inventory
        class Inventory*        _inventory;
        Leadwerks::Sound*       _pickSound;
        //Physics
        Leadwerks::Shape*       _body;
        Leadwerks::Model*       _bodyModel;
        Leadwerks::Material*    _bodyModelMaterial;
        //Punch Physics
        Leadwerks::Material*    _punchModelMaterial;
        Leadwerks::Shape*       _punchShapeRight;
        Leadwerks::Model*       _punchColliderModelRigth;
        Leadwerks::Shape*       _punchShapeLeft;
        Leadwerks::Model*       _punchColliderModelLeft;
        float                   _punching = false;
        float                   _freeToPunch = true;
        //Weapons
        Leadwerks::Entity*      _weapon;
        Leadwerks::Entity*      _weaponModel;
        float                   _timer;
        string                  _currentAnimation;
        int                     _currentAnimationFrame = 0;
        int                     _currentAnimationLength = 0;
        int                     _currentAnimationTime = 0;
        int                     _currentAnimationLastFrameTime = 0;
        //Crosshair
        Leadwerks::Texture*     _crosshair;
        Leadwerks::PickInfo     _pickinfo;
        Leadwerks::Model*       _pickSphere;
        WorldObject*            _interactingObject;
        //Mouse
        Leadwerks::Vec3*        _currentMousePosition;
        Leadwerks::Vec2*        _mouseDiference;
        Leadwerks::Vec2*        _mouseCenter;
        float                   _mouseSensibility = 15;
        //Player
        Leadwerks::Vec3*        _playerMovement;
        Leadwerks::Vec3*        _playerPosition;
        Leadwerks::Pivot*       _playerPivot;
        float                   _playerHeigth = 1.7;
        float                   _playerCurrentHeigth = 0;
        float                   _strafeSpeed = 2;
        float                   _strafeCurrentSpeed = 2;
        float                   _moveSpeed = 2;
        float                   _moveCurrentSpeed = 2;
        float                   _jumpForce = 10;
        float                   _currentJumpForce = 0;
        bool                    _crouching = false;
        bool                    _running = false;
        //Camera
        Leadwerks::Vec3*        _cameraRotation;
        float                   _cameraTopAngle = -45;
        float                   _cameraBottomAngle = 80;
        //Animation
        void _playAnimation(string animationName);
        void _loopAnimation();
};

#endif // PLAYER_H
