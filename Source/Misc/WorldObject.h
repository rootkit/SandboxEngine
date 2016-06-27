#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "Leadwerks.h"
#include "../Scene.h"

class WorldObject : public Leadwerks::Pivot
{
    public:
        WorldObject(Leadwerks::Entity* parent,class Scene* scene);
        virtual ~WorldObject();
        void Update();
        void DrawContext();
        void SetPosition(Leadwerks::Vec3 position,bool global);
        void SetPosition(float x,float y,float z, bool global);

        void SetName(string value);
        void SetGUID(string value);
        void SetDescription(string value);
        void SetInteractive(bool value);
        void SetEquippably(bool value);
        void SetType(string value);
        void SetSubType(string value);
        void SetHudIcon(string filename128, string filename64, string filename32);
        void Show();
        void Hide();

        string GetDescription();
        string GetName();
        string GetGUID();
        bool GetInteractive();
        bool GetEquippably();
        string GetType();
        string GetSubType();
        Leadwerks::Texture* GetHudIcon128();
        Leadwerks::Texture* GetHudIcon64();
        Leadwerks::Texture* GetHudIcon32();

        Leadwerks::Vec3 GetPosition(bool global);              
        Leadwerks::Entity*      entity;        
    protected:
        class Scene*            _scene;
        Leadwerks::Vec3*        _position;
        void SetScene(class Scene* scene);
    private:
        bool                    _visible = false;
        bool                    _interactive = false;
        bool                    _equippably = false;
        string                  _type = "";  
        string                  _subType = "";
        string                  _name = "";
        string                  _guid = "";
        string                  _description = "";
        Leadwerks::Texture*     _hudIcon128;
        Leadwerks::Texture*     _hudIcon64;
        Leadwerks::Texture*     _hudIcon32;
};

#endif // WORLDOBJECT_H
