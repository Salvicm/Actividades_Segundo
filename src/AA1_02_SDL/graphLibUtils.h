#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>
#include <SDL_image.h> // Imagenes, faltaría SDL_ttf.h para fuentes y SDL_mixer.h para sonido
#include <SDL_mixer.h>
#include "Constantes.h"

namespace graphicHelper {
	// Tienen que ser estáticas al no formar parte de un objeto?
	static void initLibrary() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			throw "Unable to initialize SDL";
		}
		if (TTF_Init() != 0) {
			throw
				"Unable to initialize TTF";
		}
		const Uint8 imgFlags{ IMG_INIT_JPG | IMG_INIT_PNG };
		if (!IMG_Init(imgFlags) & imgFlags) {
			throw "Unable to initialize IMG";
		}
		const Uint8 mixFlags{ MIX_INIT_MP3 };
		if (!(Mix_Init(mixFlags) & mixFlags)) {
			throw "Error: SDL_mixer init";
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
			throw "Unable to initialize SDL_mixer audio systems";
		Mix_VolumeMusic(MIX_MAX_VOLUME  * 0.75); // Üsar porcentajes, nada de nümeros completos, por següridad de qüe cambie la librería
	}

	static void startWindowAndRender(SDL_Window **m_window, SDL_Renderer **m_renderer) {
		*m_window = { SDL_CreateWindow("AA1_02_pt3...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
		if (m_window == nullptr) {
			throw "Unable to create window";
		}
		*m_renderer = { SDL_CreateRenderer(*m_window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
		if (m_renderer == nullptr) {
			throw "Unable to create renderer";
		}
	}
	static void closeEverything(SDL_Renderer *m_renderer, SDL_Window *m_window) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		Mix_CloseAudio();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}
}