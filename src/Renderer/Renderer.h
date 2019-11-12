#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <unordered_map>
#include "Types.h"
#include "Constants.h"


class Renderer {

private:
	SDL_Renderer *m_renderer = nullptr;
	SDL_Window *m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	static Renderer *renderer;
	// El constructor es privado para evitar que otra clase lo llame
	Renderer();

public:
	// Debe ser público para poder llamar a este método sin instanciar la clase.
	// La mayoría de métodos estáticos suelen ser públicos
	static Renderer *Instance()
	{
		// Este if se pregunta cada vez, solo entra en la comparación la primera vez, la siguiente simplemente retorna
		if (renderer == nullptr) { renderer = new Renderer; }
		return renderer;
	};

	~Renderer();
	 void Clear();
	 void Render();
	 void LoadFont(Font font);
	 void LoadTexture(const std::string &id, const std::string &path);
	 void LoadTextureText(const std::string &fontId, Text text);
	 Vector2 GetTextureSize(const std::string &id);
	 // NO está 100% desacoplado de SDL, Podemos sentirnos libres de arreglar estas funciones que acepten un rect. Debo hacerlo, mirar en mi otro rect, ya creado en mi otra clase de mi anterior ejercicio 
	 // Simplemente necesito hacerlo con el rect, además ya tiene Type Rect en Types.h
	 void PushImage(const std::string &id,const SDL_Rect &rect);
	 void PushSprite(const std::string &id,const SDL_Rect &rectSprite,const SDL_Rect &rectPos);
	 void PushRotatedSprite(const std::string &id, const SDL_Rect &rectSprite, const SDL_Rect &rectPos, float angle);
	 void SetRenderDrawColor(int r, int g, int b);	 
	 // Podríamos hacer una función que hace clear del map
};

	 // Añadir tambien la clase botón a este cpp