#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정


	return S_OK;
}

void CCore::progress()
{

}
