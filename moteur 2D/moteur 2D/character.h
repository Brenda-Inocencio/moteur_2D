#pragma once

#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
union SDL_Event;

class Character {
	float pos_x;
	float pos_y;
	int height;
	int width;
	int speed;
	float jumpingTime;
	enum State {
		CHSTATE_STATIC,
		CHSTATE_WALKING,
		CHSTATE_JUMPING,
		CHSTATE_FALLING,
		CHSTATE_CARRYING
	} state;
	State processEvents(std::vector<SDL_Event>& events, float now);

public:
	inline float GetPosX() const { return pos_x; }
	inline float GetPosY() const { return pos_y; }
	inline float GetRightX() const { return pos_x + width; }
	inline float GetBottomY() const { return pos_y + height; }
	bool isGround;
	SDL_Texture* texture;
	~Character();
	Character(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt, std::vector<SDL_Event>& events, float now);
};