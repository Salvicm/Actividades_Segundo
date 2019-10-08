#pragma once
#include "graphLibUtils.h"
#include "Utils.h"
#include <string>

class Interactible
{
public:
	Interactible();
	~Interactible();
	SDL_Texture *texture; // Siempre imprimir este, ir modificando a Hover o no Hover
	SDL_Rect rectsdl;
	rect_util rect;
	// Initialize Xpos, Ypos, Text, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
	// Initialize Xpos, Ypos, Text,color on click, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
	bool checkClick(bool clickUp, bool clickDown, Interactible **pressedButton, bool invalidPress);
	void destroyMyself();
	bool hovering = false;
private:
	vec2 position;
	int xSize;
	int ySize;
	float lerpSizeController = 0.1f;
	bool lerpController = true;
	void lerpSize();
	void normalizeSize();
	SDL_Texture *hover;
	SDL_Texture *noHover;
	SDL_Texture *clickedText;
	std::string text;
};

struct mouseController {
	vec2 position;
	bool press;
	Interactible *pressingButton = nullptr;
	mouseController() : position{0, 0}, press(false) {};
};

