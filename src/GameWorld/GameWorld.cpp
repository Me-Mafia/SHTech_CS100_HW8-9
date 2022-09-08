#include "GameWorld.h"
#include "GameObjects.h"
#include "Enemy.h"
#include "Goodie.h"
#include "Dawnbreaker.h"

GameWorld::GameWorld()
{
    m_players_remain = 3;
}

GameWorld::~GameWorld()
{
    
}

void GameWorld::Init()
{
    m_status = LevelStatus::ONGOING; 
    for (size_t i = 0; i < 30; i++)
    {
        m_object_list.push_back(
            new Star( 
            randInt(0, WINDOW_WIDTH-1), 
            randInt(0, WINDOW_HEIGHT-1),
            0, 4, 0.01 * randInt(10, 40), true, this)
        );
    }

    m_dawnbreaker = new Dawnbreaker(
        300, 100, 0, 0, 1.0, true,
        100, 10, 0, this
    );

    m_destroyed = 0;
    m_onScreen = 0;
}

LevelStatus GameWorld::Update()
{
    //GENERATE THE STARS
    if (randInt(1, 30) == 1)
    {
        m_object_list.push_back(
            new Star( 
                randInt(0, WINDOW_WIDTH-1), 
                WINDOW_HEIGHT-1,
                0, 4, 0.01 * randInt(10, 40), 1, this
            )
        );
    }

    GenerateEnemies();

    // Update  & Check the container
    for (auto i = m_object_list.begin(); i != m_object_list.end(); ++i)
    {
        (*i)->Update();
    }

    m_dawnbreaker->Update();

    // CHECK IF DAWNBREAKER IS DESTROYED
    if (m_dawnbreaker->GetHP() <= 0)
    {
        m_players_remain--;
        return LevelStatus::DAWNBREAKER_DESTROYED;
    }
    if (m_destroyed == 3 * GetLevel())
    {
        return LevelStatus::LEVEL_CLEARED;
    }

    for (auto i = m_object_list.begin(); i != m_object_list.end(); )
    {
        if (!(*i)->Get_valid())
        {
            delete (*i);
            i = m_object_list.erase(i);
        }
        else ++i;
    }

    SetStatusBarMessage(
        "HP: " 
        + std::to_string(m_dawnbreaker->GetHP())
        + "/100   Meteors: "
        + std::to_string(m_dawnbreaker->GetBombLeft())
        + "   Lives: "
        + std::to_string(m_players_remain)
        + "   Level: "
        + std::to_string(GetLevel())
        + "   Enemies: "
        + std::to_string(m_destroyed)
        + "/"
        + std::to_string(3 * GetLevel())
        + "   Score: "
        + std::to_string(GetScore())
        //+ "   OnScreen: "
        //+ std::to_string(m_onScreen)
    );

    return LevelStatus::ONGOING;  
}

void GameWorld::GenerateEnemies() {
    //GENERATE THE ENEMIES
    int toDestroy = 3 * GetLevel() - m_destroyed;
    int maxOnScreen = (GetLevel() + 5) / 2;
    int allowed = toDestroy > maxOnScreen? maxOnScreen: toDestroy;
    if (randInt(1, 100) <= (allowed - m_onScreen))
    {
        int p1 = 6;
        int p2 = GetLevel() - 1 > 0 ? GetLevel() - 1: 0;
        p2 *= 2; 
        int p3 = GetLevel() - 2 > 0 ? GetLevel() - 2: 0;
        p3 *= 3;
        if (randInt(1, p1 + p2 + p3) <= p1)
        {
            m_object_list.push_back(
                new Alphatron( 
                    randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT -1,
                    20 + 2 * GetLevel(), 
                    4 + GetLevel(), 
                    2 + (GetLevel() / 5), 
                    this
                ) 
            );
        }
        else if (randInt(1, p2 + p3) <= p2)
        {
            m_object_list.push_back(
                new Sigmatron( 
                    randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT -1,
                    25 + 5 * GetLevel(), 
                    -1, 
                    2 + (GetLevel() / 5), 
                    this
                ) 
            );
        }
        else
        {
            m_object_list.push_back(
                new Omegatron( 
                    randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT -1,
                    20 + GetLevel(), 
                    2 + 2 * GetLevel(), 
                    3 + (GetLevel() / 4), 
                    this
                ) 
            );
        }
        m_onScreen++;
    } 
}

void GameWorld::CleanUp()
{
    for (auto i = m_object_list.begin(); i != m_object_list.end();)
    {
        delete (*i);
        i = m_object_list.erase(i);
    }

    if (m_dawnbreaker != nullptr)
    {
        delete m_dawnbreaker;
    }  
}

bool GameWorld::IsGameOver() const
{
    if (m_players_remain > 0) return false;
    else return true;    
}

int GameWorld::GetOnScreen() const {
    return m_onScreen;
};

void GameWorld::SetOnScreen(int onScreen) {
    m_onScreen = onScreen;
}; 

bool GameWorld::IfCollides(GameObject *obj1, GameObject *obj2) {
    int obx1 = obj1->GetX();
    int oby1 = obj1->GetY();
    double obsize1 = obj1->GetSize();
    int obx2 = obj2->GetX();
    int oby2 = obj2->GetY();
    double obsize2 = obj2->GetSize();
    double dis = sqrt((obx1 - obx2) * (obx1 - obx2) + (oby1 - oby2) * (oby1 - oby2));

    if (dis < 30 * (obsize1 + obsize2) 
        && obj1->Get_valid() 
        && obj2->Get_valid()) return true;      
    else return false;
};

void GameWorld::WhenRBCollides(GameObject *rb) {
    if (IfCollides(rb, m_dawnbreaker))
    {
        rb->Set_valid(false);
        IncreaseHP(-(rb->GetPower()));
    }
    return; 
}

