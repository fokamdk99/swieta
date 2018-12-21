#include "main.h"

int main(int argc, char* argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));

	initSDL();

	player.x = 100;
	player.y = 100;
	char obraz[50] = "player.png";
	char pocisk[50] = "bullet.png";
	char* d = obraz;
	player.texture = loadTexture(obraz);
	bullet.texture = loadTexture(pocisk);
	//player.surface = loadSurface(obraz);
	//SDL_Texture* converted = SDL_CreateTextureFromSurface(app.renderer, player.surface);
	//SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer,
		//SDL_Surface*  surface);
	atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		player.x += player.dx;
		player.y += player.dy;

		if (app.up && app.acc)
		{
			player.y -= 8;
		}
		if (app.up)
		{
			player.y -= 4;
		}
		
		if (app.down && app.acc)
		{
			player.y += 8;
		}
		if (app.down)
		{
			player.y += 4;
		}
		
		if (app.right && app.acc)
		{
			player.x += 8;
		}
		if (app.right)
		{
			player.x += 4;
		}

		if (app.left && app.acc)
		{
			player.x -= 8;
		}
		if (app.left)
		{
			player.x -= 4;
		}

		if (app.fire && bullet.health == 0)
		{
			bullet.x = player.x;
			bullet.y = player.y;
			bullet.dx = 16;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		if (bullet.x > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}

		blit(player.texture, player.x, player.y);

		if (bullet.health > 0)
		{
			blit(bullet.texture, bullet.x, bullet.y);
		}

		presentScene();

		SDL_Delay(16);
	}
	return 0;
}

/*
SDL_Texture* loadTexture(char* filename)
{

	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s\n", filename);

	SDL_Surface* loadedSurface = IMG_Load("hello_world.bmp");
	if(loadedSurface == NULL)
	{
		printf("unable to load surface!\n");
	}
	else
	{
		texture = CreateTextureFromSurface(app.renderer, loadedSurface);
		if(texture == NULL)
		{
			printf("unable to creatre texture from surface!\n");
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}
*/
