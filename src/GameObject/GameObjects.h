#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameWorld;

class GameObject : public ObjectBase 
{
    public:
        GameObject(int imageID, 
            int x, int y, int direction, 
            int layer, double size, bool is_valid,
            GameWorld *world);
        void Set_valid(bool is_valid);
        bool Get_valid() const;
        GameWorld *GetWorld() const;
        virtual void Update();
        virtual std::string GetType() const = 0;
        virtual int GetPower() const = 0;
        virtual bool IsEnemy() const = 0;
        virtual void SetHP(int HP) = 0;
        virtual int GetHP() const = 0;
    private:
        bool m_is_valid;
        GameWorld *m_world;
};

class Explosion : public GameObject {
    public:
        Explosion(
            int x, int y, GameWorld *world
        );
        std::string GetType() const;
        int GetPower() const;
        void SetHP(int HP);
        int GetHP() const;
        void Update();
        bool IsEnemy() const;
    private:
        int m_tick_tock;
};  

class Star : public GameObject
{
    private:
        /* data */
    public:
        Star ( 
            int x, int y, int direction, 
            int layer, double size, 
            bool is_valid, GameWorld *world);
        std::string GetType() const;
        void Update();
        int GetPower() const;
        bool IsEnemy() const;
        void SetHP(int HP);
        int GetHP() const;
};

class BlueBullet : public GameObject {
    private:
        int m_power;
    public:
        BlueBullet ( 
            int x, int y, int direction, 
            int layer, double size, bool is_valid,
            int power, GameWorld *world);
        std::string GetType() const;
        int GetPower() const;
        void Update();
        bool IsEnemy() const;
        void SetHP(int HP);
        int GetHP() const;
};

 class Meteor : public GameObject {
    public:
        Meteor(
            int x, int y, GameWorld *world
        );
        void Update();
        std::string GetType() const;
        int GetPower()  const;
        bool IsEnemy() const;
        void SetHP(int HP);
        int GetHP() const;
};

#endif // GAMEOBJECTS_H__