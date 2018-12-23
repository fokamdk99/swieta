#include "common.h"

void prepareScene(void);
void presentScene(void);
SDL_Texture* loadTexture(char* filename);
void blit(SDL_Texture* texture, int x, int y);
SDL_Texture* loadTexture(char* filename);
SDL_Surface* loadSurface(char* filename);
extern App app;
extern Entity player;