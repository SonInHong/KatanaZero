#pragma once
#include "CObject.h"
#include <map>
class CFloor :
    public CObject
{
public:
    CFloor();
    virtual ~CFloor();

    virtual void Initialize();
    virtual bool Collide(CObject* other);
    virtual bool Colliding(CObject* other);
    virtual bool CollideEscape(CObject* other);
    virtual bool DontCollide(CObject* other);

    std::map<DWORD_PTR, POINT>& GetCollideDir() { return m_CollideDir; }

protected:
    std::map<DWORD_PTR, POINT> m_CollideDir;
    

};

