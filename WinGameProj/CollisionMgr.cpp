#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "CObject.h"
#include "Scene.h"
#include "Collider.h"


void CollisionMgr::Init()
{

}
void CollisionMgr::ColllisionUpdateGroup(GROUP_TYPE gltype, GROUP_TYPE grtype)
{
	shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	//�������� ��� ���� ��쿡�� ��ȯ������ ���۷��� ������ ����ؾ� ��. ����X
	const vector<shared_ptr<CObject>>& vecLeft = pCurScene->GetGroupObject(gltype);
	const vector<shared_ptr<CObject>>& vecRight = pCurScene->GetGroupObject(grtype);
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (vecRight[j]->GetCollider() == nullptr
				|| (vecLeft[i] == vecRight[j]))
			{
				continue;
			}

			shared_ptr<Collider> pLeftCol = vecLeft[i]->GetCollider(); 
			shared_ptr<Collider> pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID cID;
			cID.iLeft = pLeftCol->GetID();
			cID.iRight = pRightCol->GetID();
			map<ULONGLONG,bool>::iterator itr= mMapPrevColInfo.find(cID.ID); 
			if (itr == mMapPrevColInfo.end())
			{
				mMapPrevColInfo.insert(make_pair(cID.ID, false));
				itr = mMapPrevColInfo.find(cID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol)) 
			{
				//�� �浹�� ����
				if (itr->second)
				{
					//���� ������ ���� �浹 :�浹 ������
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						itr->second = false;
					}
					else 
					{
						pLeftCol->OnCollision(pRightCol);
					 	pRightCol->OnCollision(pLeftCol);
					}
				}
				else 
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()) 
					{
						// ù �浹 �߻�
						pLeftCol->EnterCollision(pRightCol);  
						pRightCol->EnterCollision(pLeftCol); 
						itr->second = true; 
					}

				}
			}
			else 
			{
				if (itr->second)
				{
					pLeftCol->ExitCollision(pRightCol); 
					pRightCol->ExitCollision(pLeftCol);
					itr->second = false;
					//�浹�� �ƴ� ���·� ��ȯ
				}
			}

		}
	}
}

bool CollisionMgr::IsCollision(shared_ptr<Collider> pLeftCollider, shared_ptr<Collider> pRightCollider)
{
	Vec2 leftPos = pLeftCollider->GetFinalPos();
	Vec2 leftScale = pLeftCollider->GetScale();


	Vec2 rightPos = pRightCollider->GetFinalPos();
	Vec2 rightScale = pRightCollider->GetScale();
	if (abs(rightPos.x - leftPos.x) < (rightScale.x + leftScale.x) / 2.f &&
		abs(rightPos.y - leftPos.y) < (rightScale.y + leftScale.y) / 2.f)
	{
		return true;
	}
	
	return false;
}

void CollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (mArrCheck[iRow] & (1 << iCol))
			{
				ColllisionUpdateGroup((GROUP_TYPE)iCol, (GROUP_TYPE)iRow);
			}		 
		}
	}
}

void CollisionMgr::CheckGroup(GROUP_TYPE gltype, GROUP_TYPE grtype)
{
	//������ ���׷���
	//ū �� �� ��Ʈ�� ���
	UINT iRow = (UINT)gltype;
	UINT iCol = (UINT)grtype;
	if (iCol < iRow)
	{
		iRow =(UINT) grtype;
		iCol = (UINT)gltype; 
	}

	if (mArrCheck[iRow] % (1 << iCol))
	{
		mArrCheck[iRow] &= ~(1 << iCol); 
	}
	else {
		mArrCheck[iRow] |= (1 << iCol); 
	}
	

}

void CollisionMgr::Reset()
{
	memset(mArrCheck, 0, sizeof(UINT) * ((UINT)GROUP_TYPE::END));

}

CollisionMgr::CollisionMgr():mArrCheck{}
{

}
CollisionMgr::~CollisionMgr()
{

}