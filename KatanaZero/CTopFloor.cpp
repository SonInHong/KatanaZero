#include "pch.h"
#include "CTopFloor.h"
#include "CPlayer.h"
#include "CComponent.h"
#include "CRigidBody.h"
#include "CCollider.h"

#include "KeyMgr.h"

CTopFloor::CTopFloor()
{
}

CTopFloor::~CTopFloor()
{
}

bool CTopFloor::Collide(CObject* other)
{

	std::map<DWORD_PTR, POINT>::iterator iter = m_CollideDir.find((DWORD_PTR)other);
	if (iter == m_CollideDir.end())
	{
		m_CollideDir.insert(std::make_pair((DWORD_PTR)other, POINT{ 0,0 }));
		iter = m_CollideDir.find((DWORD_PTR)other);
	}
	
	((CCollider*)m_Component[(UINT)COMPONENT_TYPE::COLLIDER][0])->SetCollision(true);

	doublepoint OtherPosition = ((CCollider*)other->GetComponent(COMPONENT_TYPE::COLLIDER)[0])->GetAbsPos();
	doublepoint OtherScale = ((CCollider*)other->GetComponent(COMPONENT_TYPE::COLLIDER)[0])->GetScale();

	double dx = (OtherScale.x + Scale.x * Resize.x) / 2 - abs(Pos.x - OtherPosition.x);
	double dy = (OtherScale.y + Scale.y * Resize.y) / 2 - abs(Pos.y - OtherPosition.y);

	if (dx > dy || dy < 1)
	{
		if (Pos.y > OtherPosition.y)
			iter->second = POINT{ 0,1 };
	}


	if (iter->second.y == 1)
	{
		if (other->GetComponent(COMPONENT_TYPE::RIGIDBODY).empty())
			return true;

		CRigidBody* p = dynamic_cast<CRigidBody*>(other->GetComponent(COMPONENT_TYPE::RIGIDBODY)[0]);
		if (p)
		{
			//double dy = (other->GetScale().y * other->GetResize().y + Scale.y * Resize.y) / 2 - abs(Pos.y - other->GetPos().y);

			other->GetPos().y -= iter->second.y * dy;
			other->SetState(Object_State::ON_FLOOR);

			dynamic_cast<CRigidBody*>(other->GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->SetOnGround(true);
			dynamic_cast<CRigidBody*>(other->GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->SetOnStair(0);

			other->GetComponent(COMPONENT_TYPE::COLLIDER)[0]->Update();

			return true;
		}
	}

	return false;
}


