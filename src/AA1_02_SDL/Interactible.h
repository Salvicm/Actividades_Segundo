#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>
#include <SDL_image.h> // Imagenes, faltaría SDL_ttf.h para fuentes y SDL_mixer.h para sonido
#include <SDL_mixer.h>
#include <string>
class Interactible
{
public:
	Interactible();
	~Interactible();
	SDL_Texture *texture; // Siempre imprimir este, ir modificando a Hover o no Hover
	SDL_Texture *hover;
	SDL_Texture *noHover;
	SDL_Texture *clickedText;
	SDL_Rect rect;
	// Initialize Xpos, Ypos, Text, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
	// Initialize Xpos, Ypos, Text,color on click, color on hover, color base, temporal surface, font, renderer
	void initialize(int _xPos, int _yPos, const char *_text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface *tmpSurface, TTF_Font *font, SDL_Renderer *renderer);
	bool checkClick(int mouseX, int mouseY, bool clickUp, bool clickDown, Interactible **pressedButton, bool invalidPress);
	void destroyMyself();
	
private:
	int posX;
	int posY;
	int xSize;
	int ySize;
	std::string text;
};

