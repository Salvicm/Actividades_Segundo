#include "graphicClasses.h"



Texture::Texture()
{
}

Texture::Texture(SDL_Renderer **m_renderer, const char *_path, int _posX, int _posY, int _xSize, int _ySize )
{ 
	texture = { IMG_LoadTexture(*m_renderer, _path) };
	if (texture == nullptr) throw "Error: Texture init";
	rectsdl = { _posX, _posY, _xSize, _ySize};
	rect = { _posX, _posY, _xSize, _ySize };
}


Texture::~Texture()
{
}

void Texture::destroy()
{
	SDL_DestroyTexture(texture);

}

Audio::Audio()
{
}

Audio::Audio(const char * _path)
{
	 track = { Mix_LoadMUS(_path) };
	if (!track) throw "Unable to load the Mix_Music soundtrack";
}

Audio::~Audio()
{
}

void Audio::play(int _numberOfTimes)
{
	Mix_PlayMusic(track, _numberOfTimes); // Nümero de veces qüe se reprodüce. -1 es ün bücle infinito

}

Surface::Surface()
{
}

Surface::~Surface()
{
}

void Surface::free()
{
	SDL_FreeSurface(surface);
}
