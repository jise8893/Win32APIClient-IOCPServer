#pragma once
#define SINGLE(type) public:\
						static type* GetInst(){\
							static type mgr;\
							 return &mgr;\
						}\
					private :\
						 type();\
						 ~type();


#define KEY_CHECK(key,state) CKeyMgr::GetInst()->GetKeyState(key)==state
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos(); 
#define PI 3.1415926535f

#define TILE_SIZE 64
enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PLAYER,
	MISSILE,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,
	OTHER_PLAYER,
	END=32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE01,
	STAGE02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};