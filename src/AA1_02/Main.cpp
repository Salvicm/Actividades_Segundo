#include "Utils.h"
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h> // Imagenes, faltaría SDL_ttf.h para fuentes y SDL_mixer.h para sonido
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image	
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG }; //Esto es para indicar los formatos que vamos a cargar, en esta librería hay jpg, png, TIF y WEBP
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_TTF"; //TAmbien se püede poner == -1
	
	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3};
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_mixer init";

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
		// Cursor
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect playerRect{ 0,0,175,96 };


	//-->Animated Sprite ---

	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 80) };
	if (font == nullptr)
		throw "No es pot inicialitzar the TTF_FONT";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "UWU", SDL_Color{ 255,150,0, 255 }) };
	if (tmpSurf == nullptr) 
		throw "No es pot crear the SDL text surface";
	SDL_Texture *textHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font, "UWU", SDL_Color{ 0,150,0, 255 }) };
	if (tmpSurf == nullptr)
		throw "No es pot crear the SDL text surface";
	SDL_Texture *textNoHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Texture *textTexture = textHover;
	SDL_Rect textRect{ 100, 50, tmpSurf->w, tmpSurf->h };
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);
	vector2 mousePos; 

	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0) 
		throw "Unable to initialize SDL_mixer audio systems";
	
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // Üsar porcentajes, nada de nümeros completos, por següridad de qüe cambie la librería
	Mix_PlayMusic(soundtrack, -1); // Nümero de veces qüe se reprodüce. -1 es ün bücle infinito

	// --- GAME LOOP ---
	SDL_Event event; // Tipo Strüct, maneja ün evento
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) { // Fünción SDL contiene la cola de todos los eventos, estrüctüra de datos( Pilla siempre el primer elemento y lo elimina de la cola)
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;

				break;
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN: // SOLDADO CAIDO, REPITO: SOLDADO CAÍDO
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += ((mousePos.x - playerRect.w/2) - playerRect.x) / 10;
		playerRect.y += ((mousePos.y - playerRect.h/2) - playerRect.y) / 10;
		if (mousePos.x >= textRect.x && mousePos.x <= textRect.x + textRect.w) { 
			if (mousePos.y >= textRect.y && mousePos.y <= textRect.y + textRect.h) {
				textTexture = textHover;
			}
			else {
				textTexture = textNoHover;
			}
		}
		else {
			textTexture = textNoHover;
		}
		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);
		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	Mix_CloseAudio();
	// --- QUIT ---
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

	return 0;
}