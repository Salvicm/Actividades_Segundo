#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>
#include <SDL_image.h> // Imagenes, faltaría SDL_ttf.h para fuentes y SDL_mixer.h para sonido
#include <SDL_mixer.h>
#include <string>
#include "Constantes.h"

namespace graphicUtils {
	void initLibrary() {
		// inits
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
	}

	void StartWindowAndRender(SDL_Renderer **m_renderer, SDL_Window **m_window) {
		
		SDL_Window *m_auxWindow = { SDL_CreateWindow("AA1_02_pt3...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
		if (m_window == nullptr) {
			throw "Unable to create window";
		}
		SDL_Renderer *m_auxRenderer = { SDL_CreateRenderer(*m_window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
		if (m_renderer == nullptr) {
			throw "Unable to create renderer";
		}
		m_window = &m_auxWindow;
		m_renderer = &m_auxRenderer;
	}

}