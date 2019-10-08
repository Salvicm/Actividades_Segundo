#pragma once
#include "graphLibUtils.h"
class Texture
{
public:
	Texture();
	Texture(SDL_Renderer **m_renderer, const char *_path, int _posX, int _posY, int _xSize, int _ySize);
	~Texture();
	SDL_Texture *texture;
	SDL_Rect rect;

	void destroy();
private:
};

class Audio {
public:
	Audio();
	Audio(const char* _path);
	~Audio();
	void play(int _numberOfTimes);
	Mix_Music *track;

};

