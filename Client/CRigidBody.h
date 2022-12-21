#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// 크기, 방향
	Vec2		m_vAccel;	// 가속도
	float		m_fMass;	// 질량

	Vec2		m_vVelocity; // 속도(속력(크기), 방향 둘 다 가지고 있음)

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

