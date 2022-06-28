# cdebug - memory debugger in c

this program records every call to malloc and free, it stores the file, function and line of the call. At the end it prints out every call, 
that has not been freed

## Example

More examples are in the `tests/` directory

### tests/test1.c:
```c
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

	memdeb_print(true);
	sleep(10);

	SDL_DestroyWindow(window);
	memdeb_mark_freed(window, "freed window");
	SDL_DestroyRenderer(rend);
	memdeb_mark_freed(rend, "freed renderer");
	memdeb_print(true);
	SDL_Quit();
	memdeb_destroy();
	return 0;
}
```
### Output:
```
0: 
        line: 10
        file: test1.c
        func: main
        isFreed: 0
        message: sdl window
1: 
        line: 13
        file: test1.c
        func: main
        isFreed: 0
        message: renderer
0: 
        line: 10
        file: test1.c
        func: main
        isFreed: 1
        message: freed window
1: 
        line: 13
        file: test1.c
        func: main
        isFreed: 1
        message: freed renderer
```
