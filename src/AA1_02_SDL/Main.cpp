#include <exception>
#include <iostream>
#include "utils.h"
#include "Interactible.h"
#include "graphicClasses.h"

int main(int, char*[]) {
	
	// inits
	graphicHelper::initLibrary();
	// Window/Renderer
	SDL_Renderer *m_renderer;
	SDL_Window *m_window;
	graphicHelper::startWindowAndRender(&m_window, &m_renderer);

	// --- SPRITES ---

	//Background
	Texture bgText(&m_renderer, "../../res/img/bg.jpg",  0, 0,  SCREEN_WIDTH,SCREEN_HEIGHT);
	Texture playerTexture(&m_renderer, "../../res/img/kintoun.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 175, 96);
	// Cursor


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
	
	Audio bgMusic("../../res/au/mainTheme.mp3");
	bgMusic.play(-1);


	bool isRunning = true;
	bool clickUp = false;
	bool clickDown = false;
	Interactible *pressedButton = nullptr;
	bool invalidPress = false;
	mouseController mainMouse;
	SDL_Event event;
	while (isRunning) {
#pragma region MouseEvent
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mainMouse.x = event.motion.x;
				mainMouse.y = event.motion.y;
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN: // SOLDADO CAIDO, REPITO: SOLDADO CA�DO
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
#pragma endregion

		// Update
		playerTexture.rect.x += ((mainMouse.x - playerTexture.rect.w / 2) - playerTexture.rect.x) / 10;
		playerTexture.rect.y += ((mainMouse.y - playerTexture.rect.h / 2) - playerTexture.rect.y) / 10;
	

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
			SDL_RenderCopy(m_renderer, bgText.texture, nullptr, &bgText.rect);
			SDL_RenderCopy(m_renderer, playerTexture.texture, nullptr, &playerTexture.rect);
			SDL_RenderCopy(m_renderer, uwuButton.texture, nullptr, &uwuButton.rect);
			SDL_RenderCopy(m_renderer, playButton.texture, nullptr, &playButton.rect);
			SDL_RenderCopy(m_renderer, exitButton.texture, nullptr, &exitButton.rect);
			SDL_RenderCopy(m_renderer, soundButton.texture, nullptr, &soundButton.rect);
		
			SDL_RenderPresent(m_renderer);
	}
	
	// Destroy
	bgText.destroy();
	playerTexture.destroy();
	uwuButton.destroyMyself();
	playButton.destroyMyself();
	exitButton.destroyMyself();
	soundButton.destroyMyself();

		

	// Quits
	graphicHelper::closeEverything(m_renderer, m_window);
	return 0;
}