#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_TOOL;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_STAGE_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_STAGE_02;
	
	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	//m_pCurScene->Enter(); 잘못 쓴 코드
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
