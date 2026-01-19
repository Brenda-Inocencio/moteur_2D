#pragma once

struct SDL_Renderer;
struct SDL_Texture;

class Block {
	float cooldown;
	float width;
	int height;
	int blockType;
	int direction;
	SDL_Texture* texture;
	float pos_x;
	float pos_y;
public:
	inline float GetPosX() const { return pos_x; }
	inline float GetPosY() const { return pos_y; }
	inline float GetRightX() const { return pos_x+ width; }
	inline float GetBottomY() const { return pos_y+ height; }
	bool collision;
	Block(SDL_Texture* blockTexture);
	~Block();
	void Render(SDL_Renderer* renderer);
	int GetRandomNumber(int min, int max); // TODO: move in appropriate class
	void Update(float now);
};