#ifndef ENEMY_H__
#define ENEMY_H__

#include "GameObjects.h"

class Enemy : public GameObject
{
    public:
        Enemy(
            int imageID, 
            int x, int y, int direction, int layer, 
            double size, int HP, int MP, int power, 
            int velocity, GameWorld *world
        );
        int GetHP() const;
        int GetMP() const;
        int GetPower() const;
        int GetTimeRemain() const;
        int GetStrategy() const;
        int GetVelocity() const;
        void SetPower(int power);
        void SetHP(int HP);
        void SetMP(int MP);
        void SetTimeRemain(int time); 
        void SetStrategy(int strategy);
        void SetVelocity(int velocity);
        virtual void Update() override = 0;
        virtual std::string EnemyType() = 0;
        std::string GetType() const;
        bool IsEnemy() const;
        void Move();

    private:
        int m_HP;
        int m_MP;
        int m_power;
        int m_velocity;
        int m_tick_tock;
        int m_strategy;
};

class Alphatron : public Enemy
{
    public:
        Alphatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world);
        void Update();
        std::string EnemyType();
    private:
        
};

class Sigmatron : public Enemy
{
    public:
        Sigmatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world);
        void Update();
        std::string EnemyType();
    private:
      
};

class Omegatron : public Enemy
{
    public:
        Omegatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world);
        void Update();
        std::string EnemyType();
    private:
      
};

class RedBullet : public Enemy
{
    public:
        RedBullet(int x, int y, int direction,
            int power, GameWorld *world);
        //void Move_S();
        //void Move_SW();
        //void Move_SE();
        void Update();
        std::string EnemyType();
        void SetHP(int HP);
        int GetHP() const;
        bool IsEnemy() const;
    private:
};

#endif //ENEMY_H__