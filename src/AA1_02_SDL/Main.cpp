#include <exception>
#include <iostream>
#include <time.h>
#include "graphLibUtils.h"

int main(int, char*[]) {
	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10; //timer
	float deltaTime = 0;

	// inits
	keyboardInputs keyInputs;
	graphicHelper::initLibrary();
	// Window/Renderer
	Window m_window("My_first_SDL", SCREEN_WIDTH, SCREEN_HEIGHT);
	Renderer m_renderer(&m_window);

	// --- SPRITES ---

	//Background
	Texture bgText(&m_renderer, "../../res/img/bg.jpg",  0, 0,  SCREEN_WIDTH, SCREEN_HEIGHT);
	Texture playerTexture(&m_renderer, "../../res/img/kintoun.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 175, 96);
	// Cursor


	//-->Animated Sprite ---
	AnimatedTexture playerAnim(&m_renderer, "../../res/img/sp01.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT /2, 6, 1, 0.5);


	// --- TEXT ---
	Font mainFont("../../res/ttf/saiyan.ttf", 80);
	Font subFont("../../res/ttf/arial.ttf", 80);
	//Button initialization

	Surface tmpSurf;
	Interactible titleButton, playButton, exitButton, soundButton;
	// TODO  
	titleButton.initialize(100, 50, "SDL", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface,  &mainFont, &m_renderer);
	playButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -300, "Play", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, &mainFont, &m_renderer);
	soundButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -200 , "Sound", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, &mainFont, &m_renderer);
	exitButton.initialize(SCREEN_WIDTH - 250, SCREEN_HEIGHT -100, "Exit", SDL_Color{ 255,0,0,255 }, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 231, 228, 0 }, tmpSurf.surface, &mainFont, &m_renderer);
	#pragma endregion
	tmpSurf.free();
	mainFont.close();
	subFont.close();
	// --- AUDIO ---
	
	Audio bgMusic("../../res/au/mainTheme.mp3");
	bgMusic.play(-1);


	bool isRunning = true;
	bool esc = false; 
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
				if (event.key.keysym.sym == SDLK_m) {
					keyInputs.MUTE_KEY = true;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mainMouse.pressDown = true;
				mainMouse.pressUp = false;
				break;
			case SDL_MOUSEBUTTONUP:
				mainMouse.pressDown = false;
				mainMouse.pressUp = true;
				break;
			default:
				break;
			}
		}
#pragma endregion

		// Update
			// Animations
		playerAnim.updateAnimation();
			// Input
		if (keyInputs.ESC_KEY == true ) {
			isRunning =  false;
		}
		if(keyInputs.MUTE_KEY == true){
			if (Mix_PausedMusic() == false) {
				Mix_PauseMusic();
			}
			else {
				Mix_ResumeMusic();
			}	
		}
		int rectNewX = playerTexture.rect.x + ((mainMouse.position.x - playerTexture.rect.w / 2) - playerTexture.rect.x) / 10;
		int rectNewY = playerTexture.rect.y + ((mainMouse.position.y - playerTexture.rect.h / 2) - playerTexture.rect.y) / 10;
		playerTexture.updateRect(rectNewX, rectNewY);
			
		
	
		if (checkButtonColision(&mainMouse, &titleButton)) {
			
			if (titleButton.checkClick(&mainMouse, invalidPress)) {
				std::cout << "Title Pressed\n";
			}
		}
		if (checkButtonColision(&mainMouse, &playButton)) {

			if (playButton.checkClick(&mainMouse, invalidPress)) {
				std::cout << "Works\n";
			}
		}
		if (checkButtonColision(&mainMouse, &exitButton)) {

			if (exitButton.checkClick(&mainMouse, invalidPress)) {
				isRunning = false;
			}
		}
		if (checkButtonColision(&mainMouse, &soundButton)) {

			if (soundButton.checkClick(&mainMouse, invalidPress)) {
				if (Mix_PausedMusic() == false) {
					Mix_PauseMusic();
				}
				else {
					Mix_ResumeMusic();
				}
			}
		}


		if (mainMouse.pressDown == true && mainMouse.pressUp == false && mainMouse.pressedButton == NO_BUTTON) {
			invalidPress = true;
		}else if (mainMouse.pressDown == false && mainMouse.pressUp == true) {
			mainMouse.pressedButton = NO_BUTTON;
			invalidPress = false;
		}
		
			// Draw
			graphicHelper::renderClear(m_renderer.renderer);
			graphicHelper::renderCopy(m_renderer.renderer, &bgText);
			graphicHelper::renderCopy(m_renderer.renderer, &playerAnim);
			graphicHelper::renderCopy(m_renderer.renderer, &playerTexture);
			graphicHelper::renderCopy(m_renderer.renderer, &titleButton);
			graphicHelper::renderCopy(m_renderer.renderer, &playButton);
			graphicHelper::renderCopy(m_renderer.renderer, &exitButton);
			graphicHelper::renderCopy(m_renderer.renderer, &soundButton);
			graphicHelper::renderPresent(m_renderer.renderer);
			keyInputs.clean();

			deltaTime = (clock() - lastTime);
			lastTime = clock();
			deltaTime /= CLOCKS_PER_SEC;
			timeDown -= deltaTime;
			
	}
	
	// Destroy
	bgText.destroy();
	playerTexture.destroy();
	titleButton.destroyMyself();
	playButton.destroyMyself();
	exitButton.destroyMyself();
	soundButton.destroyMyself();

		
	// Quits
	graphicHelper::closeEverything(m_renderer.renderer, m_window.window);
	return 0;
}
