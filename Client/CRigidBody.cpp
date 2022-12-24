#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_fMaxSpeed(200.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;
		// 위의 3줄은 사실 없어도 되는건데 단계별로 분해해보고자 표시해놨음

		// 가속도
		m_vAccel = m_vForce * m_fAccel; // m_vForce / m_fMass 이거랑 같음
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * fDT;

	// 마찰력에 의한 반대방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한 검사
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}


	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);
	
	// 가속도 초기화
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// 이동 방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();
		// 이동 방향과 이동 속도를 분해는 해봤지만 사실상 의미는 없음 그냥 바로 velocity * fDT 하면 됨. 하지만 단계별로 보고자 표시해놓음

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT; // vDir * fSpeed * fDT 와 같음

		m_pOwner->SetPos(vPos);
	}
}
