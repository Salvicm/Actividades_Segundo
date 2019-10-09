#pragma once
#include "graphLibUtils.h"

class Interactible
{
public:
	Interactible();
	~Interactible();
	std::string name;
	SDL_Texture *texture; // Siempre imprimir este, ir modificando a Hover o no Hover
	SDL_Rect rectsdl;
	rect_util rect;
	// Initialize Xpos, Ypos, Text, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
	// Initialize Xpos, Ypos, Text,color on click, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
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
	SDL_Texture *hover;
	SDL_Texture *noHover;
	SDL_Texture *clickedText;
	std::string text;
};




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