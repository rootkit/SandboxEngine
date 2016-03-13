#ifndef PLAYER_H
#define PLAYER_H
#include <boost/lexical_cast.hpp>
#include "Leadwerks.h"
#include "Scene.h"
#include "Misc/WorldObject.h"
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
    protected:
        Scene* _scene;
    private:
        //Physics
        Leadwerks::Shape*       _body;
        Leadwerks::Model*       _bodyModel;
        Leadwerks::Material*    _bodyModelMaterial;
        //Punch Physics
        Leadwerks::Shape*       _punchShape;
        Leadwerks::Model*       _punchModel;
        Leadwerks::Material*    _punchModelMaterial;
        float                   _punching = false;
        float                   _freeToPunch = true;
        //Weapons
        Leadwerks::Entity*      _weapon;
        Leadwerks::Entity*      _weaponModel;
        float                   _timer;
        //Crosshair
        Leadwerks::Texture*     _crosshair;
        Leadwerks::PickInfo     _pickinfo;
        Leadwerks::Model*        _pickSphere;
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
        float                   _jumpForce = 7;
        float                   _currentJumpForce = 0;
        bool                    _crouching = false;
        bool                    _running = false;
        //Camera
        Leadwerks::Vec3*        _cameraRotation;
        float                   _cameraTopAngle = -45;
        float                   _cameraBottomAngle = 80;
};

#endif // PLAYER_H
