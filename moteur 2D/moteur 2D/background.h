#pragma once

#include <vector>

struct SDL_Texture;
struct SDL_Renderer;

class Background {
	int width;
	int height;
	std::vector<SDL_Texture*> textures;
	SDL_Texture* texture;
public:
	Background(std::vector<SDL_Texture*> _textures);
	~Background();
	void Render(SDL_Renderer* _renderer, int windowWidth, float y_camera, SDL_Texture* _texture);
};