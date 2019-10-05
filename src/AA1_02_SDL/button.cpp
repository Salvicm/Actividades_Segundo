#include "button.h"


button::button()
{
}

button::~button()
{
}

void button::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };

	rect = { _xPos, _yPos, tmpSurface->w, tmpSurface->h };
}
/// With three colours the clicked is included
void button::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, TTF_Font * font, SDL_Renderer * renderer)
{
	tmpSurface = { TTF_RenderText_Blended(font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(font, _text, _clicked) };
	clickedText = { SDL_CreateTextureFromSurface(renderer, tmpSurface) };
	rect = { _xPos, _yPos, tmpSurface->w, tmpSurface->h };
}

bool button::checkClick(int mouseX, int mouseY, bool clickUp, bool clickDown, button **pressedButton)
{
	//IF inside X
	if (mouseX >= rect.x && mouseX <= rect.x + rect.w) {
		// If inside Y
		if (mouseY >= rect.y && mouseY <= rect.y + rect.h) {
			// Then texture is hover version
			texture = hover;
			// If you click
 			if (clickDown == true && clickUp == false && (*pressedButton == nullptr || *pressedButton == this)) {
				if (clickedText != nullptr) {
					texture = clickedText;
				}
				clickingMe = true;
				*pressedButton = this;
			}
			// If you stop clicking inside the button
			else if (clickDown == false && clickUp == true && *pressedButton == this) {
				*pressedButton = nullptr;
				return true;
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


void button::destroyMyself()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(noHover);
	SDL_DestroyTexture(clickedText);
}
