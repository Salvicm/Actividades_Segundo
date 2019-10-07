#include <exception>
#include <iostream>
#include "utils.h"


int main(int, char*[]) {
	
	// inits
	graphicHelper::initLibrary();
	// Window/Renderer
	SDL_Renderer *m_renderer;
	SDL_Window *m_window;
	graphicHelper::startWindowAndRender(&m_window, &m_renderer);

	// --- SPRITES ---

	//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	// Cursor
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect playerRect{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 175,96 };

	//-->Animated Sprite ---

	// --- TEXT ---
	#pragma region font_Inits
	TTF_Font *mainFont{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 80) };
	if (mainFont == nullptr)
	throw "No es pot inicialitzar the TTF_FONT";
	TTF_Font *subFont{ TTF_OpenFont("../../res/ttf/arial.ttf", 80) };
	if (mainFont == nullptr)
	throw "No es pot inicialitzar the TTF_FONT";
	SDL_Surface *tmpSurf = nullptr;
	#pragma endregion
	//Button initialization
	#pragma region "Button Initialization"
	Interactible uwuButton, playButton, exitButton, soundButton;
	uwuButton.initialize(100, 50, "UwU", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf, mainFont, m_renderer);
	playButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -300, "Play", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf, mainFont, m_renderer);
	soundButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -200 , "Sound", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf, mainFont, m_renderer);
	exitButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -100, "Exit", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf, mainFont, m_renderer);
	#pragma endregion

	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(mainFont);
	TTF_CloseFont(subFont);

	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	throw "Unable to initialize SDL_mixer audio systems";

	Mix_Music *bgMusic{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!bgMusic) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME  * 0.75); // Üsar porcentajes, nada de nümeros completos, por següridad de qüe cambie la librería
	Mix_PlayMusic(bgMusic, -1); // Nümero de veces qüe se reprodüce. -1 es ün bücle infinito


	bool isRunning = true;
	bool clickUp = false;
	bool clickDown = false;
	Interactible *pressedButton = nullptr;
	bool invalidPress = false;
	mouseController mainMouse;
	SDL_Event event;
	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mainMouse.x = event.motion.x;
				mainMouse.y = event.motion.y;
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN: // SOLDADO CAIDO, REPITO: SOLDADO CAÍDO
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mainMouse.press = clickDown = true;
				clickUp = false;
				break;
			case SDL_MOUSEBUTTONUP:
				mainMouse.press = clickDown = false;
				clickUp = true;
				break;
			default:
				break;
			}
		}
		// Update
	
	
		playerRect.x += ((mainMouse.x - playerRect.w / 2) - playerRect.x) / 10;
		playerRect.y += ((mainMouse.y - playerRect.h / 2) - playerRect.y) / 10;
	

		if (uwuButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton, invalidPress)) {
			std::cout << "Holaaaa\n";
		}
		if (playButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton, invalidPress)){
		}
		if (exitButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton, invalidPress)){
			isRunning = false;
		}
		if (soundButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton, invalidPress)){
			if (Mix_PausedMusic() == false)
				Mix_PauseMusic();
			else
				Mix_ResumeMusic();
		}

		if (clickDown == true && clickUp == false && pressedButton == nullptr) {
			invalidPress = true;
		}else if (clickDown == false && clickUp == true) {
			pressedButton = nullptr;
			invalidPress = false;
		}

			// Draw
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
			SDL_RenderCopy(m_renderer, uwuButton.texture, nullptr, &uwuButton.rect);
			SDL_RenderCopy(m_renderer, playButton.texture, nullptr, &playButton.rect);
			SDL_RenderCopy(m_renderer, exitButton.texture, nullptr, &exitButton.rect);
			SDL_RenderCopy(m_renderer, soundButton.texture, nullptr, &soundButton.rect);
		
			SDL_RenderPresent(m_renderer);
		}
	
		// Destroy
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyTexture(playerTexture);
		uwuButton.destroyMyself();
		playButton.destroyMyself();
		exitButton.destroyMyself();
		soundButton.destroyMyself();


		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		// Quits
		Mix_CloseAudio();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
		return 0;
}