#pragma once
#include "CObject.h"
#include "CTexture.h"

class CTopFloor;

class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();

    virtual void Initialize();
    virtual void Update();
    virtual void Render(HDC _dc);

    void SetLookDirection(int b) { LookDirection = b; }

protected:
    CTexture* Texture;
    int LookDirection;
    doublepoint PrevPos;
    bool PrevOnFloor;
    bool AttackOnAir;
    long double AttackTimer;
    bool AttackTimerSwitch;

    //¿À´õµé
    Main_Order MainOrder;
    Move_Order MoveOrder;
    Action_Order ActionOrder;

    void MoveLeft();
    void MoveRight();
    void ClimbDownRight();
    void ClimbDownLeft();
    void Stay();

    std::vector<CTopFloor*> IgnoreTopFloorList;
    std::vector<CTopFloor*> RecogniseTopFloorList;
};

