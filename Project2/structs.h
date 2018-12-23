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
	/*int up;
	int down;
	int right;
	int left;
	int fire;
	int acc;*/
} App;

struct Entity
{
	float x;
	float y;
	float dx;
	float dy;
	int w;
	int h;
	int health;
	int reload;
	SDL_Texture* texture;
	SDL_Surface* surface;
	Entity *next;
	int side;
};

typedef struct
{
	Entity fighterHead, *fighterTail;
	Entity bulletHead, *bulletTail;
} Stage;