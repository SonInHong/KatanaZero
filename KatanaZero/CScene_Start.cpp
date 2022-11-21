#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CMonster.h"
#include "CColliderMgr.h"
#include "CCameraMgr.h"
#include "CCore.h"
#include "CResourceMgr.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CFloor.h"
#include "CTopFloor.h"
#include "CStair.h"
#include "CWall.h"
#include "CFloorCeiling.h"
#include "CCursor.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	//CCore::Create()->SetMenuBar(true);
	

	//ShowWindow(CCore::Create()->GetToolWindowData().hwnd, SW_NORMAL);
	//UpdateWindow(CCore::Create()->GetToolWindowData().hwnd);

	//카메라리셋
	CCameraMgr::Create()->Reset();
		
	//Map 추가
	CMap* _pMap = new CMap;
	_pMap->Load(L"Map.tile");
	AddObject(_pMap, GROUP_TYPE::MAP);

	//커서 추가
	CCursor* _pCursor = new CCursor;
	AddObject(_pCursor, GROUP_TYPE::CURSOR);
	ShowCursor(false);

	//Player 추가
	CPlayer* _pObj = new CPlayer;

	_pObj->SetPos(doublepoint{ 600,500 });
	_pObj->SetScale(doublepoint{ 15,30 });
	_pObj->SetResize(doublepoint{ 2,2 });

	AddObject(_pObj, GROUP_TYPE::PLAYER);

	//Monster 추가
	CMonster* _pMon = new CMonster;
	_pMon->SetPos(doublepoint{ 600,100 });

	//AddObject(_pMon, GROUP_TYPE::MONSTER);

	//Floor 추가
	
	CStair* _pStair = new CStair;
	_pStair->SetScale(doublepoint{ 300, 300 });
	_pStair->SetPos(doublepoint{ 905, 440 });
	_pStair->SetDir(Right);
	AddObject(_pStair, GROUP_TYPE::FLOOR);

	_pStair = new CStair;
	_pStair->SetScale(doublepoint{ 60, 60 });
	_pStair->SetPos(doublepoint{ 510, 320 });
	_pStair->SetDir(Left);
	AddObject(_pStair, GROUP_TYPE::FLOOR);

	CFloor* _pFloor = new CFloor;
	_pFloor->SetScale(doublepoint{ 800, 35 });
	_pFloor->SetPos(doublepoint{ 370, 595 });
	AddObject(_pFloor, GROUP_TYPE::FLOOR);

	_pFloor = new CFloor;
	_pFloor->SetScale(doublepoint{ 200, 60 });
	_pFloor->SetPos(doublepoint{ 1156, 319 });
	AddObject(_pFloor, GROUP_TYPE::FLOOR);
		
	_pFloor = new CFloor;
	_pFloor->SetScale(doublepoint{ 480, 60 });
	_pFloor->SetPos(doublepoint{ 240, 319 });
	//AddObject(_pFloor, GROUP_TYPE::FLOOR);

	_pFloor = new CFloor;
	_pFloor->SetScale(doublepoint{ 320, 60 });
	_pFloor->SetPos(doublepoint{ 320, 319 });
	AddObject(_pFloor, GROUP_TYPE::FLOOR);

	CTopFloor* _pTopFloor = new CTopFloor;  
	_pTopFloor->SetScale(doublepoint{ 575, 60 });
	_pTopFloor->SetPos(doublepoint{ 767.5, 319 });
	AddObject(_pTopFloor, GROUP_TYPE::FLOOR);

	_pTopFloor = new CTopFloor;
	_pTopFloor->SetScale(doublepoint{ 200, 35 });
	_pTopFloor->SetPos(doublepoint{ 75, 117.5 });
	AddObject(_pTopFloor, GROUP_TYPE::FLOOR);

	CFloorCeiling* _pCeiling = new CFloorCeiling;
	_pCeiling->SetScale(doublepoint{ 60, 10 });
	_pCeiling->SetPos(doublepoint{ 480, 220 });
	//AddObject(_pCeiling, GROUP_TYPE::FLOOR);


	
	CWall* _pWall = new CWall;
	_pWall->SetScale(doublepoint{ 35,700 });
	_pWall->SetPos(doublepoint{ 17,300 });
	AddObject(_pWall, GROUP_TYPE::FLOOR);

	_pWall = new CWall;
	_pWall->SetScale(doublepoint{ 35,400 });
	_pWall->SetPos(doublepoint{ 157,300 });
	AddObject(_pWall, GROUP_TYPE::FLOOR);

	_pWall = new CWall;
	_pWall->SetScale(doublepoint{ 35,700 });
	_pWall->SetPos(doublepoint{ 1260,400 });
	AddObject(_pWall, GROUP_TYPE::FLOOR);

	_pWall = new CWall;
	_pWall->SetScale(doublepoint{ 60,225 });
	_pWall->SetPos(doublepoint{ 480,112.5 });
	AddObject(_pWall, GROUP_TYPE::FLOOR);

	

	

	

	//UI 추가
	/*CPanelUI* _pUI = new CPanelUI;
	CButtonUI* _cUI = new CButtonUI;
	_pUI->setOffset(doublepoint{ 700, 0 });
	_pUI->SetScale(doublepoint{ 600, 300 });
	_pUI->setWindowData(CCore::Create()->GetWindowData());
	_cUI->setOffset(doublepoint{ 0, 0 });
	_cUI->SetScale(doublepoint{ 100, 50 });

	_pUI->setChild(_cUI);

	AddObject(_pUI, GROUP_TYPE::UI);*/

	

	

	//Obj 초기화
	for (int i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Initialize();
		}
	}

	//충돌 그룹 지정
	CColliderMgr::Create()->CheckGroup(GROUP_TYPE::PLAYER_PROJECTILE, GROUP_TYPE::MONSTER);
	CColliderMgr::Create()->CheckGroup(GROUP_TYPE::PLAYER_PROJECTILE, GROUP_TYPE::FLOOR);
	CColliderMgr::Create()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FLOOR);
}

void CScene_Start::Exit()
{
	//충돌 그룹 해제
	CColliderMgr::Create()->Reset();

	//커서 다시 보이게
	ShowCursor(true);
}

void CScene_Start::Update()
{
	CScene::Update();
}

void CScene_Start::Render(HDC _dc)
{
	CScene::Render(_dc);

}
