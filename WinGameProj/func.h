#pragma once
class CObject;
void CreateObject(shared_ptr<CObject> pObj,GROUP_TYPE gtype); 
void DeleteObject(shared_ptr<CObject> pObj); 
void ChangeScene(SCENE_TYPE sType);

template <typename T>
void SafeDeleteVec(vector<T>& vec)
{
	for (auto itr = vec.begin(); itr != vec.end(); itr++)
	{
		if(*itr!=nullptr)
			*itr = nullptr;
	}
	vec.clear(); //VEC SIZE SET 0
}


template <typename T,typename T2>
void SafeDeleteMap(map<T,T2>& map)
{
	for (auto itr = map.begin(); itr != map.end(); itr++)
	{
		if (nullptr != itr->second)
		{
			itr->second = nullptr;
		}
	}
	map.clear();
	
}