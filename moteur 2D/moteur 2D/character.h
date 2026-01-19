#pragma once
#include <SDL3/SDL.h>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
union SDL_EVENT;

class Character {
	int speed;
	int width;
	int height;
	float pos_x;
	float pos_y;
	enum State {
		CHSTATE_STATIC,
		CHSTATE_WALKING,
		CHSTATE_JUMPING,
		CHSTATE_FALLING,
		CHSTATE_CARRYING
	} state;
public:
	inline float GetPosX() const { return pos_x; }
	inline float GetPosY() const { return pos_y; }
	inline float GetRightX() const { return pos_x + width; }
	inline float GetBottomY() const { return pos_y + height; }
	bool collision;
	SDL_Texture* texture;
	~Character();
	Character(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt, std::vector<SDL_Event>& events);
};