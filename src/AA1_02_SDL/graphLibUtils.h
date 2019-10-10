#pragma once

#include "graphicClasses.h"

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
		Mix_VolumeMusic(MIX_MAX_VOLUME  * MUSIC_VOL / 100); // Üsar porcentajes, nada de nümeros completos, por següridad de qüe cambie la librería
	}

	static void startWindowAndRender(SDL_Window **m_window, SDL_Renderer **m_renderer) {
		
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

	//TODO Make renderClear, renderCopy and renderPresent my own functions
	static void renderClear(SDL_Renderer *m_renderer) {
		SDL_RenderClear(m_renderer);
	}
	static void renderCopy(SDL_Renderer *m_renderer, Texture *texture) {
		SDL_RenderCopy(m_renderer, texture->texture, nullptr, &texture->libRect);

	}
	static void renderCopy(SDL_Renderer *m_renderer, Interactible *texture) {
		SDL_RenderCopy(m_renderer, texture->texture, nullptr, &texture->rectLib);

	}
	static void renderPresent(SDL_Renderer *m_renderer) {
		SDL_RenderPresent(m_renderer); 

	}


}