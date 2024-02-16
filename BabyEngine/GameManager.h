#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H


#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Timer.h"
class GameManager {

private:
	static GameManager* sInstance;

	const int FRAME_RATE = 120;

	bool mQuit;
	
	Graphics* mGraphics;


	Timer* mTimer;
	SDL_Event mEvents;

	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Texture* mTex;

	Vector2 mScaleAmt = { 1, 1 };

public:

	static GameManager* Instance();
	static void Release();

	void Run();

	void ScaleEffect();

private:
	GameManager();
	~GameManager();


	void EarlyUpdate();
	void Update();
	void lateUpdate();

	void Render();
};




#endif
