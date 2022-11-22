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
	, MainOrder(Main_Order::PlayerDetected)
	,MoveOrder(Move_Order::End)
	,ActionOrder(Action_Order::End)
{
}

CMonster::~CMonster()
{

}

void CMonster::Initialize()
{

	
	CreateCollider(doublepoint{0,7});
	CreateRigidBody();

	
}

void CMonster::Update()
{	
	CPlayer* player = dynamic_cast<CPlayer*>(CSceneMgr::Create()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER)[0]);
	MoveOrder = Move_Order::End;
	ActionOrder = Action_Order::End;

	if (MainOrder == Main_Order::PlayerDetected) // �÷��̾ �����Ǿ����� ã�Ƽ� ���󰣴�
	{
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
			int a = 0; //������
		}

		std::vector<CFloor::ConnectedNode> path = CNodeMgr::FindPath(RecentFloor, player->GetRecentFloor());

		if (path.size() == 0)
		{
			//���� ����
			MoveOrder = Move_Order::End;
		}

		if (path.size() == 1)
		{
			//������
			MoveOrder = Move_Order::Stay;
		}

		if (path.size() > 1)
		{
			MoveOrder = path[1].HowToMove;
		}
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
