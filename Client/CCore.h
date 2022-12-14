#pragma once
#include "define.h"
#include <Windows.h>

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	POINT		m_ptResolution; // 메인 윈도우 해상도
	HDC			m_hDC;			// 메인 윈도우에 Draw할 DC

	CTexture*	m_pMemTex;		// 백버퍼 텍스쳐

	// 자주 사용하는 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU	m_hMenu; // Tool Scene 에서만 사용



public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};