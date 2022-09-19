#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency; // 1�ʴ� �����ִ� ī��Ʈ��

	double			m_dDT; // ������ ������ �ð���, �����Ӱ� ������ ������ �ɸ� �ð�
	double			m_dAcc;	// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS; // �ʴ� ȣ�� Ƚ��

	// FPS
	// 1 �����Ӵ� �ð� (Delta Time)
public:
	void Init();
	void update();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

