#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"
#include "Dawnbreaker.h"

/* ==================================== DAWNBREAKER =============================== */

Dawnbreaker::Dawnbreaker(
    int x, int y, int direction, 
    int layer, double size, bool is_valid,
    int HP, int MP, int bomb, GameWorld *world
):
    GameObject(IMGID_DAWNBREAKER, x, y, direction, layer, size, is_valid, world),
    m_HP(HP),
    m_MP(MP),
    m_bomb_left(bomb),
    m_power(0)
    {};

int Dawnbreaker::GetHP() const{
    return m_HP;
}

int Dawnbreaker::GetPower() const {
    return m_power;
}

int Dawnbreaker::GetBombLeft() const {
    return m_bomb_left;
}

void Dawnbreaker::SetBombLeft(int bomb_num) {
    m_bomb_left = bomb_num;
}

void Dawnbreaker::SetPower(int power) {
    m_power = power;
}

void Dawnbreaker::SetHP(int HP) {
    m_HP = HP;
}

void Dawnbreaker::Update() {
    if (m_HP <= 0 || !Get_valid())
    {
        Set_valid(false);
        return;
    }
    else
    {
        // MOVE
        if (GetWorld()->GetKey(KeyCode::LEFT) && GetX() >= 0)  
            MoveTo(GetX() - 4, GetY());
        if (GetWorld()->GetKey(KeyCode::RIGHT) && GetX() <= WINDOW_WIDTH - 1)  
            MoveTo(GetX() + 4, GetY());
        if (GetWorld()->GetKey(KeyCode::UP) && GetY() <= WINDOW_HEIGHT - 1)  
            MoveTo(GetX(), GetY() + 4);
        if (GetWorld()->GetKey(KeyCode::DOWN) && GetY() >= 50)  
            MoveTo(GetX(), GetY() - 4);

        // ATTACK
        if (GetWorld()->GetKey(KeyCode::FIRE1) && m_MP >= 10)
        {
            GetWorld()->DawnFire();
            m_MP -= 10;
        }
        if (GetWorld()->GetKeyDown(KeyCode::FIRE2) && m_bomb_left > 0)
        {
            GetWorld()->DawnBomb();
            m_bomb_left--;
        }
        


        // RECOVER
        if (m_MP <= 10) m_MP++;
        return;
    }
}

std::string Dawnbreaker::GetType() const {
    return "DAWNBREAKER";
};

bool Dawnbreaker::IsEnemy() const {
    return false;
}