#include "pch.h"
#include "CMonster.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"

CMonster::CMonster()
	:Texture(nullptr)
{
}

CMonster::~CMonster()
{

}

void CMonster::Initialize()
{

	Scale.x = 100; Scale.y = 100;


	CreateCollider();

	std::wstring str = {};
	str += L"Monster.bmp";
	Texture = CResourceMgr::Create()->Load<CTexture>(str);
}

void CMonster::Update()
{
}

void CMonster::Render(HDC _dc)
{
	doublepoint CameraPos = CCameraMgr::Create()->CameraCoordinate(Pos);
	doublepoint CameraScale = CCameraMgr::Create()->CameraScale(Scale);

	TransparentBlt(_dc, CameraPos.x - CameraScale.x / 2, CameraPos.y - CameraScale.y / 2, CameraScale.x, CameraScale.y, Texture->GetDC(), 0, 0,
		Texture->GetWidth(), Texture->GetHeight(), RGB(1, 1, 1));


	CObject::Render(_dc);
}
