#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"


class Texture: public GameEntity {

protected:
	SDL_Texture* mTex;

	
	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;

	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;


public:
	Texture(std::string fileName);

	Texture(std::string filename, int x, int y, int w, int h);

	Texture(std::string text, std::string fontpath, int size, SDL_Color color);
	~Texture();

	virtual void Render();




};



#endif
