#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"
#include "Enemy.h"

/* ==================================== ENEMY:TEMP ================================= */

Enemy::Enemy( 
    int imageID,
    int x, int y, int direction, int layer, double size, 
    int HP, int MP, int power, 
    int velocity, GameWorld *world
) 
    : GameObject(imageID, x, y, direction, layer, size, true, world),
    m_HP(HP),
    m_MP(MP),
    m_power(power),
    m_velocity(velocity),
    m_tick_tock(0)
    {};

int Enemy::GetHP() const {
    return m_HP;
}

int Enemy::GetMP() const {
    return m_MP;
}

int Enemy::GetPower() const {
    return m_power;
}

int Enemy::GetTimeRemain() const {
    return m_tick_tock;
}

int Enemy::GetStrategy() const {
    return m_strategy;
}

int Enemy::GetVelocity() const {
    return m_velocity;
}

void Enemy::SetPower(int power) {
    m_power = power;
}

void Enemy::SetHP(int HP) {
    m_HP = HP;
}

void Enemy::SetMP(int MP) {
    m_MP = MP;
}

void Enemy::SetTimeRemain(int time) {
    m_tick_tock = time;
}

void Enemy::SetStrategy(int strategy) {
    m_strategy = strategy;
}

void Enemy::SetVelocity(int velocity) {
    m_velocity = velocity;
}

std::string Enemy::GetType() const {
    return "ENEMY";
};

bool Enemy::IsEnemy() const {
    return true;
}

void Enemy::Move()
{
    int timeRemain = GetTimeRemain();
    if (timeRemain == 0)
    {
        SetStrategy(90 * randInt(1, 3));
        SetTimeRemain(randInt(10, 50));
    }

    if (GetX() < 0)
    {
        SetStrategy(90);
        SetTimeRemain(randInt(10, 50));
    }
    else if (GetX() >= WINDOW_WIDTH)
    {
        SetStrategy(270);
        SetTimeRemain(randInt(10, 50));
    }
    int strategy = GetStrategy();
    switch (strategy)
    {
    case 90:
        MoveTo(GetX() + GetVelocity(), GetY() - GetVelocity());
        break;
    case 270:
        MoveTo(GetX() - GetVelocity(), GetY() - GetVelocity());
        break;
    default:
        MoveTo(GetX(), GetY() - GetVelocity());
        break;
    }
    SetTimeRemain(GetTimeRemain() - 1);
}

/* ==================================== ALPHATRON:TEMP ================================= */

Alphatron::Alphatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world
):
    Enemy( 
        IMGID_ALPHATRON, x, y, 180, 0, 1.0, 
        HP, 25, power, velocity, world
    ) 
{};

void Alphatron::Update() {
    if (Get_valid())
    {
        if (GetY() < 0)
        {
            Set_valid(false);
            GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
            return;
        }

        GetWorld()->WhenEnemyCollides(this);
        if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->AlphaDestroyed(this);
            return;
        }

        int distance = GetWorld()->EnemyXDis(this);
        if ( distance >= -10 && distance <= 10)
        {
            if (GetMP() >= 25 && randInt(1, 100) <= 25)
            {
                GetWorld()->AlphaFire(this);
                SetMP(GetMP() - 25);
            }
        }

        if (GetMP() < 25)
        {
            SetMP(GetMP() + 1);
        }

        //TRY TO MOVE...
        Move();

        GetWorld()->WhenEnemyCollides(this);
        if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->AlphaDestroyed(this);
            return;
        }        
    }
    else return;
};

std::string Alphatron::EnemyType() {
    return "ALPHA";
};

/* ==================================== SIGMATRON:TEMP ================================= */

Sigmatron::Sigmatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world
):
    Enemy( 
        IMGID_SIGMATRON, x, y, 180, 0, 1.0, 
        HP, -1, -1, velocity, world
    ) 
{};

void Sigmatron::Update() {
    if (Get_valid())
    {
        if (GetY() < 0)
        {
            Set_valid(false);
            GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
            return;
        }

        GetWorld()->WhenEnemyCollides(this);
        if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->SigmaDestroyed(this);
            return;
        }

        int distance = GetWorld()->EnemyXDis(this);
        if ( distance >= -10 && distance <= 10)
        {
            SetStrategy(180);
            SetTimeRemain(WINDOW_HEIGHT);
            SetVelocity(10);
        }

        //TRY TO MOVE...
        Move();

        GetWorld()->WhenEnemyCollides(this);
       if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->SigmaDestroyed(this);
            return;
        }

        if (GetMP() < 25)
        {
            SetMP(GetMP() + 1);
        }
        
    }
    else return;
};

std::string Sigmatron::EnemyType() {
    return "SIGMA";
};

/* ==================================== OMEGATRON:TEMP ================================= */

Omegatron::Omegatron(int x, int y, 
            int HP, int power, int velocity, GameWorld *world
):
    Enemy( 
        IMGID_OMEGATRON, x, y, 180, 0, 1.0, 
        HP, 50, power, velocity, world
    ) 
{};

void Omegatron::Update() {
    if (Get_valid())
    {
        if (GetY() < 0)
        {
            Set_valid(false);
            GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
            return;
        }

        GetWorld()->WhenEnemyCollides(this);
        if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->OmegaDestroyed(this);
            return;
        }
        
        if (GetMP() >= 50)
        {          
            GetWorld()->OmegaFire(this);
            SetMP(GetMP() - 50);
        }
        else
        {
            SetMP(GetMP() + 1);
        }

        //TRY TO MOVE...
        Move();

        GetWorld()->WhenEnemyCollides(this);
        if (GetHP() <= 0) 
        {
            Set_valid(false);
            GetWorld()->OmegaDestroyed(this);
            return;
        }      
    }
    else return;
};

std::string Omegatron::EnemyType() {
    return "OMEGA";
};

/* ==================================== REDBULLET:TEMP ================================= */

RedBullet::RedBullet(int x, int y, int direction, 
            int power,  GameWorld *world
):
    Enemy( 
        IMGID_RED_BULLET, x, y, direction, 1, 0.5, -1, -1, power,-1, world
    ) 
{};

void RedBullet::Update() {
    if (Get_valid())
    {
        if (GetY() < 0)
        {
            Set_valid(false);
            return;
        }
        else
        {
            GetWorld()->WhenRBCollides(this);
            if (!Get_valid()) return;

            switch (GetDirection())
            {
            case 162:
                MoveTo(GetX() + 2, GetY() - 6);
                break;
            case 198:
                MoveTo(GetX() - 2, GetY() - 6);
                break;
            default:
                MoveTo(GetX(), GetY() - 6);
                break;
            }

            GetWorld()->WhenRBCollides(this);
            return;
        }
    }
    else return;
}

std::string RedBullet::EnemyType() {
    return "REDBULLET";
};

bool RedBullet::IsEnemy() const {
    return false;
}

void RedBullet::SetHP(int HP) {
    return;
}

int RedBullet::GetHP() const {
    return -1;
}