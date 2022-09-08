#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"
#include "Goodie.h"

/* ========================================= GOODIE:TEMP ============================================= */

Goodie::Goodie( 
    int imageID,
    int x, int y, int direction, int layer, double size, 
    GameWorld *world
):
    GameObject(imageID, x, y, direction, layer, size, true, world)
    {};

void Goodie::Update() {
    if (Get_valid())
    {
        if (GetY() < 0)
        {
            Set_valid(false);
            return;
        }
        else
        {
            GetWorld()->WhenGoodieCollides(this);
            if(!Get_valid()) return;

            MoveTo(GetX(), GetY() - 2);

            GetWorld()->WhenGoodieCollides(this);
        }
    }
    else return;
};

bool Goodie::IsEnemy() const {
    return false;
}

/* ========================================= HPRESTORE:TEMP ============================================= */

HPRestoreGoodie::HPRestoreGoodie(
   int x, int y, GameWorld *world
):
    Goodie(IMGID_HP_RESTORE_GOODIE, x, y, 0, 2, 0.5, world)
    {};

std::string HPRestoreGoodie::GetType() const {
    return "HPRESTORE";
};

void HPRestoreGoodie::Restore() {
    GetWorld()->IncreaseHP(50);
    GetWorld()->IncreaseScore(20);
}

int HPRestoreGoodie::GetPower() const {
    return -1;
};

void HPRestoreGoodie::SetHP(int HP) {
    return;
}

int HPRestoreGoodie::GetHP() const {
    return -1;
}

/* ========================================= POWERUPGOODIE:TEMP ============================================= */

PowerUpGoodie::PowerUpGoodie(
   int x, int y, GameWorld *world
):
    Goodie(IMGID_POWERUP_GOODIE, x, y, 0, 2, 0.5, world)
    {};

void PowerUpGoodie::Restore() {
    GetWorld()->IncreasePower(1);
    GetWorld()->IncreaseScore(20);
}

std::string PowerUpGoodie::GetType() const {
    return "POWERUP";
};

int PowerUpGoodie::GetPower() const {
    return -1;
};

void PowerUpGoodie::SetHP(int HP) {
    return;
}

int PowerUpGoodie::GetHP() const {
    return -1;
}

/* ========================================= METEORPGOODIE:TEMP ============================================= */

MeteorGoodie::MeteorGoodie(
   int x, int y, GameWorld *world
):
    Goodie(IMGID_METEOR_GOODIE, x, y, 0, 2, 0.5, world)
    {};

void MeteorGoodie::Restore() {
    GetWorld()->IncreaseBombLeft(1);
    GetWorld()->IncreaseScore(20);
}

std::string MeteorGoodie::GetType() const {
    return "METEORGOODIE";
};

int MeteorGoodie::GetPower() const {
    return -1;
};

void MeteorGoodie::SetHP(int HP) {
    return;
}

int MeteorGoodie::GetHP() const {
    return -1;
}