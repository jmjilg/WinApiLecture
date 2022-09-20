#include "pch.h"
#include "CKeyMgr.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	//LEFT,
	VK_RIGHT,	//RIGHT,
	VK_UP,		//UP,
	VK_DOWN,	//DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	//LAST,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });		
	}
}

void CKeyMgr::update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 키가 눌려있다.
		if(GetAsyncKeyState(g_arrVK[i]) & 0X8000)
		{
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에도 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				// 이전에 눌려있지 않았다.
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			m_vecKey[i].bPrevPush = true;
		}

		// 키가 안눌려있다.
		else
		{
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				// 이전에도 안눌려있었다.
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPush = false;
		}
	}
}

