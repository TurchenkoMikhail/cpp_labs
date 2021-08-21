#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDL_Sprite {
public:

	SDL_Sprite();
	~SDL_Sprite();

	void draw(SDL_Renderer*	renderer);

	void setColor(int r, int g, int b, int a); //change color
	void setColor(SDL_Color color);

	void setPosition(SDL_FPoint position); //change position
	void setPosition(const float & x, const float &y);


	void setScale(const SDL_FPoint scale);   //set new scale
	void setScale(const float & x, const float & y);

	void setTexture(SDL_Texture* texture);  //set textures
	void setTextureRect(SDL_Rect rectTxt);
	void setTextureRect(const int & x, const int & y, const int & w, const int & h);
	void setTextureRect(const float & x, const float & y, const float & w, const float & h);


	void setOrigin(const SDL_FPoint origin);  //set center
	void setOrigin(const float & x, const float & y);

	void setRotation(float angel);
	void rotate(float angel);

	SDL_FPoint getPosition() { return _position; }  
	SDL_FPoint getOrigin() { return _origin; }  
	SDL_FPoint getScale() { return _scale; }  
	SDL_Color getColor() { return _color; }

	SDL_Texture* getTexture() { return _texture; }
	SDL_Rect getTextureRect() {	return _rectTxt; }

	SDL_FRect getRect();

	void move(SDL_FPoint move);
	void move(float x, float y);
	void move(int x, int y);

private:

	void init();

	float			_angel;
	SDL_FPoint		_position;
	SDL_FPoint		_scale;
	SDL_FPoint		_origin;
	SDL_Texture*	_texture;
	SDL_Rect		_rectTxt;
	SDL_Color		_color;
};

