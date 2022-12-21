#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"

CPlayer::CPlayer()
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

	CreateAnimator();	
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -200.f));
	}

	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)vPos.x - (float)(iWidth / 2)
	//	, (int)vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	//TransparentBlt(_dc
	//	, (int)vPos.x - (float)(iWidth / 2)
	//	, (int)vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 255, 255));

	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);


	// 알파블렌드 테스트 코드(비행기 스프라이트)
	/*CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Player_A.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		, pTex->GetDC()
		, 0, 0
		, int(width), int(height)
		, bf);*/
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER); // 앞으로 생성될 모든 종류의 오브젝트를 커버할 수 있어야함
}
