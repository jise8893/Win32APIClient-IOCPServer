#pragma once
#include "Scene.h"
class CSceneStart : public Scene
{
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
public:
	CSceneStart();
	~CSceneStart();
};