void GameWorld::WhenBulbombCollides(GameObject *bb) {
    for (auto i = m_object_list.begin(); i != m_object_list.end(); ++i)
    {
        if (IfCollides(bb, (*i)))
        {
            if ((bb)->GetType() == "BLUEBULLET" 
                && (bb)->Get_valid() 
                && (*i)->IsEnemy()
                && (*i)->Get_valid())
            {
                (*i)->SetHP((*i)->GetHP() - (bb)->GetPower());
                (bb)->Set_valid(false); 
                return;   
            }
            
            else if ((bb)->GetType() == "METEOR" 
                && (bb)->Get_valid() 
                && (*i)->IsEnemy()
                && (*i)->Get_valid())
            {
                (*i)->SetHP(0);
                // MAY OCCUR MANY TIMES
            }
        }    
    } 
    
}

void GameWorld::WhenGoodieCollides(Goodie *goodie) {
    if (IfCollides(goodie, m_dawnbreaker))
    {
        goodie->Restore();
        goodie->Set_valid(false);
    }
    return;  
}

void GameWorld::WhenEnemyCollides(Enemy *object) {
    for (auto i = m_object_list.begin(); i != m_object_list.end(); ++i)
    {
        if (IfCollides(object, (*i)))
        {
            if ((*i)->GetType() == "BLUEBULLET"
                && (*i)->Get_valid()
                && object->Get_valid() )
            {
                object->SetHP(object->GetHP() - (*i)->GetPower());
                (*i)->Set_valid(false);  // BLUEBULLET
                if ((object)->GetHP() <= 0) return;    
            }

            else if ((*i)->GetType() == "METEOR"
                && (*i)->Get_valid()
                && object->Get_valid() )
            {
                object->SetHP(0);
                return;
            }
        }    
    } 
    if (IfCollides(object, m_dawnbreaker))
    {
        object->SetHP(0);
        IncreaseHP(-20);
    }
    return;  
}

int GameWorld::EnemyXDis(Enemy *enemy) {
    return (enemy->GetX() - m_dawnbreaker->GetX());
}

void GameWorld::AlphaFire(Enemy *enemy) {
    if (enemy->Get_valid())
    {
        m_object_list.push_back(
            new RedBullet(
                enemy->GetX(), enemy->GetY() - 50, 180,
                enemy->GetPower(), this
            )
        );
    }  
} 

void GameWorld::OmegaFire(Enemy *enemy) {
    if (enemy->Get_valid())
    {
        m_object_list.push_back(
            new RedBullet(
                enemy->GetX(), enemy->GetY() - 50, 162,
                enemy->GetPower(), this
            )
        );
        m_object_list.push_back(
            new RedBullet(
                enemy->GetX(), enemy->GetY() - 50, 198,
                enemy->GetPower(), this
            )
        );
    }
}

void GameWorld::DawnFire()
{
    m_object_list.push_back(
        new BlueBullet(
            m_dawnbreaker->GetX(), m_dawnbreaker->GetY() + 50,
            0, 1, 
            0.5 + 0.1 * m_dawnbreaker->GetPower(), 
            true, 
            5 + 3 * m_dawnbreaker->GetPower(), 
            this
        )
    );
};

void GameWorld::DawnBomb()
{
    m_object_list.push_back(
        new Meteor(
            m_dawnbreaker->GetX(), m_dawnbreaker->GetY() + 100,
            this
        )
    );
};

void GameWorld::IncreaseHP(int HP) {
    // PLUS ON THE BASIS
    int HP_set = m_dawnbreaker->GetHP() + HP < 100? m_dawnbreaker->GetHP() + HP: 100;
    m_dawnbreaker->SetHP(HP_set);
}

void GameWorld::IncreasePower(int power) {
    m_dawnbreaker->SetPower(m_dawnbreaker->GetPower() + power);
}

void GameWorld::IncreaseBombLeft(int bomb_num) {
    m_dawnbreaker->SetBombLeft(m_dawnbreaker->GetBombLeft() + bomb_num);
}

void GameWorld::IncreaseOnScreen(int onscreen) {
    m_onScreen += onscreen;
}

void GameWorld::IncreaseDestroyed(int destroyed) {
    m_destroyed += destroyed;
}

void GameWorld::AlphaDestroyed(Enemy *alpha)
{
    m_onScreen--;
    m_destroyed++;
    IncreaseScore(50);
    m_object_list.push_back(
        new Explosion(
            alpha->GetX(), alpha->GetY(), this
        )
    );
};

void GameWorld::SigmaDestroyed(Enemy *sigma)
{
    m_onScreen--;
    m_destroyed++;
    IncreaseScore(100);
    m_object_list.push_back(
        new Explosion(
            sigma->GetX(), sigma->GetY(), this
        )
    );
    if (randInt(1, 5) == 1)
    {
        m_object_list.push_back(
            new HPRestoreGoodie(
                sigma->GetX(), sigma->GetY(), this
            )
        );
    }
    
};

void GameWorld::OmegaDestroyed(Enemy *omega)
{
    m_onScreen--;
    m_destroyed++;
    IncreaseScore(200);
    m_object_list.push_back(
        new Explosion(
            omega->GetX(), omega->GetY(), this
        )
    );
    if (randInt(1, 5) <= 2)
    {
        if (randInt(1, 5) == 1)
        {
            m_object_list.push_back(
                new MeteorGoodie(
                    omega->GetX(), omega->GetY() , this
                )
            );
        }
        else
        {
            m_object_list.push_back(
                new PowerUpGoodie(
                    omega->GetX(), omega->GetY() , this
                )
            );
        }
    }
};