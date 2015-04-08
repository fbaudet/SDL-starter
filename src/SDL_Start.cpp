
#include "../include/SDL_Start.hpp"

std::string				SDL_Start::errorText = "Unexpected Error";

/**
 *********************  CONSTRUCTORS / DESTRUCTORS  ********************
 */

SDL_Start::SDL_Start(int width, int height, std::string title)
	: _width(width), _height(height), _title(title), _continue(true)
{
	state = SDL_GetKeyboardState(NULL);
	return;
}

SDL_Start::~SDL_Start(void)
{
	if (this->getWindow())
		SDL_DestroyWindow(this->getWindow());
	SDL_Quit();
	return;
}

/**
 ********************  METHODS  ********************
 */

bool					SDL_Start::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Start::errorText = "Error SDL_Init : initialization failed";
		throw SDLException();
		SDL_Quit();
		return false;
	}

	this->_window = SDL_CreateWindow(
			this->getTitle().c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			this->getWidth(), this->getHeight(),
			SDL_WINDOW_SHOWN);

	if (this->_window == 0)
	{
		SDL_Start::errorText = "Error SDL_CreateWindow : creation failed";
		throw SDLException();
		SDL_DestroyWindow(this->getWindow());
		SDL_Quit();
		return false;
	}

	return true;
}

void					SDL_Start::mainLoop()
{
	Uint32 timeBegin(SDL_GetTicks()), timeEnd(0), timeRun(0), frameRate(1000 / 50);
	SDL_Renderer * renderer = SDL_CreateRenderer(this->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0xEE, 0xFF);

	while (this->_continue)
	{
		// Events
		SDL_PollEvent(&_event);
		if (this->_event.window.event == SDL_WINDOWEVENT_CLOSE || state[SDL_SCANCODE_ESCAPE])
			_continue = false;
		if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_F])
			this->swapFullScreen();

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		// Frame Rate
		timeEnd = SDL_GetTicks();
		timeRun = timeEnd - timeBegin;
		if (timeRun < frameRate)
		{
			timeBegin = SDL_GetTicks();
			SDL_Delay(frameRate - timeRun);
		}
	}
	SDL_DestroyRenderer(renderer);
}

void                	SDL_Start::swapFullScreen(void)
{
	if (this->getFullScreen())
		this->setFullScreen(false);
	else
		this->setFullScreen(true);
}

void					SDL_Start::showDisplayModes(void)
{
	int modeNumber = SDL_GetNumDisplayModes(0);
	SDL_DisplayMode	mode;

	for (int i = 0; i < modeNumber + 1; ++i)
	{
		if (SDL_GetDisplayMode(0, i, &mode) < 0)
			break;
		std::cout << "Mode " << i << " :\t" << mode.w << "\t" << mode.h << "\t" << mode.refresh_rate << "\t" << SDL_GetPixelFormatName(mode.format) << std::endl;
	}
}

/**
 *******************  GETTERS  *******************
 */

int						SDL_Start::getHeight() const
{
	return this->_height;
}

std::string				SDL_Start::getTitle() const
{
	return this->_title;
}

int						SDL_Start::getWidth() const
{
	return this->_width;
}

SDL_Window *			SDL_Start::getWindow() const
{
	return this->_window;
}

bool					SDL_Start::getFullScreen() const
{
	return this->_fullscreen;
}

/**
 *******************  SETTERS  *******************
 */


void					SDL_Start::setHeight(int height)
{
	this->_height = height;
}

void					SDL_Start::setTitle(std::string title)
{
	this->_title = title;
}

void					SDL_Start::setWidth(int width)
{
	this->_width = width;
}

void					SDL_Start::setFullScreen(bool fs)
{
	if (fs)
	{
		this->_fullscreen = true;
		SDL_SetWindowFullscreen(this->getWindow(), SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		this->_fullscreen = false;
		SDL_SetWindowFullscreen(this->getWindow(), 0);
	}
}

/**
 *******************  NON MEMBERS METHODS  *******************
 */

std::ostream &			operator<<(std::ostream& o, SDL_Start const & rhs)
{
	o << "SDL Window : " << rhs.getTitle() << std::endl;
	return o;
}

/**
 *******************  EXCEPTIONS  *******************
 */

const char *			SDL_Start::SDLException::what() const throw ()
{
	return (SDL_Start::errorText.c_str());
}
