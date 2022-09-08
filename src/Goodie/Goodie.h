#ifndef GOODIE_H__
#define GOODIE_H__

#include "GameObjects.h"

class Goodie : public GameObject {
    public:
        Goodie(int imageID, 
            int x, int y, int direction, 
            int layer, double size, 
            GameWorld *world);
        void Update();
        virtual void Restore() = 0;
        bool IsEnemy() const;
};

class HPRestoreGoodie : public Goodie {
    public:
        HPRestoreGoodie(
            int x, int y, GameWorld *world
        );
        void Restore();
        std::string GetType() const;
        int GetPower() const;
        void SetHP(int HP);
        int GetHP() const;
};  

class PowerUpGoodie : public Goodie {
    public:
        PowerUpGoodie(
            int x, int y, GameWorld *world
        );
        void Restore();
        std::string GetType() const;
        int GetPower() const;
        void SetHP(int HP);
        int GetHP() const;
};  

class MeteorGoodie : public Goodie {
    public:
        MeteorGoodie(
            int x, int y, GameWorld *world
        );
        void Restore();
        std::string GetType() const;
        int GetPower() const;
        void SetHP(int HP);
        int GetHP() const;
};  

#endif //GOODIE_H__