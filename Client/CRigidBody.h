#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// ũ��, ����
	Vec2		m_vAccel;	// ���ӵ�
	float		m_fMass;	// ����

	Vec2		m_vVelocity; // �ӵ�(�ӷ�(ũ��), ���� �� �� ������ ����)

	// F = M * A;
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vf) { m_vForce += _vf; }
	void SetMass(float _fMass) { m_fMass = _fMass; }

	float GetMass() { return m_fMass; }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

