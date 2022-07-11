#define MEM_DEBUG 1

#include <SDL2/SDL.h> // window, renderer
#include <unistd.h> // sleep
#include <ntr/debug.h>

int main() {
	SDL_Init(0);
	SDL_Window *window = SDL_CreateWindow("title", 0,0, 100,100, 0);
	memdeb_add_m(window, "sdl window");

	SDL_Renderer *rend = SDL_CreateRenderer(window, 0, 0);
	memdeb_add_m(rend, "renderer");
	SDL_RenderPresent(rend);

	memdeb_print();
	sleep(10);

	SDL_DestroyWindow(window);
	memdeb_mark_freed(window);
	SDL_DestroyRenderer(rend);
	memdeb_mark_freed(rend);
	memdeb_print();
	SDL_Quit();
	memdeb_destroy();
	return 0;
}