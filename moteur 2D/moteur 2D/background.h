#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Background {
	int width;
	int height;
	SDL_Texture* texture;
public:
	Background(SDL_Texture* _texture);
	~Background();
	void Render(SDL_Renderer* _renderer, int windowWidth, float y_camera);
};