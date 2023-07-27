#pragma once
#include "Scene.h"
class Scene_Tool :public Scene
{
private:
public:
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
public:
	Scene_Tool();
	~Scene_Tool();
};

