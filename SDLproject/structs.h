typedef struct 
{
	void(*logic)(void);
	void(*draw)(void);
} Delegate;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	int up;
	int down;
	int right;
	int left;
	int fire;
	int acc;
} App;

typedef struct
{
	int x;
	int y;
	int dx;
	int dy;
	int health;
	SDL_Texture* texture;
	SDL_Surface* surface;
} Entity;