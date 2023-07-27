#pragma once
class TimeMgr
{
	SINGLE(TimeMgr) 
private:
	LARGE_INTEGER mlIPrevCount;
	LARGE_INTEGER mlICurCount;
	LARGE_INTEGER mlIFrequency;
	//FPS
	//������ �� �ð� Delta Time
	double mDeltaTime;
	UINT   mCount;
	double mDeltaAcc;
	UINT   mFps;
public:
	void Init();
	void Update();
	void Render();
	double GetDelTime() {
		return mDeltaTime;
	}
};

