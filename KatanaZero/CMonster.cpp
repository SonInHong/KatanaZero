#include "pch.h"
#include "CMonster.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CRigidBody.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CNodeMgr.h"
#include "KeyMgr.h"
#include "CTopFloor.h"
#include "CStair.h"
#include "CFloor.h"


CMonster::CMonster()
	:Texture(nullptr)
	,IgnoreTopFloorList{}
	, RecogniseTopFloorList{}
{
}

CMonster::~CMonster()
{

}

void CMonster::Initialize()
{

	Scale.x = 35; Scale.y = 35;
	

	CreateCollider();
	CreateRigidBody();

	
}

void CMonster::Update()
{
	doublepoint& velocity = dynamic_cast<CRigidBody*>(m_Component[(UINT)COMPONENT_TYPE::RIGIDBODY][0])->GetVelocity();
	doublepoint& force = dynamic_cast<CRigidBody*>(m_Component[(UINT)COMPONENT_TYPE::RIGIDBODY][0])->GetForce();

	bool& OnGround = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetOnGround();
	int& OnStair = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetOnStair();
	int& OnWall = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetOnWall();
	int& WallGrab = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetWallGrab();
	int& Roll = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetRoll();
	int& Flip = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetFlip();
	bool& AttackOnOff = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetAttack();
	double& AttackAngle = dynamic_cast<CRigidBody*>(GetComponent(COMPONENT_TYPE::RIGIDBODY)[0])->GetAttackAngle();


	CPlayer* player = dynamic_cast<CPlayer*>(CSceneMgr::Create()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER)[0]);
	Move_Order _order = Move_Order::End;

	for (int i = 0; i < IgnoreTopFloorList.size(); ++i)
	{
		IgnoreTopFloorList[i]->ResetIgnoreList();
	}

	IgnoreTopFloorList.clear();

	for (int i = 0; i < RecogniseTopFloorList.size(); ++i)
	{
		RecogniseTopFloorList[i]->ResetRecogniseList();
	}
	RecogniseTopFloorList.clear();

	if (KeyMgr::Create()->key(Key::M).pressed)
	{
		std::vector<CFloor::ConnectedNode> path = CNodeMgr::FindPath(RecentFloor, player->GetRecentFloor());
		int a = 0; //디버깅용
	}
	
	std::vector<CFloor::ConnectedNode> path = CNodeMgr::FindPath(RecentFloor, player->GetRecentFloor());
	
	if (path.size() == 0)
	{
		//길이 없음
	}

	if (path.size() == 1)
	{
		//스테이
		_order = Move_Order::Stay;
	}

	if (path.size() > 1)
	{
		_order = path[1].HowToMove;
	}

	switch (_order)
	{
	
	case Move_Order::End:
	{

	}
	break;

	case Move_Order::MoveLeft:
	{
		MoveLeft();
		force.x -= 250000;
	}
	break;

	case Move_Order::MoveRight:
	{
		MoveRight();
		force.x += 250000;
	}
	break;

	case Move_Order::ClimbDownLeft:
	{

		if (dynamic_cast<CStair*>(RecentFloor) == nullptr)
		{
			std::vector<CFloor::ConnectedNode> CN = RecentFloor->GetConnectedNodes();

			for (int i = 0; i < CN.size(); ++i)
			{
				CTopFloor* ct = dynamic_cast<CTopFloor*>(CN[i].node);

				if (ct)
				{
					ct->IgnoreMe(this);
					IgnoreTopFloorList.push_back(ct);
										
				}
			}
			
			if (Pos.x < RecentFloor->GetPos().x - (RecentFloor->GetScale().x * RecentFloor->GetResize().x) / 2)
				OnStair = Right;
		}

		force.x -= 250000;

		
		


		ClimbDownLeft();
	}
	break;

	case Move_Order::ClimbDownRight:
	{

		if (dynamic_cast<CStair*>(RecentFloor) == nullptr)
		{
			std::vector<CFloor::ConnectedNode> CN = RecentFloor->GetConnectedNodes();

			for (int i = 0; i < CN.size(); ++i)
			{
				CTopFloor* ct = dynamic_cast<CTopFloor*>(CN[i].node);

				if (ct)
				{
					ct->IgnoreMe(this);
					IgnoreTopFloorList.push_back(ct);

				}
			}

			if (Pos.x > RecentFloor->GetPos().x + (RecentFloor->GetScale().x * RecentFloor->GetResize().x) / 2)
				OnStair = Left;
		}

		force.x += 250000;

		ClimbDownRight();
	}
	break;

	case Move_Order::Stay:
	{
		if(player->GetPos().x > Pos.x - 100)
			force.x += 250000;

		if (player->GetPos().x < Pos.x + 100)
			force.x -= 250000;

		Stay();
	}
	break;

	case Move_Order::MoveToTopFloorRight:
	{
		std::vector<CFloor::ConnectedNode> CN = RecentFloor->GetConnectedNodes();
		for (int i = 0; i < CN.size(); ++i)
		{
			CTopFloor* ct = dynamic_cast<CTopFloor*>(CN[i].node);
			if (ct)
			{
				ct->RecogniseMe(this);
				RecogniseTopFloorList.push_back(ct);
			}

		}

		force.x += 250000;
	}
	break;

	case Move_Order::MoveToTopFloorLeft:
	{
		std::vector<CFloor::ConnectedNode> CN = RecentFloor->GetConnectedNodes();
		for (int i = 0; i < CN.size(); ++i)
		{
			CTopFloor* ct = dynamic_cast<CTopFloor*>(CN[i].node);
			if (ct)
			{
				ct->RecogniseMe(this);
				RecogniseTopFloorList.push_back(ct);
			}

		}

		force.x -= 250000;
	}
	break;
	
	}

}

void CMonster::Render(HDC _dc)
{
	

	CObject::Render(_dc);
}

void CMonster::MoveLeft()
{

}

void CMonster::MoveRight()
{
}

void CMonster::ClimbDownRight()
{
}

void CMonster::ClimbDownLeft()
{
}

void CMonster::Stay()
{
}
