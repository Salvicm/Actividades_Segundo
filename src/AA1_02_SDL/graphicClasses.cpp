#include "graphicClasses.h"
#pragma region Window
Window::Window()
{
	throw "Uninitialized window";
}

Window::Window(const char * _path, int _width, int _height)
{
	window = { SDL_CreateWindow(_path, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN) };
	if (window == nullptr) {
		throw "Unable to create window";
	}
}

Window::~Window()
{
}
#pragma endregion
#pragma region Renderer
Renderer::Renderer()
{
	throw "Uninitialized renderer";
}

Renderer::Renderer(Window *_window)
{
	renderer = { SDL_CreateRenderer( _window->window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) {
		throw "Unable to create renderer";
	}
}

Renderer::~Renderer()
{
}
#pragma endregion
#pragma region Textures
Texture::Texture()
{
}

Texture::Texture(Renderer *m_renderer, const char *_path, int _posX, int _posY, int _xSize, int _ySize )
{ 
	texture = { IMG_LoadTexture(m_renderer->renderer, _path) };
	if (texture == nullptr) throw "Error: Texture init";
	libRect = { _posX, _posY, _xSize, _ySize};
	rect = { _posX, _posY, _xSize, _ySize };
}


Texture::~Texture()
{
}

void Texture::updateTexture(Renderer * m_renderer, const char * _path, int _posX, int _posY, int _xSize, int _ySize)
{
	texture = { IMG_LoadTexture(m_renderer->renderer, _path) };
	if (texture == nullptr) throw "Error: Texture init";
	libRect = { _posX, _posY, _xSize, _ySize};
	rect = { _posX, _posY, _xSize, _ySize };
}

void Texture::updateRect(int newXValue, int newYValue)
{
	rect.x = libRect.x = newXValue;
	rect.y = libRect.y = newYValue;
}

void Texture::updateRect(int newXValue, int newYValue, int newWValue, int newHValue)
{
	rect.h = libRect.h = newHValue;
	rect.w = libRect.w = newWValue;
	rect.x = libRect.x = newXValue;
	rect.y = libRect.y = newYValue;
}

void Texture::destroy()
{
	SDL_DestroyTexture(texture);

}
#pragma endregion
#pragma region Animated Texture
AnimatedTexture::AnimatedTexture()
{
}

AnimatedTexture::AnimatedTexture(Renderer * m_renderer, const char * _path, int _posX, int _posY, int numColumns, int numRows, float modSize)
{
	texture = { IMG_LoadTexture(m_renderer->renderer, _path) };
	if (texture == nullptr) throw "Error: Texture init";
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / numColumns;
	frameHeight = textHeight / numRows;
	updateRect(0, 0, frameHeight, frameWidth);
	updatePosRect(_posX, _posY, frameHeight*modSize, frameWidth*modSize);
	frameTime = 0;

}

AnimatedTexture::~AnimatedTexture()
{
}

void AnimatedTexture::updateTexture(Renderer * m_renderer, const char * _path, int _posX, int _posY, int numColumns, int numRows, float modSize)
{
	texture = { IMG_LoadTexture(m_renderer->renderer, _path) };
	if (texture == nullptr) throw "Error: Texture init";
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / numColumns;
	frameHeight = textWidth / numRows;
	updateRect(0, 0, frameHeight, frameWidth);
	updatePosRect(_posX, _posY, frameHeight*modSize, frameWidth*modSize);
	frameTime = 0;
}

void AnimatedTexture::updateRect(int newXValue, int newYValue)
{

	rect.x = libRect.x = newXValue;
	rect.y = libRect.y = newYValue;
}

void AnimatedTexture::updateRect(int newXValue, int newYValue, int newHValue, int newWValue)
{
	rect.h = libRect.h = newHValue;
	rect.w = libRect.w = newWValue;
	rect.x = libRect.x = newXValue;
	rect.y = libRect.y = newYValue;
}

void AnimatedTexture::updatePosRect(int newXValue, int newYValue)
{
	pos.x = libPos.x = newXValue;
	pos.y = libPos.y = newYValue;
}

void AnimatedTexture::updatePosRect(int newXValue, int newYValue, int newHValue, int newWValue)
{
	pos.h = libPos.h = newHValue;
	pos.w = libPos.w = newWValue;
	pos.x = libPos.x = newXValue;
	pos.y = libPos.y = newYValue;
}

void AnimatedTexture::updateAnimation()
{
	frameTime++;
	if (FPS / frameTime <= 9) {
		frameTime = 0;
		updateRect(rect.x + frameWidth, rect.y);
		if (rect.x >= textWidth)
			updateRect(0, rect.y);
	}
}

void AnimatedTexture::destroy()
{
	SDL_DestroyTexture(texture);
}

#pragma endregion
#pragma region Audio
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
#pragma endregion
#pragma region Surface
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
#pragma endregion
#pragma region Font
Font::Font()
{
	throw "Unitialized font";
}

Font::Font(const char * _path, int size)
{

	path = _path;
	font = { TTF_OpenFont(path, size) };
	if (font == nullptr)
		throw "No es pot inicialitzar the TTF_FONT";
}

Font::~Font()
{
}

void Font::changeFontSize(int size) {
	font = { TTF_OpenFont(path, size) };
	if (font == nullptr)
		throw "No es pot inicialitzar the TTF_FONT";
}
void Font::close()
{
	if (font == nullptr)
		throw "No es pot inicialitzar the TTF_FONT";
	TTF_CloseFont(font);
}
#pragma endregion
#pragma region Interactible

Interactible::Interactible()
{
}

Interactible::~Interactible()
{
}

void Interactible::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, Font * _font, Renderer * renderer)
{
	name = _text;
	tmpSurface = { TTF_RenderText_Blended(_font->font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer->renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(_font->font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer->renderer, tmpSurface) };
	rect = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };

	xSize = rect.w;
	ySize = rect.h;
	position.x = _xPos;
	position.y = _yPos;
}
/// With three colours the clicked is included
void Interactible::initialize(int _xPos, int _yPos, const char * _text, SDL_Color _clicked, SDL_Color _hover, SDL_Color _noHover, SDL_Surface * tmpSurface, Font * _font, Renderer * renderer)
{
	name = _text;
	tmpSurface = { TTF_RenderText_Blended(_font->font, _text, _hover) };
	texture = hover = { SDL_CreateTextureFromSurface(renderer->renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(_font->font, _text, _noHover) };
	noHover = { SDL_CreateTextureFromSurface(renderer->renderer, tmpSurface) };
	tmpSurface = { TTF_RenderText_Blended(_font->font, _text, _clicked) };
	clickedText = { SDL_CreateTextureFromSurface(renderer->renderer, tmpSurface) };
	rect = { _xPos - tmpSurface->w / 2, _yPos - tmpSurface->h / 2, tmpSurface->w, tmpSurface->h };

	xSize = rect.w;
	ySize = rect.h;
	position.x = _xPos;
	position.y = _yPos;
}

bool Interactible::checkClick(mouseController *mouse, bool invalidPress)
{
	texture = hover;
	this->lerpSize();
	if (hovering == true) {
		if (invalidPress == false) {
			if (mouse->pressDown == true && mouse->pressUp == false && (mouse->pressedButton == NO_BUTTON || mouse->pressedButton == name)) {
				if (clickedText != nullptr) {
					texture = clickedText;
				}
				mouse->pressedButton = name;
			}
			// If you stop clicking inside the Button
			else if (mouse->pressDown == false && mouse->pressUp == true && mouse->pressedButton == name) {
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
	int h = Utils::lerp(lerpSizeController, ySize, ySize*1.2f);
	int w = Utils::lerp(lerpSizeController, xSize, xSize*1.2f);
	int x = position.x - rect.w / 2;
	int y = position.y - rect.h / 2;
	updateRect(x, y, w, h);
}

void Interactible::updateRect(int newXValue, int newYValue)
{
	rect.x = rectLib.x = newXValue;
	rect.y = rectLib.y = newYValue;
}

void Interactible::updateRect(int newXValue, int newYValue, int newWValue, int newHValue)
{
	rect.h = rectLib.h = newHValue;
	rect.w = rectLib.w = newWValue;
	rect.x = rectLib.x = newXValue;
	rect.y = rectLib.y = newYValue;
}

void Interactible::normalizeSize(mouseController *mouse)
{
	if (mouse->pressedButton == name) {
		mouse->pressedButton = NO_BUTTON;
	}
	lerpSizeController = 0;
	lerpController = true;
	texture = noHover;
	updateRect(position.x - rect.w / 2, position.y - rect.h / 2, xSize, ySize);
}
#pragma endregion

