#include <exception>
#include <iostream>
#include "utils.h"
#include "Constantes.h"


int main(int, char*[]) {
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
// Window/Renderer
SDL_Window *m_window{ SDL_CreateWindow("AA1_02_pt3---", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
if (m_window == nullptr) {
	throw "Unable to create window";
}
SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
if (m_renderer == nullptr) {
	throw "Unable to create renderer";
}


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
TTF_Font *mainFont{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 80) };
if (mainFont == nullptr)
throw "No es pot inicialitzar the TTF_FONT";
TTF_Font *subFont{ TTF_OpenFont("../../res/ttf/arial.ttf", 80) };
if (mainFont == nullptr)
throw "No es pot inicialitzar the TTF_FONT";
SDL_Surface *tmpSurf = nullptr;
button uwuButton, playButton, exitButton, soundButton;
uwuButton.initialize(100, 50, "UwU", SDL_Color{ 255,150,0, 255 }, SDL_Color{ 0, 150, 0, 255 }, tmpSurf, mainFont, m_renderer);
playButton.initialize(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 100, "Play", SDL_Color{255, 0, 0, 255}, SDL_Color{ 255,150,0, 255 }, SDL_Color{ 0, 150, 0, 255 }, tmpSurf, mainFont, m_renderer);
exitButton.initialize(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Exit", SDL_Color{ 255,150,0, 255 }, SDL_Color{ 0, 150, 0, 255 }, tmpSurf, mainFont, m_renderer);
soundButton.initialize(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100, "Sound", SDL_Color{ 255,150, 0, 255 }, SDL_Color{ 0, 150, 0, 255 }, tmpSurf, mainFont, m_renderer);

SDL_FreeSurface(tmpSurf);
TTF_CloseFont(mainFont);
TTF_CloseFont(subFont);

// --- AUDIO ---
if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
throw "Unable to initialize SDL_mixer audio systems";

Mix_Music *bgMusic{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
if (!bgMusic) throw "Unable to load the Mix_Music soundtrack";
Mix_VolumeMusic(0); // �sar porcentajes, nada de n�meros completos, por seg�ridad de q�e cambie la librer�a
Mix_PlayMusic(bgMusic, -1); // N�mero de veces q�e se reprod�ce. -1 es �n b�cle infinito


bool isRunning = true;
bool clickUp = false;
bool clickDown = false;
button *pressedButton = nullptr;
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
	// Update
	playerRect.x += ((mainMouse.x - playerRect.w / 2) - playerRect.x) / 10;
	playerRect.y += ((mainMouse.y - playerRect.h / 2) - playerRect.y) / 10;

	
	if (uwuButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton)) {
		std::cout << "Holaaaa\n";
	}
	if (playButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton)){
	}
	if (exitButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton)){
		isRunning = false;
	}
	if (soundButton.checkClick(mainMouse.x, mainMouse.y, clickUp, clickDown, &pressedButton)){
		if (Mix_PausedMusic() == false)
			Mix_PauseMusic();
		else
			Mix_PlayMusic(bgMusic, -1);
	}

	if (mainMouse.press = false && pressedButton != nullptr) {
		pressedButton = nullptr;
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