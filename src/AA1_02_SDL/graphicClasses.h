#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>
#include <SDL_image.h> // Imagenes, faltaría SDL_ttf.h para fuentes y SDL_mixer.h para sonido
#include <SDL_mixer.h>
#include "Utils.h"

class Window {
public:
	Window();
	Window(const char *_path, int _width, int _height);
	~Window();
	SDL_Window *window;
	 
	
};

class Renderer {
public:
	Renderer();
	Renderer(Window *_window);
	~Renderer();
	SDL_Renderer *renderer;
};

class Texture
{
public:
	Texture();
	Texture(Renderer *m_renderer, const char *_path, int _posX, int _posY, int _xSize, int _ySize);
	~Texture();
	SDL_Texture *texture;
	SDL_Rect libRect;
	rect_util rect;
	void updateTexture(Renderer *m_renderer, const char *_path, int _posX, int _posY, int _xSize, int _ySize);
	void updateRect(int newXValue, int newYValue);
	void updateRect(int newXValue, int newYValue, int newHValue, int newWValue );
	void destroy();
};

class Audio {
public:
	Audio();
	Audio(const char* _path);
	~Audio();
	void play(int _numberOfTimes);
	Mix_Music *track;

};
class Surface {
public:
	Surface();
	~Surface();
	void free();
	SDL_Surface *surface;
};

class Font {
public:
	Font();
	Font(const char *_path, int size);
	~Font();
	void close();
	void changeFontSize(int size);
	TTF_Font *font;
private:
	const char *path;
};

class Interactible
{
public:
	Interactible();
	~Interactible();
	std::string name;
	SDL_Texture *texture; // Siempre imprimir este, ir modificando a Hover o no Hover
	rect_util rect;
	SDL_Rect rectLib;
	// Initialize Xpos, Ypos, Text, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, Font *_font, Renderer *renderer);
	// Initialize Xpos, Ypos, Text,color on click, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, Font *_font, Renderer *renderer);
	bool checkClick(mouseController *mouse, bool invalidPress);
	void destroyMyself();
	bool hovering = false;
	void normalizeSize(mouseController *mouse);
	
private:
	vec2 position;
	int xSize;
	int ySize;
	float lerpSizeController = 0.1f;
	bool lerpController = true;
	void lerpSize();
	void updateRect(int newXValue, int newYValue);
	void updateRect(int newXValue, int newYValue, int newHValue, int newWValue); SDL_Texture *hover;
	SDL_Texture *noHover;
	SDL_Texture *clickedText;
	std::string text;
};


// This must be here, it needs a mouseController and an Interactible, we can't have cyclic includes
static bool checkButtonColision(mouseController *mousePos, Interactible *_button) {
	if (mousePos->position.x >= _button->rect.x && mousePos->position.x <= _button->rect.x + _button->rect.w) {
		// If mousePos Y
		if (mousePos->position.y >= _button->rect.y && mousePos->position.y <= _button->rect.y + _button->rect.h) {
			_button->hovering = true;
			return true;
		}
		else {
			_button->hovering = false;
			_button->normalizeSize(mousePos);
		}
	}
	else {
		_button->hovering = false;
		_button->normalizeSize(mousePos);
	}
	return false;
}