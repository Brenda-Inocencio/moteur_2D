#pragma once

#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
union SDL_Event;
class Block;

class Character {
	float pos_x;
	float pos_y;
	float height;
	float width;
	int speed;
	float jumpingTime;
	std::vector<SDL_Texture*> textures;
	SDL_Texture* texture;
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
	~Character();
	Character(std::vector<SDL_Texture*>& _textures);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt, float now, std::vector<SDL_Event>& events, std::vector<Block*> blocks);
	void CollideBlock(std::vector<Block*> blocks);
	bool isGround(std::vector<Block*> blocks);
};