#include "ManagerTexture.h"

ManagerTexture::ManagerTexture() {}

void ManagerTexture::SetRender(SDL_Renderer	*renderer){_renderer = renderer;}

void ManagerTexture::Dispose() {
	for (std::map <std::string, SDL_Texture* >::iterator i = _texturemap.begin(); i != _texturemap.end(); ++i)
		SDL_DestroyTexture(i->second);
	
	_texturemap.clear();
}

ManagerTexture::~ManagerTexture(){ Dispose();}


SDL_Texture* ManagerTexture::getTexture(std::string name) {

	std::map <std::string, SDL_Texture* >::iterator mit = _texturemap.find(name);

	if (mit == _texturemap.end()) {
		SDL_Texture* newTexture = loadTexture(name);
		_texturemap.insert(make_pair(name, newTexture));
		return newTexture;
	}
	return mit->second;
}

SDL_Texture* ManagerTexture::loadTexture(std::string name) {
	SDL_Surface* loadedImage = IMG_Load(name.c_str());
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(_renderer, loadedImage);
	SDL_FreeSurface(loadedImage);

	return newTexture;
}

	