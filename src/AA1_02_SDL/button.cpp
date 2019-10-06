#include "Button.h"


Button::Button()
{
}

Button::~Button()
{
}

void Button::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };

	rect = { _xPos, _yPos, tmpSurface->w, tmpSurface->h };
}
/// With three colours the clicked is included
void Button::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _clicked) };
	clickedText = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	rect = { _xPos, _yPos, tmpSurface->w, tmpSurface->h };
}

bool Button::checkClick(int mouseX, int mouseY, bool clickUp, bool clickDown, Button **pressedButton, bool invalidPress)
{
	//IF inside X
	if (mouseX >= rect.x && mouseX <= rect.x + rect.w) {
		// If inside Y
		if (mouseY >= rect.y && mouseY <= rect.y + rect.h) {
			// Then texture is hover version
			texture = hover;
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
			}
		}
	}
	else {
		texture = noHover;
		if (*pressedButton == this) {
			*pressedButton = nullptr;
		}
	}
	return false;
}


void Button::destroyMyself()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(noHover);
	SDL_DestroyTexture(clickedText);
}
