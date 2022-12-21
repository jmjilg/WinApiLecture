#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;
		// ���� 3���� ��� ��� �Ǵ°ǵ� �ܰ躰�� �����غ����� ǥ���س���

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel; // m_vForce / m_fMass �̰Ŷ� ����

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();
		// �̵� ����� �̵� �ӵ��� ���ش� �غ����� ��ǻ� �ǹ̴� ���� �׳� �ٷ� velocity * fDT �ϸ� ��. ������ �ܰ躰�� ������ ǥ���س���

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT; // vDir * fSpeed * fDT �� ����

		m_pOwner->SetPos(vPos);
	}
}
