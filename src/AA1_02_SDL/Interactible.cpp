#include "Interactible.h"


Interactible::Interactible()
{
}

Interactible::~Interactible()
{
}

void Interactible::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	rect = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };
	xSize = rect.w;
	ySize = rect.h;
	posX = _xPos;
	posY = _yPos;
 }
/// With three colours the clicked is included
void Interactible::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _clicked) };
	clickedText = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	rect = { _xPos - tmpSurface->w/2, _yPos-tmpSurface->h/2, tmpSurface->w, tmpSurface->h };
	xSize = rect.w;
	ySize = rect.h;
	posX = _xPos;
	posY = _yPos;
}

bool Interactible::checkClick(int mouseX, int mouseY, bool clickUp, bool clickDown, Interactible **pressedButton, bool invalidPress)
{
	//IF inside X
	if (mouseX >= rect.x && mouseX <= rect.x + rect.w) {
		// If inside Y
		if (mouseY >= rect.y && mouseY <= rect.y + rect.h) {
			// Then texture is hover version
			texture = hover;
			this->lerpSize();
			// If you click
			if (invalidPress ==  false) {
				if (clickDown == true && clickUp == false && (*pressedButton == nullptr || *pressedButton == this)) {
					if (clickedText != nullptr) {
						texture = clickedText;
					
					}
					*pressedButton = this;
				}
				// If you stop clicking inside the Button
				else if (clickDown == false && clickUp == true && *pressedButton == this) {
					*pressedButton = nullptr;
					return true;
				}
			}
		}
		//Needed for the case where you stop being on Y but not on X
		else {
			texture = noHover;
			if (*pressedButton == this) {
				*pressedButton = nullptr;
				lerpSizeController = 0;
				lerpController = true;
			}
				rect.h = ySize;
				rect.w = xSize;
		}
	}
	else {
		texture = noHover;
		lerpSizeController = 0;
		lerpController = true;
		rect.h = ySize;
		rect.w = xSize;
		if (*pressedButton == this) {
			*pressedButton = nullptr;
		}
	}
	return false;
}


void Interactible::destroyMyself()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(noHover);
	SDL_DestroyTexture(clickedText);
}

void Interactible::lerpSize()
{
#pragma region lerp
	if (lerpSizeController <= 0.0f) {
		lerpController = true;
	}
	else if (lerpSizeController >= 1.0f) {
		lerpController = false;
	}
	if (lerpController == false) {
		lerpSizeController -= 0.05f;
	}
	else if (lerpController == true) {
		lerpSizeController += 0.05f;
	}
#pragma endregion
	rect.w = (xSize * (1.0 - lerpSizeController)) + (xSize*1.2 * lerpSizeController);
	rect.h = (ySize * (1.0 - lerpSizeController)) + (ySize*1.2 * lerpSizeController);
	rect.x = posX - rect.w / 2;
	rect.y = posY - rect.h / 2;
}
