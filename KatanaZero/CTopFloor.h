#pragma once
#include "CFloor.h"
class CTopFloor :
    public CFloor
{
public:
    CTopFloor();
    virtual ~CTopFloor();

    virtual bool Collide(CObject* other);
   
};

