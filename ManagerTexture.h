#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <iostream>


class ManagerTexture
{
public:
	void SetRender(SDL_Renderer		*renderer);
	ManagerTexture();
	~ManagerTexture();
	void Dispose();

	SDL_Texture* getTexture(std::string name);
private:
	SDL_Renderer*		_renderer;

	SDL_Texture* loadTexture(std::string name);

	std::map <std::string, SDL_Texture* > _texturemap;

};

