#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;		// ��� Animation
	CAnimation*					m_pCurAnim;		// ���� ������� Animation
	CObject*					m_pOwner;		// Animator ���� ������Ʈ


public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFreamCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play();

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};
