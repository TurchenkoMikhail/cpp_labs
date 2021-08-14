#include "SDL_Sprite.h"

SDL_Sprite::SDL_Sprite(){}
SDL_Sprite::~SDL_Sprite() {}

void SDL_Sprite::init() {
	_origin = { 0.0,0.0 };
	_scale = { 1.0, 1.0 };
	_position = { 0,0 };
	_color = {255, 255, 255, 255};  //RGBA color model
	_rectTxt.x = _rectTxt.y = 0;
	_angel = 0;
}

void SDL_Sprite::setColor(int r, int g, int b, int a) {
	_color = { (Uint8)r,(Uint8)g,(Uint8)b,(Uint8)a };
}
void SDL_Sprite::setColor(SDL_Color color) {_color = color;}

void SDL_Sprite::setPosition(SDL_FPoint position) { _position = position;}
void SDL_Sprite::setPosition(const float& x, const float & y) {_position = { x,y };}

void SDL_Sprite::move(SDL_FPoint move) {
	_position.x += move.x;
	_position.y += move.y;
}

void SDL_Sprite::setScale(SDL_FPoint scale){_scale = scale;}
void SDL_Sprite::setScale(const float & x, const float & y){	_scale = { x,y }; } 

void SDL_Sprite::setTexture(SDL_Texture* texture) {
	_texture = texture;
	SDL_QueryTexture(_texture, NULL,NULL, &_rectTxt.w, &_rectTxt.h);
	init();
}

void SDL_Sprite::setOrigin(SDL_FPoint origin){ _origin = origin; }
void SDL_Sprite::setOrigin(const float & x, const float & y) {_origin = {x,y};}


void SDL_Sprite::setRotation(float angel) {_angel = angel;}
void SDL_Sprite::rotate(float angel) {_angel += angel;}

void SDL_Sprite::draw(SDL_Renderer*	renderer) {
	SDL_FPoint Centr = _origin;
	Centr.x *= _scale.x;
	Centr.y *= _scale.y;
	SDL_FRect rectWin{ 
		_position.x - Centr.x,
		_position.y - Centr.y, 
		_rectTxt.w * _scale.x, 
		_rectTxt.h * _scale.y };

	SDL_SetTextureColorMod(_texture, _color.r, _color.g, _color.b);
	SDL_SetTextureAlphaMod(_texture, _color.a);
	SDL_RenderCopyExF(renderer, _texture, &_rectTxt, &rectWin, _angel, &Centr, SDL_FLIP_NONE);
}

SDL_FRect SDL_Sprite::getRect() {

	SDL_FPoint Centr = _origin;
	Centr.x *= _scale.x;
	Centr.y *= _scale.y;
	SDL_FRect rectWin{
		_position.x - Centr.x,
		_position.y - Centr.y,
		_rectTxt.w * _scale.x,
		_rectTxt.h * _scale.y
	};

	return rectWin;
}

void SDL_Sprite::setTextureRect(SDL_Rect rectTxt) { _rectTxt = rectTxt; }
void SDL_Sprite::setTextureRect(const int & x, const int & y, const int & w, const int & h) {
	_rectTxt = { x,y,w,h };
}

void SDL_Sprite::setTextureRect(const float & x, const float & y, const float & w, const float & h) {
	_rectTxt = {(int) x,(int) y,(int) w,(int) h };
}

void SDL_Sprite::move(float x, float y){
	_position.x += x;
	_position.y += y;
}
void SDL_Sprite::move(int x, int y) {
	_position.x += x;
	_position.y += y;
}