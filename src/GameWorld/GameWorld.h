#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"
#include "utils.h"

class GameObject;
class Dawnbreaker;
class Enemy;
class Goodie;

class GameWorld : public WorldBase
{
public:
    GameWorld();

    virtual ~GameWorld();

    virtual void Init() override;

    virtual LevelStatus Update() override;

    void GenerateEnemies();

    virtual void CleanUp() override;

    virtual bool IsGameOver() const override;

    //FOR ENEMYS

    int GetOnScreen() const;

    void SetOnScreen(int onScreen); 

    bool IfCollides(GameObject *obj1, GameObject *obj2);

    void WhenRBCollides(GameObject *rb);

    void WhenBulbombCollides(GameObject *bb);

    void WhenEnemyCollides(Enemy *object);

    void WhenGoodieCollides(Goodie *object);

    int EnemyXDis(Enemy *enemy);

    void AlphaFire(Enemy *enemy);

    void OmegaFire(Enemy *enemy);

    void DawnFire();

    void DawnBomb();

    //FOR DAWN

    void IncreaseHP(int HP);

    void IncreasePower(int power);

    void IncreaseBombLeft(int bomb_num);

    void IncreaseOnScreen(int onscreen);

    void IncreaseDestroyed(int destroyed);

    void AlphaDestroyed(Enemy *alpha);

    void SigmaDestroyed(Enemy *sigma);

    void OmegaDestroyed(Enemy *omega);

private:
    std::list<GameObject *> m_object_list;

    Dawnbreaker *m_dawnbreaker;

    LevelStatus m_status;

    int m_players_remain; 

    int m_destroyed; 

    int m_onScreen;
};

#endif // !GAMEWORLD_H__
