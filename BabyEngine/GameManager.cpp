#include "GameManager.h"
#include "MathHelper.h"

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance() {
	if (sInstance == NULL)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release() {
	delete sInstance;
	sInstance = NULL;

}

GameManager::GameManager() {
	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();


	mTimer = Timer::Instance();

	
	mTex = new Texture("Welcome!", "Sans.TTF", 72, {255, 0, 0});
	
	mTex->Pos(Vector2(400, 300));
	
}

GameManager::~GameManager() {


	AssetManager::Release();
	mAssetManager = NULL;

	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputManager = NULL;

	Timer::Release();
	mTimer = NULL;

	delete mTex; 
	mTex = NULL;

	AudioManager::Release();
	mAudioManager = NULL;


}

void GameManager::EarlyUpdate() {
	

	mInputManager->Update();
	mTimer->Reset();

}

void GameManager::Update() {
	


	if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
		if (!Mix_PlayingMusic())
			mAudioManager->PlayMusic("AD.wav", -1);
		else mAudioManager->ResumeMusic();
	}
		
	

	if (mInputManager->KeyReleased(SDL_SCANCODE_W)) {

		mAudioManager->PauseMusic();
		
	}


	if (mInputManager->MouseButtonDown(InputManager::left)) {
		printf("left mouse pressed: (%f, %f) \n", mInputManager->MousePos().x, mInputManager->MousePos().y);
	}
	if (mInputManager->MouseButtonReleased(InputManager::left)) {
		printf("left mouse released: (%f, %f)\n", mInputManager->MousePos().x, mInputManager->MousePos().y);
	}


	


	//mTex->Rotate(20 * mTimer->DeltaTime());

	mTex->Update();



}

void GameManager::lateUpdate() {

	mInputManager->UpdatePrevInput();
	

}

void GameManager::Render() {

	mGraphics->ClearBackBuffer();

	mTex->Render();
	

	mGraphics->Render();

}
void GameManager::Run() {
	while (!mQuit) {
		mTimer->Update();
		while (SDL_PollEvent(&mEvents) != 0) {
			if (mEvents.type == SDL_QUIT) {
				mQuit = true;
			}
			
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

			EarlyUpdate();
			Update();
			lateUpdate();
			Render();
		}
		
	}
}

void GameManager::ScaleEffect() {

	srand(mTimer->DeltaTime()); //Random seed
	int random = rand() % 3;

	if (random == 0) {
		mScaleAmt += VEC2_ONE * 0.5f * mTimer->DeltaTime();
		mTex->Scale(mScaleAmt);
	}
	else if (random >= 1) {
		mScaleAmt -= VEC2_ONE * (1 / 0.5f) * mTimer->DeltaTime();
		mTex->Scale(mScaleAmt);
		
	}
	


	
	
	
}