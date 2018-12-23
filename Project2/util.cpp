#include "util.h"

int MAX(int x1, int x2);

int MIN(int x1, int x2);

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return(MAX(x1, x2) < MIN(x1 + w1, x2 + w2) && (MAX(y1, y2)) < MIN(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}

static void resetStage(void)
{
	Entity *e;

	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}

	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	enemySpawnTimer = 0;

	stageResetTimer = FPS * 2;
}

int MAX(int x1, int x2)
{
	if (x1 > x2)
	{
		return x1;
	}
	else
	{
		return x2;
	}
}

int MIN(int x1, int x2)
{
	if (x1 < x2)
	{
		return x1;
	}
	else
	{
		return x2;
	}
}