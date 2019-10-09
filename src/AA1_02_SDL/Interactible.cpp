#include "Interactible.h"


Interactible::Interactible()
{
}

Interactible::~Interactible()
{
}

void Interactible::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	name = _text;
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	rectsdl = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };
	rect = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };

	xSize = rectsdl.w;
	ySize = rectsdl.h;
	position.x = _xPos;
	position.y = _yPos;
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
	rectsdl = { _xPos - tmpSurface->w/2, _yPos-tmpSurface->h/2, tmpSurface->w, tmpSurface->h };
	rect = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };

	xSize = rectsdl.w;
	ySize = rectsdl.h;
	position.x = _xPos;
	position.y = _yPos;
}

bool Interactible::checkClick(mouseController *mouse, bool invalidPress)
{
		texture = hover;
		this->lerpSize();
	if (hovering == true) {
		if (invalidPress == false) {
			if (mouse->pressDown == true && mouse->pressUp == false && (mouse->pressedButton == NO_BUTTON || mouse->pressedButton == this->name)) {
				if (clickedText != nullptr) {
					texture = clickedText;
				}
				mouse->pressedButton = this->name;
			}
			// If you stop clicking inside the Button
			else if (mouse->pressDown == false && mouse->pressUp == true && mouse->pressedButton == this->name) {
				mouse->pressedButton = NO_BUTTON;
				return true;
			}
		}
	}
		//Needed for the case where you stop being on Y but not on X
	else {
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
	rectsdl.w = (xSize * (1.0 - lerpSizeController)) + (xSize*1.2 * lerpSizeController);
	rectsdl.h = (ySize * (1.0 - lerpSizeController)) + (ySize*1.2 * lerpSizeController);
	rectsdl.x = position.x - rectsdl.w / 2;
	rectsdl.y = position.y - rectsdl.h / 2;
}

void Interactible::normalizeSize(mouseController *mouse)
{
	if (mouse->pressedButton == this->name) {
		mouse->pressedButton = NO_BUTTON;
		lerpSizeController = 0;
		lerpController = true;
	}
	texture = noHover;
	rectsdl.h = ySize;
	rectsdl.w = xSize;
	rectsdl.x = position.x - rectsdl.w / 2;
	rectsdl.y = position.y - rectsdl.h / 2;
}
