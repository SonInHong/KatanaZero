#include "pch.h"
#include "CGrunt.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CTopFloor.h"
#include "CStair.h"
#include "CFloor.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "KeyMgr.h"

CGrunt::CGrunt()
{
}

CGrunt::~CGrunt()
{
}

void CGrunt::Initialize()
{
	CMonster::Initialize();
	CreateAnimator();

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_idle\\right", L"GruntIdleRight", doublepoint{ 0,0 }, doublepoint{ 30,36 }, 8, 0.07, true);
	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_idle\\left", L"GruntIdleLeft", doublepoint{ 0,0 }, doublepoint{ 30,36 }, 8, 0.07, true);

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_run\\right", L"GruntRunRight", doublepoint{ 0,0 }, doublepoint{ 36,39 }, 10, 0.07, true);
	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_run\\left", L"GruntRunLeft", doublepoint{ 0,0 }, doublepoint{ 36,39 }, 10, 0.07, true);

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_turn\\right", L"GruntTurnRight", doublepoint{ 0,0 }, doublepoint{ 36,35 }, 8, 0.1, false);
	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_turn\\left", L"GruntTurnLeft", doublepoint{ 0,0 }, doublepoint{ 36,35 }, 8, 0.1, false);

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_attack\\right", L"GruntAttackRight", doublepoint{ 0,0 }, doublepoint{ 44,42 }, 8, 0.07, false);
	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->CreateSpriteAndAnimation(L"Enemy\\Grunt\\spr_grunt_attack\\left", L"GruntAttackLeft", doublepoint{ 0,0 }, doublepoint{ 44,42 }, 8, 0.07, false);

	//==============================================================================================================================================================
	//이벤트 지정
	//==============================================================================================================================================================

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])
		->FindAnimation(L"GruntTurnRight")->m_CompleteEvent = std::bind(&CMonster::SetLookDirection, this, Right);

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])
		->FindAnimation(L"GruntTurnLeft")->m_CompleteEvent = std::bind(&CMonster::SetLookDirection, this, Left);

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])
		->FindAnimation(L"GruntAttackRight")->m_CompleteEvent = std::bind(&CAnimator::StartPlaying, dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0]), L"GruntIdleRight");

	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])
		->FindAnimation(L"GruntAttackLeft")->m_CompleteEvent = std::bind(&CAnimator::StartPlaying, dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0]), L"GruntIdleLeft");


	dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntIdleRight");
	LookDirection = Right;
}

void CGrunt::Update()
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

	CMonster::Update();

	if (KeyMgr::Create()->key(Key::M).pressed)
	{
		int a = 0;
	}
	
	switch (MoveOrder)
	{

		case Move_Order::End:
		{
			
		}
		break;

		case Move_Order::MoveLeft:
		{
			if (LookDirection == Right)
				ActionOrder = Action_Order::TurnLeft;

			else
				ActionOrder = Action_Order::RunLeft;
			
			
			
		}
		break;

		case Move_Order::MoveRight:
		{
			if (LookDirection == Left)
				ActionOrder = Action_Order::TurnRight;

			else
				ActionOrder = Action_Order::RunRight;
			
			
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

			if (LookDirection == Right)
				ActionOrder = Action_Order::TurnLeft;

			else
				ActionOrder = Action_Order::RunLeft;
			
			


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

			if (LookDirection == Left)
				ActionOrder = Action_Order::TurnRight;

			else
				ActionOrder = Action_Order::RunRight;

			

			
		}
		break;

		case Move_Order::Stay:
		{
			if (player->GetPos().x > Pos.x + 50)
			{
				if (LookDirection == Left)
					ActionOrder = Action_Order::TurnRight;

				else
					ActionOrder = Action_Order::RunRight;
				
			}
				

			if (player->GetPos().x < Pos.x - 50)
			{
				if (LookDirection == Right)
					ActionOrder = Action_Order::TurnLeft;

				else
					ActionOrder = Action_Order::RunLeft;
				
			}
				

			
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

			if (LookDirection == Left)
				ActionOrder = Action_Order::TurnRight;

			else
				ActionOrder = Action_Order::RunRight;

			
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

			if (LookDirection == Right)
				ActionOrder = Action_Order::TurnLeft;

			else
				ActionOrder = Action_Order::RunLeft;
			
		}
		break;

	}

	//예외처리
	doublepoint diff = (player->GetPos() - Pos);              // 공격수행 조건
	if (diff.Norm() < 100 && diff.x * LookDirection >= 0)
	{
		if (LookDirection == Right)
			ActionOrder = Action_Order::AttackRight;

		else
			ActionOrder = Action_Order::AttackLeft;
	}

	if (dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->GetCurAnimation()->GetName() == L"GruntAttackRight")   // 공격은 무조건 마무리
		ActionOrder = Action_Order::AttackRight;

	if (dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->GetCurAnimation()->GetName() == L"GruntAttackLeft") 
		ActionOrder = Action_Order::AttackLeft;
		
	if (ActionOrder == Action_Order::RunLeft && OnWall) // 벽에 붙었으면 서있기
	{
		ActionOrder = Action_Order::IdleLeft;
		force.x -= 250000;
	}
	if (ActionOrder == Action_Order::RunRight && OnWall)
	{
		ActionOrder = Action_Order::IdleRight;
		force.x += 250000;
	}	
	
	//===========================================================================================
	// 액션 오더 수행
	//===========================================================================================

	switch (ActionOrder)
	{
	case Action_Order::End:
	{

	}
	break;

	case Action_Order::RunLeft:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntRunLeft");
		force.x -= 250000;
	}
	break;

	case Action_Order::RunRight:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntRunRight");
		force.x += 250000;
	}
	break;

	case Action_Order::TurnLeft:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntTurnLeft");
		
	}
	break;

	case Action_Order::TurnRight:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntTurnRight");
	}
	break;

	case Action_Order::IdleRight:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntIdleRight");
	}
	break;

	case Action_Order::IdleLeft:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntIdleLeft");
	}
	break;

	case Action_Order::AttackLeft:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntAttackLeft");
	}
	break;

	case Action_Order::AttackRight:
	{
		dynamic_cast<CAnimator*>(m_Component[(UINT)COMPONENT_TYPE::ANIMATOR][0])->StartPlaying(L"GruntAttackRight");
	}
	break;

	}

	wchar_t _Buffer[250];
	swprintf_s(_Buffer, L"Main: %d, Move: %d, Action: %d. force.x: %f",
		MainOrder,MoveOrder,ActionOrder, force.x);

	std::wstring str = {};
	str += _Buffer;
		
	SetWindowText(CCore::Create()->GetWindowData().hwnd, str.c_str());
}
