#ifndef PLAYER_H
#define PLAYER_H
#include "Leadwerks.h"
#include "Scene.h"

class Player
{
    public:
        Player(class Scene* scene);
        virtual ~Player();
        void Update();
        void InputUpdate();
        void Crouch();
        void Run();
        void Walk();
    protected:
        Scene* _scene;
    private:
        //Mouse
        Leadwerks::Vec3*    _currentMousePosition;
        Leadwerks::Vec2*    _mouseDiference;
        Leadwerks::Vec2*    _mouseCenter;
        float               _mouseSensibility = 15;
        //Player
        Leadwerks::Vec3*    _playerMovement;
        Leadwerks::Vec3*    _playerPosition;
        Leadwerks::Pivot*   _playerPivot;
        float               _playerHeigth = 1.7;
        float               _playerCurrentHeigth = 0;
        float               _strafeSpeed = 3;
        float               _strafeCurrentSpeed = 3;
        float               _moveSpeed = 3;
        float               _moveCurrentSpeed = 3;
        float               _jumpForce = 6;
        float               _currentJumpForce = 0;
        bool                _crouching = false;
        bool                _running = false;
        //Camera
        Leadwerks::Vec3*    _cameraRotation;
        float               _cameraTopAngle = -45;
        float               _cameraBottomAngle = 80;
};

#endif // PLAYER_H
