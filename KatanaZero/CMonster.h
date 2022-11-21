#pragma once
#include "CObject.h"
#include "CTexture.h"

class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();

    virtual void Initialize();
    virtual void Update();
    virtual void Render(HDC _dc);

private:
    CTexture* Texture;
};

