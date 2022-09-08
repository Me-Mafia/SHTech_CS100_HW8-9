#ifndef DAWNBREAKER_H__
#define DAWNBREAKER_H__

#include "GameObjects.h"

class Dawnbreaker : public GameObject
{
    public:
        Dawnbreaker( 
            int x, int y, int direction, 
            int layer, double size, bool is_valid,
            int HP, int MP, int bomb, GameWorld *world);
        int GetHP() const;
        int GetPower() const;
        int GetBombLeft() const;

        void SetPower(int power);
        void SetHP(int HP);
        void SetBombLeft(int bomb_num); 
        std::string GetType() const;
        void Update();
        bool IsEnemy() const;
    
    private:
        int m_HP;
        int m_MP;
        int m_bomb_left;
        int m_power;
};

#endif //DAWNBREAKER_H__