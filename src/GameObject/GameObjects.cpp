#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"

GameObject::GameObject(int imageID, 
        int x, int y, int direction, 
        int layer, double size, bool is_valid,
        GameWorld *world)
    :ObjectBase(imageID, x, y, direction, layer, size), 
    m_is_valid(is_valid), 
    m_world(world) 
    {};

void GameObject::Update() {
    return;
}

bool GameObject::Get_valid() const{
    return m_is_valid;
}

void GameObject::Set_valid(bool is_valid) {
    m_is_valid = is_valid;
}

GameWorld *GameObject::GetWorld() const {
    return m_world;
};


/* ======================================== EXPLOSION ========================================*/

Explosion::Explosion(
            int x, int y, GameWorld *world
):
    GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5, true, world),
    m_tick_tock(0)
    {};

std::string  Explosion::GetType() const {
    return "EXPLOSION";
}

int Explosion::GetPower() const {
    return -1;
}

void Explosion::SetHP(int HP) {
    return;
};

int Explosion::GetHP() const{
    return -1;
};

bool Explosion::IsEnemy() const {
    return false;
} 

void Explosion::Update() {
    if (Get_valid())
    {
        m_tick_tock++;
        SetSize(GetSize() - 0.2);
        if (m_tick_tock == 20)
        {
            Set_valid(false);
        }   
    }
    else return;
}

/* ======================================== STAR ========================================*/

Star::Star( 
        int x, int y, int direction, 
        int layer, double size, bool is_valid, GameWorld *world)
    :GameObject(IMGID_STAR, 
            x, y, direction, 
            layer, size, is_valid, world)
{}

void Star::Update() {
    if (GetY() >= 0)
    {
        MoveTo(GetX(), GetY() - 1);
    }
    else
    {
        Set_valid(false);
    }
}

std::string Star::GetType() const {
    return "STAR";
};

int Star::GetPower() const {
    return -1;
} 

bool Star::IsEnemy() const {
    return false;
}

void Star::SetHP(int HP) {
    return;
}

int Star::GetHP() const {
    return -1;
}

/* ================================= BLUEBULLET ================================ */

BlueBullet::BlueBullet ( 
            int x, int y, int direction, 
            int layer, double size, bool is_valid,
            int power, GameWorld *world
):
    GameObject(IMGID_BLUE_BULLET, x, y, direction,
        layer, size, is_valid, world),
    m_power(power)
    {}
;

void BlueBullet::Update () {
    if (Get_valid())
    {
        if (GetY() >= WINDOW_HEIGHT)
        {
            Set_valid(false);
            return;
        }
        else
        {
            GetWorld()->WhenBulbombCollides(this);
            if (!Get_valid()) return;

            MoveTo(GetX(), GetY() + 6);

            GetWorld()->WhenBulbombCollides(this);
            if (!Get_valid()) return;
        }
    }
    else return ;
}

std::string BlueBullet::GetType() const {
    return "BLUEBULLET";
};

int BlueBullet::GetPower() const {
    return m_power;
}

bool BlueBullet::IsEnemy() const {
    return false;
}

void BlueBullet::SetHP(int HP) {
    return;
}

int BlueBullet::GetHP() const {
    return -1;
}

/* ==================================== METEOR:TEMP ================================= */

Meteor::Meteor(
    int x, int y, GameWorld *world
):
    GameObject(IMGID_METEOR, x, y, 0, 1, 2.0, true, world)
    {};

void Meteor::Update()  {
    if (Get_valid())
    {
        if (GetY() >= WINDOW_HEIGHT)
        {
            Set_valid(false);
            return;
        }
        GetWorld()->WhenBulbombCollides(this);

        SetDirection(GetDirection() + 5);
        MoveTo(GetX(), GetY() + 2);

        GetWorld()->WhenBulbombCollides(this);
    }
    else return;
}

std::string Meteor::GetType() const {
    return "METEOR";
};
        
int Meteor::GetPower() const {
    return -1;
}; 

bool Meteor::IsEnemy() const {
    return false;
}

void Meteor::SetHP(int HP) {
    return;
}

int Meteor::GetHP() const {
    return -1;
}



