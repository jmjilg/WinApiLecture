#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);  // 동시간에 true가 될 순 없음. false는 될 수 있지만

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	CUI* pTargetUI = nullptr;

	list<CUI*> queue;

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
			
		}
		else
		{
			// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	
	return pTargetUI;
}

