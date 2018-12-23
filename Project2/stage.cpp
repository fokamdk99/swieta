#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer();
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);
static void doFighters(void);
static void spawnEnemies(void);
static void drawFighters(void);
static int bulletHitFighter(Entity *b);
static void placeofSpawn(Entity* enemy);

static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static int enemySpawnTimer;
static int StageResetTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	memset(&stage2, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage2.fighterTail = &stage2.fighterHead;
	stage2.bulletTail = &stage2.bulletHead;

	char obrazek[50] = "playerBullet.png";
	char obrazek2[50] = "enemy.png";
	bulletTexture = loadTexture(obrazek);
	enemyTexture = loadTexture(obrazek2);
	enemySpawnTimer = 0;
	initPlayer();
}

static void initPlayer()
{
	player = (Entity*)malloc(sizeof(Entity));
	if (player == NULL)
	{
		printf("zjebane initplayer\n");
	}
	memset(player, 0, sizeof(Entity));
	if (player == NULL)
	{
		printf("zjebany memset w initplayer\n");
	}
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	stage2.fighterTail->next = player;
	stage2.fighterTail = player;

	player->x = 100;
	player->y = 100;
	player->side = SIDE_PLAYER;
	player->health = 1;
	char picture[50] = "player.png";
	player->texture = loadTexture(picture);
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void)
{
	doPlayer();

	doFighters();

	doBullets();

	spawnEnemies();
}

static void doPlayer()
{
	if (player != NULL)
	{

		player->dx = 0;

		player->dy = 0;

		if (player->reload > 0)
		{
			player->reload--;
		}

		if (app.keyboard[SDL_SCANCODE_UP] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dy = ((-2)*PLAYER_SPEED);
		}
		else
			if (app.keyboard[SDL_SCANCODE_UP])
			{
				player->dy = -PLAYER_SPEED;
			}

		if (app.keyboard[SDL_SCANCODE_DOWN] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dy = (2 * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_DOWN])
			{
				player->dy = PLAYER_SPEED;
			}
		}

		if (app.keyboard[SDL_SCANCODE_LEFT] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dx = ((-2) * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_LEFT])
			{
				player->dx = -PLAYER_SPEED;
			}
		}

		if (app.keyboard[SDL_SCANCODE_RIGHT] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dx = (2 * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_RIGHT])
			{
				player->dx = PLAYER_SPEED;
			}
		}


		if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
		{
			fireBullet();
		}
		if (player->x < 0)
		{
			player->x = 0;
		}
		if (player->y < 0)
		{
			player->y = 0;
		}
		if (player->x + player->w > SCREEN_WIDTH)
		{
			player->x = SCREEN_WIDTH - player->w;
		}
		if (player->y + player->h > SCREEN_HEIGHT)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
	}
	else
	{
		printf("player jest nullptr\n");
	}
}

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	if (player == NULL)
	{
		printf("player w dofihters nie dziala\n");
	}

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e != player && e->x < 0)
		{
			e->dx = -e->dx;
		}
		if (e != player && e->y < 0)
		{
			e->dy = -e->dy;
		}
		if (e != player && e->x + e->w > SCREEN_WIDTH)
		{
			e->dx = -e->dx;
		}
		if (e != player && e->y + e->h > SCREEN_HEIGHT)
		{
			e->dy = -e->dy;
		}
		if (e->side != player->side && collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h))
		{
			printf("dofighters: 1\n");
			//player = NULL;
		}

		e->x += e->dx;
		e->y += e->dy;

		if (e->health == 0)//jeœli fighter nie jest playerem i jest ca³kowicie poza lew¹ czêœci¹ ekranu
		{
			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void placeofSpawn(Entity* enemy)
{
	int i = rand() % 3;
	switch (i)
	{
	case 0:
		enemy->x = SCREEN_WIDTH-2*(enemy->w);
		enemy->y = SCREEN_HEIGHT / 2;
		break;
	case 1:
		enemy->x = SCREEN_WIDTH - 200;
		enemy->y = 0;
		break;
	case 2:
		enemy->x = SCREEN_WIDTH - 200;
		enemy->y = SCREEN_HEIGHT - 2*(enemy->h);
		break;
	default:
		printf("zjebany placeofSpawn\n");
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = (Entity*)malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		//enemy->x = SCREEN_WIDTH;
		//enemy->y = rand() % SCREEN_HEIGHT;
		
		enemy->texture = enemyTexture;
		enemy->side = SIDE_ALIEN;
		enemy->health = 1;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 4)+ rand()%9);
		enemy->dy = (5 - (rand() % 7));

		placeofSpawn(enemy);
		enemySpawnTimer = 30 + (rand() % 60);
	}
}

static void fireBullet(void)
{
	Entity *bullet1;
	Entity *bullet2;

	bullet1 = (Entity*)malloc(sizeof(Entity));
	bullet2 = (Entity*)malloc(sizeof(Entity));
	memset(bullet1, 0, sizeof(Entity));
	memset(bullet2, 0, sizeof(Entity));
	stage.bulletTail->next = bullet1;
	stage.bulletTail = bullet1;
	stage2.bulletTail->next = bullet2;
	stage2.bulletTail = bullet2;

	bullet1->x = player->x;
	bullet2->x = player->x;
	bullet1->y = player->y;
	bullet2->y = player->y;
	bullet1->dx = PLAYER_BULLET_SPEED;
	bullet2->dx = PLAYER_BULLET_SPEED;
	bullet1->health = 1;
	bullet2->health = 1;
	bullet1->texture = bulletTexture;
	bullet2->texture = bulletTexture;
	SDL_QueryTexture(bullet1->texture, NULL, NULL, &bullet1->w, &bullet1->h);
	SDL_QueryTexture(bullet2->texture, NULL, NULL, &bullet2->w, &bullet2->h);
	bullet1->side = SIDE_PLAYER;
	bullet2->side = SIDE_PLAYER;

	bullet1->y += (bullet1->h / 2); //+= (player->h / 2)
	bullet2->y += (player->h / 2) + (bullet2->h / 2);
	player->reload = 8;
}

static void doBullets(void)
{
	Entity *b, *prev, *b2, *prev2;

	prev = &stage.bulletHead;
	prev2 = &stage2.bulletHead;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (bulletHitFighter(b) || b->x > SCREEN_WIDTH)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
	for (b2 = stage2.bulletHead.next; b2 != NULL; b2 = b2->next)
	{
		b2->x += b2->dx;
		b2->y += b2->dy;

		if (bulletHitFighter(b2) || b2->x > SCREEN_WIDTH)
		{
			if (b2 == stage2.bulletTail)
			{
				stage2.bulletTail = prev2;
			}

			prev2->next = b2->next;
			free(b2);
			b2 = prev2;
		}

		prev2 = b2;
	}
}

static void draw(void)
{
	drawBullets();

	drawFighters();
}

static void drawPlayer(void)
{
	blit(player->texture, player->x, player->y);
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
	for (b = stage2.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}

static int bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{
			b->health = 0;
			e->health = 0;

			return 1;
		}
	}

	return 0;
}
