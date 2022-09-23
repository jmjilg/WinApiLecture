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
	// �� ���� ����
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
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_TOOL;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_STAGE_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_STAGE_02;
	
	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
}
