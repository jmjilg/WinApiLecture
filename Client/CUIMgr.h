#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:


public:
	void update();

private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI 를 찾아서 반환한다.
	CUI* GetTargetedUI(CUI* _pParentUI);	

};

