#pragma once

#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
union SDL_Event;
class Block;
class Menu;

class Character {
	float pos_x;
	float pos_y;
	float chHeight;
	float chWidth;
	int speed;
	int jumpSpeed;
	int fallSpeed;
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
	inline float GetRightX() const { return pos_x + chWidth; }
	inline float GetBottomY() const { return pos_y + chHeight; }
	~Character();
	Character(std::vector<SDL_Texture*>& _textures);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt, float now, std::vector<SDL_Event>& events, std::vector<Block*> blocks, Menu& menu);
	void CollideBlock(std::vector<Block*> blocks);
	bool CollideBlockUp(std::vector<Block*> blocks);
	bool isGround(std::vector<Block*> blocks);
};