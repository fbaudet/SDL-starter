
#include "../includes/SDL_Start.hpp"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	SDL_Start sdl(800, 600, "SDL");
	try {
		sdl.initSDL();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	sdl.mainLoop();
	return 0;
}
