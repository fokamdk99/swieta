#include "util.h"

int MAX(int x1, int x2);

int MIN(int x1, int x2);

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return(MAX(x1, x2) < MIN(x1 + w1, x2 + w2) && (MAX(y1, y2)) < MIN(y1 + h1, y2 + h2));
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