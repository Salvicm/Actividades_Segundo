#include <exception>
#include <iostream>
#include "Utils.h"
#include "Interactible.h"
#include "graphicClasses.h"

int main(int, char*[]) {

	// inits
	keyboardInputs keyInputs;
	graphicHelper::initLibrary();
	// Window/Renderer
	SDL_Renderer *m_renderer;
	SDL_Window *m_window;
	graphicHelper::startWindowAndRender(&m_window, &m_renderer);

	// --- SPRITES ---

	//Background
	Texture bgText(&m_renderer, "../../res/img/bg.jpg",  0, 0,  SCREEN_WIDTH, SCREEN_HEIGHT);
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
	#pragma endregion
	//Button initialization
	#pragma region "Button Initialization"

	Surface tmpSurf;
	Interactible titleButton, playButton, exitButton, soundButton;
	// TODO  Hacer simplemente que creas las texturas en cuestión y las pasas como parámetros por referéncia, de ese modo evitas el utilizar SDL ??
	titleButton.initialize(100, 50, "SDL", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface,  mainFont, m_renderer);
	playButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -300, "Play", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, mainFont, m_renderer);
	soundButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -200 , "Sound", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, mainFont, m_renderer);
	exitButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -100, "Exit", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, mainFont, m_renderer);
	#pragma endregion
	tmpSurf.free();
	TTF_CloseFont(mainFont);
	TTF_CloseFont(subFont);

	// --- AUDIO ---
	
	Audio bgMusic("../../res/au/mainTheme.mp3");
	bgMusic.play(-1);


	bool isRunning = true;
	bool clickUp = false;
	bool clickDown = false;
	bool esc = false; 
	Interactible *pressedButton = nullptr;
	bool invalidPress = false;
	mouseController mainMouse;
	SDL_Event event;

	while (isRunning) {
#pragma region MouseEvent
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mainMouse.position.x = event.motion.x;
				mainMouse.position.y = event.motion.y;
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN: 
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					keyInputs.ESC_KEY = true;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				clickDown = true;
				clickUp = false;
				break;
			case SDL_MOUSEBUTTONUP:
				clickDown = false;
				clickUp = true;
				break;
			default:
				break;
			}
		}
#pragma endregion

		// Update
		if (keyInputs.ESC_KEY == true ) {
			isRunning =  false;
		}
		playerTexture.rect.x += ((mainMouse.position.x - playerTexture.rect.w / 2) - playerTexture.rect.x) / 10;
		playerTexture.rect.y += ((mainMouse.position.y - playerTexture.rect.h / 2) - playerTexture.rect.y) / 10;
	
		if (checkMouseColision(mainMouse.position, titleButton.rect)) {
			titleButton.hovering = true;
			if (titleButton.checkClick(clickUp, clickDown, &pressedButton, invalidPress)) {
				std::cout << "Holaaaa\n";

			}
		}
		else titleButton.hovering = false;
		
		/*if (playButton.checkClick(mainMouse.position, clickUp, clickDown, &pressedButton, invalidPress)){
		}
		if (exitButton.checkClick(mainMouse.position, clickUp, clickDown, &pressedButton, invalidPress)){
			isRunning = false;
		}
		if (soundButton.checkClick(mainMouse.position, clickUp, clickDown, &pressedButton, invalidPress)){
			if (Mix_PausedMusic() == false)
				Mix_PauseMusic();
			else
				Mix_ResumeMusic();
		}*/

		if (clickDown == true && clickUp == false && pressedButton == nullptr) {
			invalidPress = true;
		}else if (clickDown == false && clickUp == true) {
			pressedButton = nullptr;
			invalidPress = false;
		}

			// Draw
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, bgText.texture, nullptr, &bgText.rectsdl);
			SDL_RenderCopy(m_renderer, playerTexture.texture, nullptr, &playerTexture.rectsdl);
			SDL_RenderCopy(m_renderer, titleButton.texture, nullptr, &titleButton.rectsdl);
			SDL_RenderCopy(m_renderer, playButton.texture, nullptr, &playButton.rectsdl);
			SDL_RenderCopy(m_renderer, exitButton.texture, nullptr, &exitButton.rectsdl);
			SDL_RenderCopy(m_renderer, soundButton.texture, nullptr, &soundButton.rectsdl);
		
			SDL_RenderPresent(m_renderer);
			keyInputs.clean();
	}
	
	// Destroy
	bgText.destroy();
	playerTexture.destroy();
	titleButton.destroyMyself();
	playButton.destroyMyself();
	exitButton.destroyMyself();
	soundButton.destroyMyself();

		
	// Quits
	graphicHelper::closeEverything(m_renderer, m_window);
	return 0;
}
